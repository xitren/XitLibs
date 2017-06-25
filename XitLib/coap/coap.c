
/* Local headers -------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "coap.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
static coap_token_record awaited_answers[MAXWAIT];
uint32_t awaited_answers_cnt = 0;
static uint8_t part_buff[3];
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
void coap_clock(void)
{
    int i,j;
    for (i=0;i<awaited_answers_cnt;i++)
    {
        awaited_answers[i].tok_wait--;
        if (!(awaited_answers[i].tok_wait))
        {
            printf("Released %d: %06s %d\r\n\r",i,
                    awaited_answers[i].p,awaited_answers[i].used);
            if ((!(awaited_answers[i].used)) 
                    && (awaited_answers[awaited_answers_cnt].release[0]))
            {
                CommandLineInterpreter(awaited_answers[i].release);
            }
            for (j=i+1;j<awaited_answers_cnt;j++)
            {
                awaited_answers[j-1] = awaited_answers[j];
            }
            awaited_answers_cnt--;
        }
    }
    return;
}
char* coap_check_ans(const char *other)
{
    int i,j;
    for (i=0;i<awaited_answers_cnt;i++)
    {
        //printf("I %d: %6s <-> %6s\r\n\r",i,other,awaited_answers[i].p);
        if (!strncmp(other,awaited_answers[i].p,awaited_answers[i].len))
        {
            awaited_answers[i].used = 1;
            return awaited_answers[i].callback;
        }
    }
    return 0;
}

#ifdef DEBUG
void coap_dumpHeader(coap_header_t *hdr)
{
    printf("Header:\r\n\r");
    printf("  ver  0x%02X\r\n\r", hdr->ver);
    printf("  t    0x%02X\r\n\r", hdr->t);
    printf("  tkl  0x%02X\r\n\r", hdr->tkl);
    printf("  code 0x%02X\r\n\r", hdr->code);
    printf("  id   0x%02X%02X\r\n\r", hdr->id[0], hdr->id[1]);
}
void coap_dumpOptions(coap_option_t *opts, size_t numopt)
{
    size_t i;
    printf(" Options:\r\n\r");
    for (i=0;i<numopt;i++)
    {
        printf("  0x%02X [ ", opts[i].num);
        coap_dump(opts[i].buf.p, opts[i].buf.len, true);
        printf(" ]\r\n\r");
    }
    for (i=0;i<numopt;i++)
    {
        printf("  0x%02X [ ", opts[i].num);
        coap_dump_char(opts[i].buf.p, opts[i].buf.len, true);
        printf(" ]\r\n\r");
    }
}
void coap_dumpPacket(coap_packet_t *pkt)
{
    coap_dumpHeader(&pkt->hdr);
    coap_dumpOptions(pkt->opts, pkt->numopts);
    printf("Payload: Size of %d", pkt->payload.len);
    printf("\r\n\r");
    printf("\r\n\r");
}
void coap_dump(const uint8_t *buf, size_t buflen, bool bare)
{
    if (bare)
    {
        while(buflen--)
            printf("%02X%s", *buf++, (buflen > 0) ? " " : "");
    }
    else
    {
        printf("Dump: ");
        while(buflen--)
            printf("%02X%s", *buf++, (buflen > 0) ? " " : "");
        printf("\r\n\r");
    }
}
void coap_dump_char(const uint8_t *buf, size_t buflen, bool bare)
{
    if (bare)
    {
        while(buflen--)
            printf("%c%s", *buf++, (buflen > 0) ? " " : "");
    }
    else
    {
        printf("Dump: ");
        while(buflen--)
            printf("%c%s", *buf++, (buflen > 0) ? " " : "");
        printf("\r\n\r");
    }
}
#endif

int coap_parseHeader(coap_header_t *hdr, const uint8_t *buf, size_t buflen)
{
    if (buflen < 4)
        return COAP_ERR_HEADER_TOO_SHORT;
    hdr->ver = (buf[0] & 0xC0) >> 6;
    if (hdr->ver != 1)
        return COAP_ERR_VERSION_NOT_1;
    hdr->t = (buf[0] & 0x30) >> 4;
    hdr->tkl = buf[0] & 0x0F;
    hdr->code = buf[1];
    if (hdr->code >= COAP_RSPCODE_BAD_REQUEST)
        return COAP_ERR_UNSUPPORTED;
    hdr->id[0] = buf[2];
    hdr->id[1] = buf[3];
    return 0;
}

int coap_parseToken(char* tok_p, size_t *tok_len, const coap_header_t *hdr, const uint8_t *buf, size_t buflen)
{
    if (hdr->tkl == 0)
    {
        memset(tok_p,0,6);
        *tok_len = 0;
        return 0;
    }
    else
    if (hdr->tkl <= 8)
    {
        if (4U + hdr->tkl > buflen)
            return COAP_ERR_TOKEN_TOO_SHORT;   // tok bigger than packet
        memcpy(tok_p,buf+4,hdr->tkl);  // past header
        *tok_len = hdr->tkl;
        return 0;
    }
    else
    {
        // invalid size
        return COAP_ERR_TOKEN_TOO_SHORT;
    }
}

// advances p
int coap_parseOption(coap_option_t *option, uint16_t *running_delta, 
                                            const uint8_t **buf, size_t buflen)
{
    const uint8_t *p = *buf;
    uint8_t headlen = 1;
    uint16_t len, delta;

    if (buflen < headlen) // too small
        return COAP_ERR_OPTION_TOO_SHORT_FOR_HEADER;

    delta = (p[0] & 0xF0) >> 4;
    len = p[0] & 0x0F;

    // These are untested and may be buggy
    if (delta == 13)
    {
        headlen++;
        if (buflen < headlen)
            return COAP_ERR_OPTION_TOO_SHORT_FOR_HEADER;
        delta = p[1] + 13;
        p++;
    }
    else
    if (delta == 14)
    {
        headlen += 2;
        if (buflen < headlen)
            return COAP_ERR_OPTION_TOO_SHORT_FOR_HEADER;
        delta = ((p[1] << 8) | p[2]) + 269;
        p+=2;
    }
    else
    if (delta == 15)
        return COAP_ERR_OPTION_DELTA_INVALID;

    if (len == 13)
    {
        headlen++;
        if (buflen < headlen)
            return COAP_ERR_OPTION_TOO_SHORT_FOR_HEADER;
        len = p[1] + 13;
        p++;
    }
    else
    if (len == 14)
    {
        headlen += 2;
        if (buflen < headlen)
            return COAP_ERR_OPTION_TOO_SHORT_FOR_HEADER;
        len = ((p[1] << 8) | p[2]) + 269;
        p+=2;
    }
    else
    if (len == 15)
        return COAP_ERR_OPTION_LEN_INVALID;

    if ((p + 1 + len) > (*buf + buflen))
        return COAP_ERR_OPTION_TOO_BIG;

    //printf("option num=%d\r\n\r", delta + *running_delta);
    option->num = delta + *running_delta;
    option->buf.p = p+1;
    option->buf.len = len;
    //coap_dump(p+1, len, false);

    // advance buf
    *buf = p + 1 + len;
    *running_delta += delta;

    return 0;
}

// http://tools.ietf.org/html/rfc7252#section-3.1
int coap_parseOptionsAndPayload(coap_option_t *options, uint8_t *numOptions, coap_buffer_t *payload, const coap_header_t *hdr, const uint8_t *buf, size_t buflen)
{
    size_t optionIndex = 0;
    uint16_t delta = 0;
    const uint8_t *p = buf + 4 + hdr->tkl;
    const uint8_t *end = buf + buflen;
    int rc;
    if (p > end)
        return COAP_ERR_OPTION_OVERRUNS_PACKET;   // out of bounds

    //coap_dump(p, end - p);

    // 0xFF is payload marker
    while((optionIndex < *numOptions) && (p < end) && (*p != 0xFF))
    {
        if (0 != (rc = coap_parseOption(&options[optionIndex], &delta, &p, end-p)))
            return rc;
        optionIndex++;
    }
    *numOptions = optionIndex;

    if (p+1 < end && *p == 0xFF)  // payload marker
    {
        payload->p = p+1;
        payload->len = end-(p+1);
    }
    else
    {
        payload->p = NULL;
        payload->len = 0;
    }

    return 0;
}

int coap_parse(coap_packet_t *pkt, const uint8_t *buf, size_t buflen)
{
    int rc;

    // coap_dump(buf, buflen, false);

    if (0 != (rc = coap_parseHeader(&pkt->hdr, buf, buflen)))
        return rc;
//    coap_dumpHeader(&hdr);
    if (0 != (rc = coap_parseToken(pkt->tok_p, &pkt->tok_len, &pkt->hdr, buf, buflen)))
        return rc;
    pkt->numopts = MAXOPT;
    if (0 != (rc = coap_parseOptionsAndPayload(pkt->opts, &(pkt->numopts), &(pkt->payload), &pkt->hdr, buf, buflen)))
        return rc;
//    coap_dumpOptions(opts, numopt);
    return 0;
}

// options are always stored consecutively, so can return a block with same option num
const coap_option_t *coap_findOptions(const coap_packet_t *pkt, uint8_t num, uint8_t *count)
{
    // FIXME, options is always sorted, can find faster than this
    size_t i;
    const coap_option_t *first = NULL;
    *count = 0;
    for (i=0;i<pkt->numopts;i++)
    {
        if (pkt->opts[i].num == num)
        {
            if (NULL == first)
                first = &pkt->opts[i];
            (*count)++;
        }
        else
        {
            if (NULL != first)
                break;
        }
    }
    return first;
}

int coap_buffer_to_string(char *strbuf, size_t strbuflen, const coap_buffer_t *buf)
{
    if (buf->len+1 > strbuflen)
        return COAP_ERR_BUFFER_TOO_SMALL;
    memcpy(strbuf, buf->p, buf->len);
    strbuf[buf->len] = 0;
    return 0;
}

int coap_build(uint8_t *buf, size_t *buflen, const coap_packet_t *pkt, 
        const char *callback, const char *release_cmd)
{
    size_t opts_len = 0;
    size_t i;
    uint8_t *p;
    uint16_t running_delta = 0;

    // build header
    if (*buflen < (4U + pkt->hdr.tkl))
        return COAP_ERR_BUFFER_TOO_SMALL;

    buf[0] = (pkt->hdr.ver & 0x03) << 6;
    buf[0] |= (pkt->hdr.t & 0x03) << 4;
    buf[0] |= (pkt->hdr.tkl & 0x0F);
    buf[1] = pkt->hdr.code;
    buf[2] = pkt->hdr.id[0];
    buf[3] = pkt->hdr.id[1];

    // inject token
    p = buf + 4;
    if ((pkt->hdr.tkl > 0) && (pkt->hdr.tkl != pkt->tok_len))
        return COAP_ERR_UNSUPPORTED;
    
    if (pkt->hdr.tkl > 0)
    {
        memcpy(p, pkt->tok_p, pkt->hdr.tkl);
        printf("%d coap_build len\n",pkt->hdr.tkl);
    }

    // // http://tools.ietf.org/html/rfc7252#section-3.1
    // inject options
    p += pkt->hdr.tkl;

    for (i=0;i<pkt->numopts;i++)
    {
        uint32_t optDelta;
        uint8_t len, delta = 0;

        if (((size_t)(p-buf)) > *buflen)
             return COAP_ERR_BUFFER_TOO_SMALL;
        optDelta = pkt->opts[i].num - running_delta;
        coap_option_nibble(optDelta, &delta);
        coap_option_nibble((uint32_t)pkt->opts[i].buf.len, &len);

        *p++ = (0xFF & (delta << 4 | len));
        if (delta == 13)
        {
            *p++ = (optDelta - 13);
        }
        else
        if (delta == 14)
        {
            *p++ = ((optDelta-269) >> 8);
            *p++ = (0xFF & (optDelta-269));
        }
        if (len == 13)
        {
            *p++ = (pkt->opts[i].buf.len - 13);
        }
        else
        if (len == 14)
  	    {
            *p++ = (pkt->opts[i].buf.len >> 8);
            *p++ = (0xFF & (pkt->opts[i].buf.len-269));
        }

        memcpy(p, pkt->opts[i].buf.p, pkt->opts[i].buf.len);
        p += pkt->opts[i].buf.len;
        running_delta = pkt->opts[i].num;
    }

    opts_len = (p - buf) - 4;   // number of bytes used by options

    if (pkt->payload.len > 0)
    {
        if (*buflen < 4 + 1 + pkt->payload.len + opts_len)
            return COAP_ERR_BUFFER_TOO_SMALL;
        buf[4 + opts_len] = 0xFF;  // payload marker
        memcpy(buf+5 + opts_len, pkt->payload.p, pkt->payload.len);
        *buflen = opts_len + 5 + pkt->payload.len;
    }
    else
        *buflen = opts_len + 4;
    printf("--//internal//-- awaited_answers_cnt %d < MAXWAIT %d && callback %d.\r\n\r",awaited_answers_cnt,MAXWAIT, callback);
    if ((awaited_answers_cnt < MAXWAIT) && (callback))
    {
        if (pkt->hdr.tkl > 0)
            memcpy(awaited_answers[awaited_answers_cnt].p,pkt->tok_p,pkt->hdr.tkl);
        #ifdef DEBUG
            printf("--//internal//-- add tkn %06s clb %s.\r\n\r",
                        pkt->tok_p,callback);
            if (release_cmd)
            {
                printf("--//internal//-- release %s.\r\n\r",release_cmd);
            }
        #endif
        awaited_answers[awaited_answers_cnt].len = pkt->hdr.tkl;
        awaited_answers[awaited_answers_cnt].tok_wait = MAXWAITTIME;
        awaited_answers[awaited_answers_cnt].callback = callback;
        awaited_answers[awaited_answers_cnt].used = 0;
        if (release_cmd)
        {
            strncpy(awaited_answers[awaited_answers_cnt].release,release_cmd
                                                               ,MAXRELEASESTR);
        }
        else
            awaited_answers[awaited_answers_cnt].release[0] = 0;
        awaited_answers_cnt++;
    }
    
    return 0;
}

void coap_option_nibble(uint32_t value, uint8_t *nibble)
{
    if (value<13)
    {
        *nibble = (0xFF & value);
    }
    else
    if (value<=0xFF+13)
    {
        *nibble = 13;
    } else if (value<=0xFFFF+269)
    {
        *nibble = 14;
    }
}
int make_part_option(coap_option_t *opt_part, uint32_t num, 
        coap_option_part_size sizep, uint8_t last)
{
    uint32_t value;
    if (last)
        value = (num << 4) + sizep;
    else
        value = (num << 4) + sizep + 8;
//    part_buff[2] = (uint8_t)(value >> 16);
    part_buff[0] = (uint8_t)(value >> 8);
    part_buff[1] = (uint8_t)(value);
    opt_part->num = COAP_OPTION_BLOCK2;
    opt_part->buf.p = part_buff;
    opt_part->buf.len = 2;
    #ifdef DEBUG
        printf("--//internal//-- Into make_part_option %02X %02X %02X Lenght %d End %d .\r\n\r",
                    part_buff[2],part_buff[1],part_buff[0],opt_part->buf.len, last);
    #endif
    return 0;
}
int parse_part_option(const coap_buffer_t *opt_part,uint8_t *end)
{
    uint32_t value = 0;
    uint32_t len = opt_part->len;
    
    if (len == 3)
    {
        value = ((opt_part->p[0]*65536) 
                + (opt_part->p[1]*256) 
                + (opt_part->p[2])) >> 4;
        *end = ((opt_part->p[2]) >> 3) & 0x01;
    }
    else if (len == 2)
    {
        value = ((opt_part->p[0]*256) 
                + (opt_part->p[1])) >> 4;
        *end = ((opt_part->p[1]) >> 3) & 0x01;
    }
    else if (len == 1)
    {
        value = opt_part->p[0] >> 4;
        *end = ((opt_part->p[0]) >> 3) & 0x01;
    }
    else
        return -1;
    
    
    #ifdef DEBUG
        printf("--//internal//-- %04X Into parse_part_option %X end %02X Lenght %d .\r\n\r"
                    ,((opt_part->p[0]*256) + (opt_part->p[1])),value,*end,len);
    #endif
    return value;
}
//Add make_msg
int coap_make_msg(coap_rw_buffer_t *scratch, coap_packet_t *pkt, 
        coap_option_t *opt_path, coap_option_t *opt_args, coap_option_t *opt_part, 
        const uint8_t *content, size_t content_len, 
        uint8_t msgid_hi, uint8_t msgid_lo, 
        const char* tok_p, size_t tok_len, coap_responsecode_t rspcode, 
        coap_content_type_t content_type)
{
    pkt->hdr.ver = 0x01;
    pkt->hdr.t = COAP_TYPE_NONCON;
    pkt->hdr.tkl = 0;
    pkt->hdr.code = rspcode;
    pkt->hdr.id[0] = msgid_hi;
    pkt->hdr.id[1] = msgid_lo;
    pkt->numopts = 0;

    // need token in response
    if (tok_len > 0) {
        pkt->hdr.tkl = tok_len;
        pkt->tok_len = tok_len;
        memcpy(pkt->tok_p,tok_p,tok_len);
        printf("%d make_msg len\n",tok_len);
    }

    if (opt_path){
        pkt->opts[pkt->numopts].num = opt_path->num;
        pkt->opts[pkt->numopts].buf.p = opt_path->buf.p;
        pkt->opts[pkt->numopts].buf.len = opt_path->buf.len;
        pkt->numopts++;
    }
    if (opt_args){
        pkt->opts[pkt->numopts].num = opt_args->num;
        pkt->opts[pkt->numopts].buf.p = opt_args->buf.p;
        pkt->opts[pkt->numopts].buf.len = opt_args->buf.len;
        pkt->numopts++;
    }
    if (opt_part){
        pkt->opts[pkt->numopts].num = opt_part->num;
        pkt->opts[pkt->numopts].buf.p = opt_part->buf.p;
        pkt->opts[pkt->numopts].buf.len = opt_part->buf.len;
        pkt->numopts++;
        //printf("%02X %02X %02X \n",opt_part->buf.p[0],opt_part->buf.p[1],opt_part->buf.p[2]);
    }
    pkt->payload.p = content;
    pkt->payload.len = content_len;
    return 0;
}
int coap_make_response(coap_rw_buffer_t *scratch, coap_packet_t *pkt,  
        coap_option_t *opt_part, 
        const uint8_t *content, size_t content_len, 
        uint8_t msgid_hi, uint8_t msgid_lo, 
        const char* tok_p, size_t tok_len, coap_responsecode_t rspcode, 
        coap_content_type_t content_type)
{
    pkt->hdr.ver = 0x01;
    pkt->hdr.t = COAP_TYPE_ACK;
    pkt->hdr.tkl = 0;
    pkt->hdr.code = rspcode;
    pkt->hdr.id[0] = msgid_hi;
    pkt->hdr.id[1] = msgid_lo;
    pkt->numopts = 1;

    // need token in response
    if (tok_len > 0) {
        pkt->hdr.tkl = tok_len;
        pkt->tok_len = tok_len;
        memcpy(pkt->tok_p,tok_p,tok_len);
        printf("%d make_response len\n",tok_len);
    }

    // safe because 1 < MAXOPT
    pkt->opts[0].num = COAP_OPTION_CONTENT_FORMAT;
    pkt->opts[0].buf.p = scratch->p;
    if (scratch->len < 2)
        return COAP_ERR_BUFFER_TOO_SMALL;
    scratch->p[0] = ((uint16_t)content_type & 0xFF00) >> 8;
    scratch->p[1] = ((uint16_t)content_type & 0x00FF);
    pkt->opts[0].buf.len = 2;
    if (opt_part){
        pkt->opts[1].num = opt_part->num;
        pkt->opts[1].buf.p = opt_part->buf.p;
        pkt->opts[1].buf.len = opt_part->buf.len;
        pkt->numopts = 2;
    }
    pkt->payload.p = content;
    pkt->payload.len = content_len;
    return 0;
}

char bufhr[200];
// FIXME, if this looked in the table at the path before the method then
// it could more easily return 405 errors
int coap_handle_req(coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, 
                                        coap_packet_t *outpkt,
                                        ParserCallback_t callback_function,
                                        char *_ip)
{
    const coap_option_t *opt;
    uint8_t count;
    uint8_t contentistext = 0;
    int i,j,k;
    char* cbl;
    uint32_t lenght = 0;
    bufhr[0]='\0';
    #ifdef DEBUG
        printf("--//internal//-- Into coap_handle_req.\r\n\r");
    #endif
    if (inpkt->hdr.code < 5)
    {
        if (COAP_METHOD_GET == inpkt->hdr.code)
        {
            strncat(bufhr,"/get", 4);
        }
        else if (COAP_METHOD_PUT == inpkt->hdr.code)
        {
            strncat(bufhr,"/put", 4);
        }
        else if (COAP_METHOD_POST == inpkt->hdr.code)
        {
            strncat(bufhr,"/post", 4);
        }
        else if (COAP_METHOD_DELETE == inpkt->hdr.code)
        {
            strncat(bufhr,"/delete", 7);
        }
        else if (COAP_METHOD_RESET == inpkt->hdr.code)
        {
            strncat(bufhr,"/reset", 7);
        }
        if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_URI_PATH, &count)))
        {
            for (i=0;i<count;i++)
            {
                strncat(bufhr,"/", 1);
                strncat(bufhr,(char const *)opt[i].buf.p, opt[i].buf.len);
            }
        }
        strncat(bufhr,"?", 1);
        strncat(bufhr,"ip=", 3);
        strncat(bufhr,_ip, strlen(_ip));
        if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_URI_QUERY, &count)))
        {
            for (i=0;i<count;i++)
            {
                strncat(bufhr,"&", 1);
                strncat(bufhr,(char const *)opt[i].buf.p, opt[i].buf.len);
            }
        }
        if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_BLOCK2, &count)))
        {
            uint8_t end;
            uint16_t part;
            for (i=0;i<count;i++)
            {
                strncat(bufhr,"&part=", 6);
                part = parse_part_option(&opt[i].buf,&end);
                sprintf((bufhr+strlen(bufhr)),"%d&end=%d"
                        ,part,end);
            }
        }
        if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_CONTENT_FORMAT, &count)))
        {
            for (i=0;i<count;i++)
            {
                if ((((opt[i].buf.p[0]) << 8)+(opt[i].buf.p[1])) 
                        == COAP_CONTENTTYPE_TEXT_PLAIN)
                    contentistext = 1;
            }
        }
        if (contentistext)
        {
            strncat(bufhr, "&", 1);
            strncat(bufhr, "value=", 6);
            strncat(bufhr, (char*)inpkt->payload.p, inpkt->payload.len);
        }
        else
            memcpy(scratch->p,inpkt->payload.p,scratch->len = inpkt->payload.len);
    }
    else
    {
        #ifdef DEBUG
            printf("--//internal//-- Look for answer waiting list.\r\n\r");
        #endif
        if (cbl = coap_check_ans((inpkt->tok_p)))
        {
            strncat(bufhr, cbl, strlen(cbl));
            strncat(bufhr,"?", 1);
            strncat(bufhr,"ip=", 3);
            strncat(bufhr,_ip, strlen(_ip));
            if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_BLOCK2, &count)))
            {
                uint8_t end;
                uint16_t part;
                for (i=0;i<count;i++)
                {
                    strncat(bufhr,"&part=", 6);
                    part = parse_part_option(&opt[i].buf,&end);
                    sprintf((bufhr+strlen(bufhr)),"%d&end=%d"
                            ,part,end);
                }
            }
//            if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_CONTENT_FORMAT, &count)))
//            {
//                for (i=0;i<count;i++)
//                {
//                    if ((((opt[i].buf.p[0]) << 8)+(opt[i].buf.p[1])) 
//                            == COAP_CONTENTTYPE_TEXT_PLAIN)
//                        contentistext = 1;
//                }
//            }
//            if (contentistext)
//            {
//                strncat(bufhr, "&", 1);
//                strncat(bufhr, "value=", 6);
//                strncat(bufhr, (char*)inpkt->payload.p, inpkt->payload.len);
//            }
//            else
                memcpy(scratch->p,inpkt->payload.p,scratch->len = inpkt->payload.len);
            #ifdef DEBUG
                printf("--//internal//-- Found.\r\n\r");
            #endif
        }
        else
        {
            #ifdef DEBUG
                printf("--//internal//-- Not Found Any.\r\n\r");
                printf("--//internal//-- Into END of coap_handle_req.\r\n\r");
            #endif
            return 0;
        }
    }
    #ifdef DEBUG
        printf("======================================\r\n\r%s\r\n\r======================================\r\n\r",bufhr);
    #endif
    if ((*callback_function)((char*)bufhr))
    {
        scratch->len = 4096;
    }
    scratch->len = 4096;

    #ifdef DEBUG
        printf("--//internal//-- Into END of coap_handle_req.\r\n\r");
    #endif
    return 0;
}

void coap_setup(void)
{
}
/*============================================================================*/
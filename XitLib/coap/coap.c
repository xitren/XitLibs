
/* Local headers -------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "coap.h"
#include "array.h"
#include "umm_malloc.h"
#include "LogModule.h"
#include "CommandModule.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
Array *AwaitedAnswersArray;
//static coap_token_record awaited_answers[MAXWAIT];
//uint32_t awaited_answers_cnt = 0;
static uint8_t part_buff[3];
static uint8_t type_opt[3];
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
void coap_clock(void)
{
    int i,j;
    coap_token_record *answer;
    coap_token_record *removed;
    DBG_LOG_DEBUG("Into coap_clock.\n");
    for (i=0;i < array_size(AwaitedAnswersArray);i++)
    {
        array_get_at(AwaitedAnswersArray, i, (void**)&answer);
        answer->tok_wait--;
        if ((answer->used) && (answer->p[0] == 'u'))
        {
            DBG_LOG_TRACE("Released like used %d: %6s %d\n",i,
                    answer->p,answer->used);
            array_remove_at(AwaitedAnswersArray, i, (void **)&removed);
            umm_free((void *)removed);
            i--;
        }
        else if (!(answer->tok_wait))
        {
            DBG_LOG_TRACE("Released %d: %6s %d\n",i,
                    answer->p,answer->used);
            if ( (!(answer->used)) && (answer->release[0] != 0) )
            {
                CommandLineInterpreter(answer->release);
            }
            array_remove_at(AwaitedAnswersArray, i, (void **)&removed);
            umm_free((void *)removed);
            i--;
        }
    }
    return;
}
char* coap_check_ans(const char *other)
{
    int i,j;
    coap_token_record *answer;
        DBG_LOG_TRACE("size %d\n",array_size(AwaitedAnswersArray));
    for (i=0;i < array_size(AwaitedAnswersArray);i++)
    {
        array_get_at(AwaitedAnswersArray, i, (void**)&answer);
//        DBG_LOG_TRACE("I %d: %6s(%d) <-> %6s(%d)\n",i,
//                answer->p,answer->p,answer->used,answer->used);
        if (!strncmp(other,answer->p,answer->len))
        {
            answer->used = 1;
            return answer->callback;
        }
    }
    return 0;
}

#ifdef DEBUG
void coap_dumpHeader(coap_header_t *hdr)
{
    DBG_LOG_DEBUG("Into coap_dumpHeader.\n");
    DBG_LOG_DEBUG("Header:\n");
    DBG_LOG_DEBUG("  ver  0x%02X\n", hdr->ver);
    DBG_LOG_DEBUG("  t    0x%02X\n", hdr->t);
    DBG_LOG_DEBUG("  tkl  0x%02X\n", hdr->tkl);
    DBG_LOG_DEBUG("  code 0x%02X\n", hdr->code);
    DBG_LOG_DEBUG("  id   0x%02X%02X\n", hdr->id[0], hdr->id[1]);
}
void coap_dumpOptions(coap_option_t *opts, size_t numopt)
{
    size_t i;
    DBG_LOG_DEBUG("Into coap_dumpOptions.\n");
    DBG_LOG_DEBUG(" Options:\n");
    for (i=0;i<numopt;i++)
    {
        DBG_LOG_DEBUG("  0x%02X [ ", opts[i].num);
        coap_dump(opts[i].buf.p, opts[i].buf.len, true);
        DBG_LOG_DEBUG(" ]\n");
    }
    for (i=0;i<numopt;i++)
    {
        DBG_LOG_DEBUG("  0x%02X [ ", opts[i].num);
        coap_dump_char(opts[i].buf.p, opts[i].buf.len, true);
        DBG_LOG_DEBUG(" ]\n");
    }
}
void coap_dumpPacket(coap_packet_t *pkt)
{
    DBG_LOG_DEBUG("Into coap_dumpPacket.\n");
    coap_dumpHeader(&pkt->hdr);
    coap_dumpOptions(pkt->opts, pkt->numopts);
    DBG_LOG_DEBUG("Payload: Size of %d", pkt->payload.len);
    DBG_LOG_DEBUG("\n");
}
void coap_dump(const uint8_t *buf, size_t buflen, bool bare)
{
    DBG_LOG_DEBUG("Into coap_dump.\n");
    if (bare)
    {
        while(buflen--)
        {
            printf("%02X%s", *buf++, (buflen > 0) ? " " : "");
        }
    }
    else
    {
        printf("Dump: ");
        while(buflen--)
        {
            printf("%02X%s", *buf++, (buflen > 0) ? " " : "");
        }
        printf("\r\n\r");
    }
}
void coap_dump_char(const uint8_t *buf, size_t buflen, bool bare)
{
    DBG_LOG_DEBUG("Into coap_dump_char.\n");
    if (bare)
    {
        while(buflen--)
        {
            printf("%c%s", *buf++, (buflen > 0) ? " " : "");
        }
    }
    else
    {
        printf("Dump: ");
        while(buflen--)
        {
            printf("%c%s", *buf++, (buflen > 0) ? " " : "");
        }
        printf("\r\n\r");
    }
}
#endif

int coap_parseHeader(coap_header_t *hdr, const uint8_t *buf, size_t buflen)
{
    DBG_LOG_DEBUG("Into coap_parseHeader.\n");
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
    DBG_LOG_DEBUG("Into coap_parseToken.\n");
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
    DBG_LOG_DEBUG("Into coap_parseOption.\n");

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
    DBG_LOG_DEBUG("Into coap_parseOptionsAndPayload.\n");
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

    DBG_LOG_DEBUG("Into coap_parse.\n");
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
    DBG_LOG_DEBUG("Into coap_findOptions.\n");
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
    DBG_LOG_DEBUG("Into coap_buffer_to_string.\n");
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
    coap_token_record *answer;
    DBG_LOG_DEBUG("Into coap_build.\n");

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
        DBG_LOG_DEBUG("%d coap_build len\n",pkt->hdr.tkl);
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
        DBG_LOG_DEBUG("awaited_answers_cnt %d && callback %s.\n"
                , array_size(AwaitedAnswersArray), callback);
    //if ((awaited_answers_cnt < MAXWAIT) && (callback))
    if (callback)
    {
        answer = (coap_token_record *)umm_calloc(1,sizeof(coap_token_record));
        if (pkt->hdr.tkl > 0)
            memcpy(answer->p,pkt->tok_p,pkt->hdr.tkl);
        #ifdef DEBUG
            DBG_LOG_TRACE("add tkn %06s clb %s.\n",
                        pkt->tok_p,callback);
            if (release_cmd)
            {
                DBG_LOG_TRACE("release %s.\n",release_cmd);
            }
        #endif
        answer->len = pkt->hdr.tkl;
        answer->tok_wait = MAXWAITTIME;
        answer->callback = callback;
        answer->used = 0;
        if (release_cmd)
        {
            strncpy(answer->release,release_cmd,MAXRELEASESTR);
        }
        else
            answer->release[0] = 0;
        if (array_add(AwaitedAnswersArray, (void *)answer) != 0)
        {
            umm_free((void *)answer);
            return -1;
        }
    }
    
    return 0;
}

void coap_option_nibble(uint32_t value, uint8_t *nibble)
{
    DBG_LOG_DEBUG("Into coap_option_nibble.\n");
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
    DBG_LOG_DEBUG("Into make_part_option.\n");
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
        DBG_LOG_TRACE("Into make_part_option %02X %02X %02X Lenght %d End %d .\n",
                part_buff[2],part_buff[1],part_buff[0],opt_part->buf.len, last);
    #endif
    return 0;
}
int parse_part_option(const coap_buffer_t *opt_part,uint8_t *end)
{
    uint32_t value = 0;
    uint32_t len = opt_part->len;
    DBG_LOG_DEBUG("Into parse_part_option.\n");
    
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
        DBG_LOG_TRACE("--//internal//-- %04X Into parse_part_option %X end %02X Lenght %d .\n"
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
    DBG_LOG_DEBUG("Into coap_make_msg.\n");
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
        DBG_LOG_TRACE("%d make_msg len\n",tok_len);
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
    DBG_LOG_DEBUG("Into coap_make_response.\n");
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
        DBG_LOG_TRACE("%d make_response len\n",tok_len);
    }

    // safe because 1 < MAXOPT
    pkt->opts[0].num = COAP_OPTION_CONTENT_FORMAT;
    pkt->opts[0].buf.p = type_opt;
    if (scratch->len < 2)
        return COAP_ERR_BUFFER_TOO_SMALL;
    pkt->opts[0].buf.p[0] = ((uint16_t)content_type & 0xFF00) >> 8;
    pkt->opts[0].buf.p[1] = ((uint16_t)content_type & 0x00FF);
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
    DBG_LOG_DEBUG("Into coap_handle_req.\n");
    const coap_option_t *opt;
    uint8_t count;
    uint8_t contentistext = 0;
    int i,j,k;
    char* cbl;
    uint32_t lenght = 0;
    bufhr[0]='\0';
    #ifdef DEBUG
        DBG_LOG_DEBUG("Into coap_handle_req.\n");
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
            DBG_LOG_DEBUG("Look for answer waiting list.\n");
            DBG_LOG_DEBUG("ptr %d.\n",inpkt->tok_p);
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
                DBG_LOG_DEBUG("Found.\n");
            #endif
        }
        else
        {
            #ifdef DEBUG
                DBG_LOG_DEBUG("Not Found Any.\nInto END of coap_handle_req.\n");
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
        DBG_LOG_DEBUG("Into END of coap_handle_req.\n");
    #endif
    return 0;
}

Array *coap_get_waiting_list(void)
{
    return AwaitedAnswersArray;
}
void coap_setup(void)
{
    DBG_LOG_DEBUG("Into coap_setup.\n");
    if (array_new(&AwaitedAnswersArray) != 0)
        return;
}
/*============================================================================*/
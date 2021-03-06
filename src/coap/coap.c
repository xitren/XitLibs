// ----------------------------------------------------------------------------
//
// coap.c - REST api for embedded systems (microcontrollers)
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

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
#include "CRC16ANSI.h"
#include "strnlen.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
Array *AwaitedAnswersArray;
static uint8_t part_buff[3];
static uint8_t type_opt[3];
uint32_t current_coap_mediatype = 0;
static char bufhr[100];
coap_packet_t *current_packet;
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/

//#ifdef DEBUG

void coap_dumpHeader(coap_header_t *hdr)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if (hdr == NULL)
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return;
	}
	DBG_LOG_DEBUG("Header:\n");
	DBG_LOG_DEBUG("  ver  0x%02X\n", hdr->ver);
	DBG_LOG_DEBUG("  t    0x%02X\n", hdr->t);
	DBG_LOG_DEBUG("  tkl  0x%02X\n", hdr->tkl);
	DBG_LOG_DEBUG("  code 0x%02X\n", hdr->code);
	DBG_LOG_DEBUG("  id   0x%02X%02X\n", hdr->id[0], hdr->id[1]);
}

void coap_dump_char(const uint8_t *buf, size_t buflen, bool bare)
{
	if (buf == NULL)
	{
		DBG_LOG_DEBUG("%s: argument is NULL\n", __func__);
		return;
	}
	if (bare)
	{
		while (buflen--)
		{
			DBG_LOG_DEBUG("%c%s", *buf++, (buflen > 0) ? " " : "");
		}
	} else
	{
		//        printf("Dump: \n");
		while (buflen--)
		{
			//            printf("%c%s\n", *buf++, (buflen > 0) ? " " : "");
		}
		//        DBG_LOG_DEBUG("\r\n\r");
	}
}

void coap_dump(const uint8_t *buf, size_t buflen, bool bare)
{
	//    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
	//            __LINE__, __FILE__, __func__);
	if (buf == NULL)
	{
		DBG_LOG_DEBUG("%s: argument is NULL\n", __func__);
		return;
	}
	if (bare)
	{
		//        printf("Bare: ");
		for (; (buflen) > 0; buflen--)
		{
			//            printf("%02X\n", *buf++);
		}
		//        DBG_LOG_DEBUG("\r\n\r");
	} else
	{
		//        printf("Dump: ");
		while (buflen--)
		{
			//            printf("%02X%s", *buf++, (buflen > 0) ? " " : "");
		}
		//        DBG_LOG_DEBUG("\r\n\r");
	}
}

void coap_dumpOptions(coap_option_t *opts, size_t numopt)
{
	size_t i;
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if (opts == NULL)
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return;
	}
	DBG_LOG_DEBUG(" Options (%p):\n", opts);
	for (i = 0; i < numopt; i++)
	{
		DBG_LOG_DEBUG(" (%p) ", &(opts[i]));
		DBG_LOG_DEBUG("0x%02X [ ", opts[i].num);
		if (opts[i].buf.p == NULL)
		{
			DBG_LOG_DEBUG("opts[i].buf.p is NULL\n");
			continue;
		}
		coap_dump(opts[i].buf.p, opts[i].buf.len, false);
		DBG_LOG_DEBUG(" ]\n");
	}
	for (i = 0; i < numopt; i++)
	{
		DBG_LOG_DEBUG(" (%p) ", &(opts[i]));
		DBG_LOG_DEBUG("0x%02X [ ", opts[i].num);
		if (opts[i].buf.p == NULL)
		{
			DBG_LOG_DEBUG("opts[i].buf.p is NULL\n");
			continue;
		}
		coap_dump_char(opts[i].buf.p, opts[i].buf.len, true);
		DBG_LOG_DEBUG(" ]\n");
	}
}

void coap_dumpPacket(coap_packet_t *pkt)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if (pkt == NULL)
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return;
	}
	coap_dumpHeader(&pkt->hdr);
	coap_dumpOptions(pkt->opts, pkt->numopts);
	DBG_LOG_DEBUG("Payload: Size of %d", (int) pkt->payload.len);
	DBG_LOG_DEBUG("\n");
}

//#endif

void coap_clock(void)
{
	uint32_t i;
	coap_token_record *answer;
	coap_token_record *removed;
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	for (i = 0; i < array_size(AwaitedAnswersArray); i++)
	{
		array_get_at(AwaitedAnswersArray, i, (void**) &answer);
		if (answer == NULL)
		{
			DBG_LOG_ERROR("answer is NULL\n");
			continue;
		}
		answer->tok_wait--;
		if ((answer->used) && (answer->p[0] == 'u'))
		{
			if (answer->p == NULL)
			{
				DBG_LOG_ERROR("answer->p is NULL\n");
				continue;
			}
			DBG_LOG_TRACE("Released like used %d: %6s %d\n", i,
					answer->p, answer->used);
			array_remove_at(AwaitedAnswersArray, i, (void **) &removed);
			if (removed == NULL)
			{
				DBG_LOG_ERROR("removed is NULL\n");
				continue;
			}
			umm_free((void *) removed);
			i--;
		} else if (!(answer->tok_wait))
		{
			if (answer->p == NULL)
			{
				DBG_LOG_ERROR("answer->p is NULL\n");
				continue;
			}
			DBG_LOG_TRACE("Released %d: %6s %d\n", i,
					answer->p, answer->used);
			if (answer->release == NULL)
			{
				DBG_LOG_ERROR("answer->release is NULL\n");
				continue;
			}
			if ((!(answer->used)) && (answer->release[0] != 0))
			{
				//                CommandLineInterpreter(answer->release);
			}
			array_remove_at(AwaitedAnswersArray, i, (void **) &removed);
			if (removed == NULL)
			{
				DBG_LOG_ERROR("removed is NULL\n");
				continue;
			}
			umm_free((void *) removed);
			i--;
		}
	}
	return;
}

char* coap_check_ans(const char *other)
{
	uint32_t i;
	if (other == NULL)
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}
	coap_token_record *answer;
	DBG_LOG_TRACE("size %d\n", (int) array_size(AwaitedAnswersArray));
	for (i = 0; i < array_size(AwaitedAnswersArray); i++)
	{
		array_get_at(AwaitedAnswersArray, i, (void**) &answer);
		if (answer == NULL)
		{
			DBG_LOG_ERROR("answer is NULL\n");
			continue;
		}
		if (answer->p == NULL)
		{
			DBG_LOG_ERROR("answer->p is NULL\n");
			continue;
		}
		if (!strncmp(other, answer->p, answer->len))
		{
			answer->used = 1;
			return answer->callback;
		}
	}
	return 0;
}

int coap_parseHeader(coap_header_t *hdr, const uint8_t *buf, size_t buflen)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if ((hdr == NULL) || (buf == NULL))
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}
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
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if ((tok_p == NULL) || (tok_len == NULL) || (hdr == NULL) || (buf == NULL))
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}
	if (hdr->tkl == 0)
	{
		memset(tok_p, 0, 6);
		*tok_len = 0;
		return 0;
	} else
		if (hdr->tkl <= 8)
	{
		if (4U + hdr->tkl > buflen)
			return COAP_ERR_TOKEN_TOO_SHORT; // tok bigger than packet
		memcpy(tok_p, buf + 4, hdr->tkl); // past header
		*tok_len = hdr->tkl;
		return 0;
	} else
	{
		// invalid size
		return COAP_ERR_TOKEN_TOO_SHORT;
	}
}

// advances p

int coap_parseOption(coap_option_t *option, uint16_t *running_delta,
		const uint8_t **buf, size_t buflen)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if ((option == NULL) || (running_delta == NULL) || (buf == NULL))
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}
	uint8_t *p = (uint8_t *) * buf;
	uint8_t headlen = 1;
	uint16_t len, delta;

	DBG_LOG_DEBUG("coap_parseOption ");
	coap_dump(p, buflen, false);
	DBG_LOG_DEBUG("\n");

	if (buflen < headlen) // too small
	{
		DBG_LOG_TRACE("COAP_ERR_OPTION_TOO_BIG\n");
		return COAP_ERR_OPTION_TOO_SHORT_FOR_HEADER;
	}

	delta = (p[0] & 0xF0) >> 4;
	len = p[0] & 0x0F;

	// These are untested and may be buggy
	if (delta == 13)
	{
		headlen++;
		if (buflen < headlen)
		{
			DBG_LOG_TRACE("COAP_ERR_OPTION_TOO_BIG\n");
			return COAP_ERR_OPTION_TOO_SHORT_FOR_HEADER;
		}
		delta = p[1] + 13;
		p++;
	} else
		if (delta == 14)
	{
		headlen += 2;
		if (buflen < headlen)
		{
			DBG_LOG_TRACE("COAP_ERR_OPTION_TOO_BIG\n");
			return COAP_ERR_OPTION_TOO_SHORT_FOR_HEADER;
		}
		delta = ((p[1] << 8) | p[2]) + 269;
		p += 2;
	} else
		if (delta == 15)
	{
		DBG_LOG_TRACE("COAP_ERR_OPTION_TOO_BIG\n");
		return COAP_ERR_OPTION_DELTA_INVALID;
	}

	if (len == 13)
	{
		headlen++;
		if (buflen < headlen)
		{
			DBG_LOG_TRACE("COAP_ERR_OPTION_TOO_BIG\n");
			return COAP_ERR_OPTION_TOO_SHORT_FOR_HEADER;
		}
		len = p[1] + 13;
		p++;
	} else
		if (len == 14)
	{
		headlen += 2;
		if (buflen < headlen)
		{
			DBG_LOG_TRACE("COAP_ERR_OPTION_TOO_BIG\n");
			return COAP_ERR_OPTION_TOO_SHORT_FOR_HEADER;
		}
		len = ((p[1] << 8) | p[2]) + 269;
		p += 2;
	} else
		if (len == 15)
	{
		DBG_LOG_TRACE("COAP_ERR_OPTION_TOO_BIG\n");
		return COAP_ERR_OPTION_LEN_INVALID;
	}

	if ((p + 1 + len) > (*buf + buflen))
	{
		DBG_LOG_TRACE("COAP_ERR_OPTION_TOO_BIG\n");
		return COAP_ERR_OPTION_TOO_BIG;
	}

	option->num = delta + *running_delta;
	option->buf.p = p + 1;
	option->buf.len = len;
	coap_dump(option->buf.p, option->buf.len, false);

	// advance buf
	*buf = p + 1 + len;
	*running_delta += delta;

	return 0;
}

// http://tools.ietf.org/html/rfc7252#section-3.1

int coap_parseOptionsAndPayload(coap_option_t *options, uint8_t *numOptions, coap_buffer_t *payload, const coap_header_t *hdr, const uint8_t *buf, size_t buflen)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if ((options == NULL) || (numOptions == NULL) || (payload == NULL)
			|| (hdr == NULL) || (buf == NULL))
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}
	size_t optionIndex = 0;
	uint16_t delta = 0;
	const uint8_t *p = buf + 4 + hdr->tkl;
	const uint8_t *end = buf + buflen;
	int rc;
	coap_dump(p, buflen - (4 + hdr->tkl), false);
	DBG_LOG_DEBUG("\n");
	if (p > end)
	{
		DBG_LOG_TRACE("COAP_ERR_OPTION_OVERRUNS_PACKET\n");
		return COAP_ERR_OPTION_OVERRUNS_PACKET; // out of bounds
	}

	//coap_dump(p, end - p);

	// 0xFF is payload marker
	while ((optionIndex < *numOptions) && (p < end) && (*p != 0xFF))
	{
		if (0 != (rc = coap_parseOption(&options[optionIndex], &delta, &p, end - p)))
		{
			DBG_LOG_TRACE("coap_parseOption error\n");
			return rc;
		}
		optionIndex++;
	}
	*numOptions = optionIndex;

	if (p + 1 < end && *p == 0xFF) // payload marker
	{
		payload->p = (uint8_t *) ((unsigned int) p + 1);
		payload->len = end - (p + 1);
	} else
	{
		payload->p = NULL;
		payload->len = 0;
	}
	coap_dumpOptions(options, optionIndex);

	return 0;
}

int coap_parse(coap_packet_t *pkt, const uint8_t *buf, size_t buflen)
{
	int rc;

	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if ((pkt == NULL) || (buf == NULL))
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}
	//    coap_dump(buf, buflen, false);
	DBG_LOG_DEBUG("%s: %d bytes hash %04X.\n",
			__func__, buflen, CRC16ANSI((uint8_t *) buf, buflen));

	coap_dump(buf, buflen, false);
	DBG_LOG_DEBUG("\n");
	if (0 != (rc = coap_parseHeader(&pkt->hdr, buf, buflen)))
		return rc;
	coap_dumpHeader(&pkt->hdr);
	if (0 != (rc = coap_parseToken(pkt->tok_p, &pkt->tok_len, &pkt->hdr, buf, buflen)))
		return rc;
	pkt->numopts = MAXOPT;
	DBG_LOG_DEBUG("coap_parseOptionsAndPayload.\n");
	if (0 != (rc = coap_parseOptionsAndPayload(
			pkt->opts, &(pkt->numopts), &(pkt->payload),
			&pkt->hdr, buf, buflen)))
		return rc;
	DBG_LOG_DEBUG("coap_parseOptionsAndPayload %d bytes hash %04X.\n",
			pkt->payload.len, CRC16ANSI(pkt->payload.p, pkt->payload.len));
	return 0;
}

// options are always stored consecutively, so can return a block with same option num

const coap_option_t *coap_findOptions(const coap_packet_t *pkt, uint8_t num, uint8_t *count)
{
	// FIXME, options is always sorted, can find faster than this
	size_t i;
	const coap_option_t *first = NULL;
	*count = 0;
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if ((pkt == NULL) || (count == NULL))
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}
	DBG_LOG_TRACE("%s: num = 0x%02X.\n",
			__func__, num);
	for (i = 0; i < pkt->numopts; i++)
	{
		if (pkt->opts[i].num == num)
		{
			if (NULL == first)
			{
				first = &pkt->opts[i];
			}
			(*count)++;
		} else
		{
			if (NULL != first)
				break;
		}
	}
	return first;
}

int coap_buffer_to_string(char *strbuf, size_t strbuflen, const coap_buffer_t *buf)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if ((strbuf == NULL) || (buf == NULL))
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}
	if (buf->len + 1 > strbuflen)
	{
		return COAP_ERR_BUFFER_TOO_SMALL;
	}
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
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if ((buf == NULL) || (buflen == NULL) || (pkt == NULL))
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}

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
		DBG_LOG_DEBUG("%d coap_build len\n", pkt->hdr.tkl);
	}

	// http://tools.ietf.org/html/rfc7252#section-3.1
	// inject options
	p += pkt->hdr.tkl;

	for (i = 0; i < pkt->numopts; i++)
	{
		uint32_t optDelta;
		uint8_t len, delta = 0;

		if (((size_t) (p - buf)) > *buflen)
			return COAP_ERR_BUFFER_TOO_SMALL;
		optDelta = pkt->opts[i].num - running_delta;
		coap_option_nibble(optDelta, &delta);
		coap_option_nibble((uint32_t) pkt->opts[i].buf.len, &len);

		*p++ = (0xFF & (delta << 4 | len));
		if (delta == 13)
		{
			*p++ = (optDelta - 13);
		} else
			if (delta == 14)
		{
			*p++ = ((optDelta - 269) >> 8);
			*p++ = (0xFF & (optDelta - 269));
		}
		if (len == 13)
		{
			*p++ = (pkt->opts[i].buf.len - 13);
		} else
			if (len == 14)
		{
			*p++ = (pkt->opts[i].buf.len >> 8);
			*p++ = (0xFF & (pkt->opts[i].buf.len - 269));
		}

		memcpy(p, pkt->opts[i].buf.p, pkt->opts[i].buf.len);
		p += pkt->opts[i].buf.len;
		running_delta = pkt->opts[i].num;
	}

	opts_len = (p - buf) - 4; // number of bytes used by options

	DBG_LOG_TRACE("Build payload (size:%d)\n", pkt->payload.len);
	if (pkt->payload.len > 0)
	{
		if ((*buflen) < (4 + 1 + pkt->payload.len + opts_len))
		{
			return COAP_ERR_BUFFER_TOO_SMALL;
		}
		buf[4 + opts_len] = 0xFF; // payload marker
		memcpy(buf + 5 + opts_len, pkt->payload.p, pkt->payload.len);
		*buflen = opts_len + 5 + pkt->payload.len;
	} else
	{
		*buflen = opts_len + 4;
	}
	//    DBG_LOG_DEBUG("awaited_answers_cnt %d && callback %s.\n"
	//            , (int)array_size(AwaitedAnswersArray), callback);
	if (callback)
	{
		answer = (coap_token_record *) umm_calloc(1, sizeof (coap_token_record));
		if (pkt->hdr.tkl > 0)
			memcpy(answer->p, pkt->tok_p, pkt->hdr.tkl);
#ifdef DEBUG
		DBG_LOG_TRACE("add tkn %s clb %s.\n",
				pkt->tok_p, callback);
		if (release_cmd)
		{
			DBG_LOG_TRACE("release %s.\n", release_cmd);
		}
#endif
		answer->len = pkt->hdr.tkl;
		answer->tok_wait = MAXWAITTIME;
		answer->callback = (char *) callback;
		answer->used = 0;
		if (release_cmd)
		{
			strncpy(answer->release, release_cmd, MAXRELEASESTR);
		} else
			answer->release[0] = 0;
		if (array_add(AwaitedAnswersArray, (void *) answer) != 0)
		{
			umm_free((void *) answer);
			return -1;
		}
	}

	return 0;
}

void coap_option_nibble(uint32_t value, uint8_t *nibble)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if (nibble == NULL)
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return;
	}
	if (value < 13)
	{
		*nibble = (0xFF & value);
	} else
	{
		if (value <= 0xFF + 13)
		{
			*nibble = 13;
		} else if (value <= 0xFFFF + 269)
		{
			*nibble = 14;
		}
	}
}

int make_part_option(coap_option_t *opt_part, uint32_t num,
		coap_option_part_size sizep, uint8_t last)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if (opt_part == NULL)
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}
	uint32_t value;
	if (last)
		value = (num << 4) + sizep;
	else
		value = (num << 4) + sizep + 8;
	part_buff[0] = (uint8_t) (value >> 8);
	part_buff[1] = (uint8_t) (value);
	opt_part->num = COAP_OPTION_BLOCK2;
	opt_part->buf.p = part_buff;
	opt_part->buf.len = 2;
#ifdef DEBUG
	DBG_LOG_TRACE("Into %s: %02X %02X %02X Lenght %d End %d .\n",
			__func__, part_buff[2], part_buff[1], part_buff[0], (int) opt_part->buf.len, last);
#endif
	return 0;
}

int parse_part_option(const coap_buffer_t *opt_part, uint8_t *end)
{
	uint32_t value = 0;
	uint32_t len = opt_part->len;
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if ((opt_part == NULL) || (end == NULL))
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}

	if (len == 3)
	{
		value = ((opt_part->p[0] << 16)
				+ (opt_part->p[1] << 8)
				+ (opt_part->p[2])) >> 4;
		*end = ((opt_part->p[2]) >> 3) & 0x01;
	} else if (len == 2)
	{
		value = ((opt_part->p[0]*256)
				+ (opt_part->p[1])) >> 4;
		*end = ((opt_part->p[1]) >> 3) & 0x01;
	} else if (len == 1)
	{
		value = opt_part->p[0] >> 4;
		*end = ((opt_part->p[0]) >> 3) & 0x01;
	} else
	{
		return -1;
	}

#ifdef DEBUG
	DBG_LOG_TRACE("--//internal//-- %04X Into parse_part_option %X end %02X Lenght %d .\n",
			((opt_part->p[0] * 256) + (opt_part->p[1])),
			value,
			*end,
			len);
#endif
	return value;
}

int coap_make_msg(coap_rw_buffer_t *scratch, coap_packet_t *pkt,
		coap_option_t *opt_path, coap_option_t *opt_args, coap_option_t *opt_part,
		const uint8_t *content, size_t content_len,
		uint8_t msgid_hi, uint8_t msgid_lo,
		const char* tok_p, size_t tok_len, coap_responsecode_t rspcode,
		coap_content_type_t content_type)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if ((scratch == NULL) || (pkt == NULL) || (tok_p == NULL))
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}
	pkt->hdr.ver = 0x01;
	pkt->hdr.t = COAP_TYPE_NONCON;
	pkt->hdr.tkl = 0;
	pkt->hdr.code = rspcode;
	pkt->hdr.id[0] = msgid_hi;
	pkt->hdr.id[1] = msgid_lo;
	pkt->numopts = 0;

	// need token in response
	if (tok_len > 0)
	{
		pkt->hdr.tkl = tok_len;
		pkt->tok_len = tok_len;
		memcpy(pkt->tok_p, tok_p, tok_len);
		DBG_LOG_TRACE("%d make_msg len\n", (int) tok_len);
	}

	if (opt_path)
	{
		pkt->opts[pkt->numopts].num = opt_path->num;
		pkt->opts[pkt->numopts].buf.p = opt_path->buf.p;
		pkt->opts[pkt->numopts].buf.len = opt_path->buf.len;
		pkt->numopts++;
	}
	if (opt_args)
	{
		pkt->opts[pkt->numopts].num = opt_args->num;
		pkt->opts[pkt->numopts].buf.p = opt_args->buf.p;
		pkt->opts[pkt->numopts].buf.len = opt_args->buf.len;
		pkt->numopts++;
	}
	if (opt_part)
	{
		pkt->opts[pkt->numopts].num = opt_part->num;
		pkt->opts[pkt->numopts].buf.p = opt_part->buf.p;
		pkt->opts[pkt->numopts].buf.len = opt_part->buf.len;
		pkt->numopts++;
	}
	pkt->payload.p = (uint8_t *) content;
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
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if ((scratch == NULL) || (pkt == NULL) || (tok_p == NULL))
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}
	pkt->hdr.ver = 0x01;
	pkt->hdr.t = COAP_TYPE_ACK;
	pkt->hdr.tkl = 0;
	pkt->hdr.code = rspcode;
	pkt->hdr.id[0] = msgid_hi;
	pkt->hdr.id[1] = msgid_lo;
	pkt->numopts = 1;

	// need token in response
	if (tok_len > 0)
	{
		pkt->hdr.tkl = tok_len;
		pkt->tok_len = tok_len;
		memcpy(pkt->tok_p, tok_p, tok_len);
		DBG_LOG_TRACE("%s: tok_len = %d\n", __func__, (int) tok_len);
	}

	// safe because 1 < MAXOPT
	pkt->opts[0].num = COAP_OPTION_CONTENT_FORMAT;
	pkt->opts[0].buf.p = type_opt;
	if (scratch->len < 2)
	{
		DBG_LOG_ERROR("%s: COAP_ERR_BUFFER_TOO_SMALL; scratch->len = %d\n", __func__, scratch->len);
		return COAP_ERR_BUFFER_TOO_SMALL;
	}
	pkt->opts[0].buf.p[0] = ((uint16_t) content_type & 0xFF00) >> 8;
	pkt->opts[0].buf.p[1] = ((uint16_t) content_type & 0x00FF);
	pkt->opts[0].buf.len = 2;
	if (opt_part)
	{
		pkt->opts[1].num = opt_part->num;
		pkt->opts[1].buf.p = opt_part->buf.p;
		pkt->opts[1].buf.len = opt_part->buf.len;
		pkt->numopts = 2;
	}
	if (content == NULL)
	{
		pkt->payload.p = 0;
		pkt->payload.len = 0;
	} else
	{
		pkt->payload.p = (uint8_t *) content;
		pkt->payload.len = content_len;
	}
	return 0;
}

/* The following function is responsible for converting number       */
/* strings to there unsigned integer equivalent.  This function can  */
/* handle leading and tailing white space, however it does not handle*/
/* signed or comma delimited values.  This function takes as its     */
/* input the string which is to be converted.  The function returns  */
/* zero if an error occurs otherwise it returns the value parsed from*/

/* the string passed as the input parameter.                         */
unsigned long StringToUnsignedInteger(char *StringInteger, size_t len)
{
	int IsHex;
	unsigned int Index;
	unsigned long ret_val = 0;

	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);

	/* Before proceeding make sure that the parameter that was passed as */
	/* an input appears to be at least semi-valid.                       */
	if ((StringInteger) && (len))
	{
		/* Initialize the variable.                                       */
		Index = 0;
		DBG_LOG_TRACE("\n%c\n", StringInteger[Index]);

		/* Next check to see if this is a hexadecimal number.             */
		if (len > 2)
		{
			if ((StringInteger[0] == '0')
					&& ((StringInteger[1] == 'x')
					|| (StringInteger[1] == 'X')))
			{
				IsHex = 1;

				/* Increment the String passed the Hexadecimal prefix.      */
				StringInteger += 2;
			} else
				IsHex = 0;
		} else
			IsHex = 0;

		/* Process the value differently depending on whether or not a    */
		/* Hexadecimal Number has been specified.                         */
		if (!IsHex)
		{
			/* Decimal Number has been specified.                          */
			while (1)
			{
				DBG_LOG_TRACE("\nDec %c\n", StringInteger[Index]);
				/* First check to make sure that this is a valid decimal    */
				/* digit.                                                   */
				if ((StringInteger[Index] >= '0')
						&& (StringInteger[Index] <= '9'))
				{
					/* This is a valid digit, add it to the value being      */
					/* built.                                                */
					ret_val += (StringInteger[Index] & 0xF);

					/* Determine if the next digit is valid.                 */
					if (((Index + 1) < len)
							&& (StringInteger[Index + 1] >= '0')
							&& (StringInteger[Index + 1] <= '9'))
					{
						/* The next digit is valid so multiply the current    */
						/* return value by 10.                                */
						ret_val *= 10;
					} else
					{
						/* The next value is invalid so break out of the loop.*/
						break;
					}
				} else
				{
					/* The next value is invalid so break out of the loop.*/
					break;
				}

				Index++;
			}
		} else
		{
			/* Hexadecimal Number has been specified.                      */
			while (1)
			{
				/* First check to make sure that this is a valid Hexadecimal*/
				/* digit.                                                   */
				if (((StringInteger[Index] >= '0')
						&& (StringInteger[Index] <= '9'))
						|| ((StringInteger[Index] >= 'a')
						&& (StringInteger[Index] <= 'f'))
						|| ((StringInteger[Index] >= 'A')
						&& (StringInteger[Index] <= 'F')))
				{
					DBG_LOG_TRACE("\nHex %c", StringInteger[Index]);
					/* This is a valid digit, add it to the value being      */
					/* built.                                                */
					if ((StringInteger[Index] >= '0')
							&& (StringInteger[Index] <= '9'))
						ret_val += (StringInteger[Index] & 0xF);
					else
					{
						if ((StringInteger[Index] >= 'a')
								&& (StringInteger[Index] <= 'f'))
							ret_val += (StringInteger[Index] - 'a' + 10);
						else
							ret_val += (StringInteger[Index] - 'A' + 10);
					}

					/* Determine if the next digit is valid.                 */
					if (((Index + 1) < len)
							&& (((StringInteger[Index + 1] >= '0')
							&& (StringInteger[Index + 1] <= '9'))
							|| ((StringInteger[Index + 1] >= 'a')
							&& (StringInteger[Index + 1] <= 'f'))
							|| ((StringInteger[Index + 1] >= 'A')
							&& (StringInteger[Index + 1] <= 'F'))))
					{
						/* The next digit is valid so multiply the current    */
						/* return value by 16.                                */
						ret_val *= 16;
					} else
					{
						/* The next value is invalid so break out of the loop.*/
						break;
					}
				} else
				{
					/* The next value is invalid so break out of the loop.*/
					break;
				}

				Index++;
			}
		}
	}
	DBG_LOG_TRACE("\nOut of %s. ret_val = %lu.\n", __func__, ret_val);
	return (ret_val);
}

int coap_handle_req(coap_rw_buffer_t *scratch, const coap_packet_t *inpkt,
		coap_packet_t *outpkt,
		ParserCallback_t callback_function,
		char *_ip, uint32_t port)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	DBG_LOG_DEBUG("ProtocolHandler2-in %d bytes hash %04X.\n",
			inpkt->payload.len, CRC16ANSI(inpkt->payload.p, inpkt->payload.len));
	if ((scratch == NULL) || (inpkt == NULL) || (outpkt == NULL)
			|| (_ip == NULL))
	{
		DBG_LOG_ERROR("%s: argument is NULL\n", __func__);
		return 0;
	}
	static ParameterList_t params;
	CommandFunction_t CommandFunction;
	const coap_option_t *opt;
	uint8_t count;
	//    uint8_t contentistext = 0;
	uint32_t methodpermission = 0;
	uint32_t i, j;
	memset(&params, 0, sizeof (ParameterList_t));
	memset(&bufhr, 0, sizeof (bufhr));
	current_packet = (coap_packet_t *) inpkt;
	if (inpkt->hdr.code < 5)
	{
		DBG_LOG_DEBUG("ProtocolHandler3 %d bytes hash %04X.\n",
				inpkt->payload.len, CRC16ANSI(scratch->p, inpkt->payload.len));
		if (COAP_METHOD_GET == inpkt->hdr.code)
			methodpermission = Method_GET;
		else if (COAP_METHOD_PUT == inpkt->hdr.code)
			methodpermission = Method_PUT;
		else if (COAP_METHOD_POST == inpkt->hdr.code)
			methodpermission = Method_POST;
		else if (COAP_METHOD_DELETE == inpkt->hdr.code)
			methodpermission = Method_DELETE;
		else if (COAP_METHOD_RESET == inpkt->hdr.code)
			methodpermission = Method_RESET;
		if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_URI_PATH, &count)))
		{
			for (i = 0; i < count; i++)
			{
				strcat(bufhr, "/");
				strncat(bufhr, (char const *) opt[i].buf.p, opt[i].buf.len);
			}
		}
		if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_URI_QUERY, &count)))
		{
			for (i = 0; i < count; i++)
			{
				uint32_t pre = 0;
				uint32_t old = 0;
				for (j = 0; j < opt[i].buf.len; j++)
				{
					DBG_LOG_TRACE("\n%c\n", opt[i].buf.p[j]);
					if (opt[i].buf.p[j] == '=')
					{
						DBG_LOG_TRACE(" =\n");
						pre = j + 1;
						opt[i].buf.p[j] = 0;
					}
					if (opt[i].buf.p[j] == '&')
					{
						DBG_LOG_TRACE(" &\n");
						DBG_LOG_DEBUG("ProtocolHandler3 %d bytes hash %04X.\n", inpkt->payload.len, CRC16ANSI(scratch->p, inpkt->payload.len));
						DBG_LOG_DEBUG("%s: line %d\n", __func__, __LINE__);
						add_parameter(
								&params,
								(char *) ((unsigned int) opt[i].buf.p + old),
								StringToUnsignedInteger(
								(char *) ((unsigned int) opt[i].buf.p + pre),
								(j - pre))
								);
						old = j + 1;
						pre = 0;
						opt[i].buf.p[j] = 0;
					}
				}
				DBG_LOG_DEBUG("%s: line %d\n", __func__, __LINE__);
				add_parameter(
						&params,
						(char *) ((unsigned int) opt[i].buf.p + old),
						StringToUnsignedInteger(
						(char *) ((unsigned int) opt[i].buf.p + pre),
						(j - pre))
						);
				DBG_LOG_TRACE("\n");
			}
		}
		conv_uint32_bytes_t converter;
		int ip0 = 0, ip1 = 0, ip2 = 0, ip3 = 0;
		sscanf(
				_ip,
				"%u.%u.%u.%u",
				&ip0,
				&ip1,
				&ip2,
				&ip3);
		converter.ui8[0] = (unsigned char) ip0;
		converter.ui8[1] = (unsigned char) ip1;
		converter.ui8[2] = (unsigned char) ip2;
		converter.ui8[3] = (unsigned char) ip3;
		DBG_LOG_DEBUG("%s: line %d\n", __func__, __LINE__);
		add_parameter(&params, "ip", converter.ui32);
		DBG_LOG_DEBUG("%s: line %d\n", __func__, __LINE__);
		add_parameter(&params, "port", port);
		DBG_LOG_DEBUG("%s: line %d\n", __func__, __LINE__);
		if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_OBSERVE, &count)))
		{
			for (i = 0; i < count; i++)
			{
				DBG_LOG_DEBUG("Found observer property.\n");
				add_parameter(&params, "observe", opt[i].buf.p[0]);
			}
		}
		DBG_LOG_DEBUG("%s: line %d\n", __func__, __LINE__);
		if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_BLOCK2, &count)))
		{
			uint8_t end;
			uint16_t part;
			for (i = 0; i < count; i++)
			{
				part = parse_part_option(&opt[i].buf, &end);
				add_parameter(&params, "part", part);
				add_parameter(&params, "end", end);
			}
		}
		current_coap_mediatype = Media_FREE;
		DBG_LOG_DEBUG("%s: line %d\n", __func__, __LINE__);
		if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_CONTENT_FORMAT, &count)))
		{
			DBG_LOG_DEBUG("%s: line %d\n", __func__, __LINE__);
			for (i = 0; i < count; i++)
			{
				uint8_t media_option = ((opt[i].buf.p[0]) << 8) + opt[i].buf.p[1];
				if (media_option == COAP_CONTENTTYPE_TEXT_PLAIN)
				{
					current_coap_mediatype = Media_TEXT;
				} else if (media_option == COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM)
				{
					current_coap_mediatype = Media_BYTE;
				} else if (media_option == COAP_CONTENTTYPE_APPLICATION_XML)
				{
					current_coap_mediatype = Media_XML;
				} else if (media_option == COAP_CONTENTTYPE_APPLICATION_JSON)
				{
					current_coap_mediatype = Media_JSON;
				} else if (media_option == COAP_CONTENTTYPE_APPLICATION_LINKFORMAT)
				{
					current_coap_mediatype = Media_LINK;
				} else
				{
					current_coap_mediatype = Media_UNKNOWN;
				}
				DBG_LOG_TRACE(
						"current_coap_mediatype (%d : %d)\n",
						current_coap_mediatype,
						media_option
						);
			}
		}
		memcpy(scratch->p, inpkt->payload.p, inpkt->payload.len);
		scratch->len = inpkt->payload.len;
	}
	for (i = 0; i < strnlen(bufhr, STRING_SIZE); i++)
	{
		if ((bufhr[i] >= 'A') && (bufhr[i] <= 'Z'))
		{
			bufhr[i] += ('a' - 'A');
		}
	}
	DBG_LOG_DEBUG("%s: line %d\n", __func__, __LINE__);
	CommandFunction = FindCommand(bufhr);
	if (CommandFunction != NULL)
	{
		DBG_LOG_DEBUG("%s: line %d\n", __func__, __LINE__);
		return ((*CommandFunction)(
				methodpermission,
				current_coap_mediatype,
				&params,
				scratch->p,
				(uint32_t *) & scratch->len,
				4096));
	} else
	{
		DBG_LOG_ERROR("%s: CommandFunction is NULL\n", __func__);
		return NO_COMMAND_ERROR;
	}
}

Array *coap_get_waiting_list(void)
{
	return AwaitedAnswersArray;
}

void coap_setup(void)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	if (array_new(&AwaitedAnswersArray) != 0)
		return;
}
/*============================================================================*/





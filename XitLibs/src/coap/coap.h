// ----------------------------------------------------------------------------
//
// coap.h - REST api for embedded systems (microcontrollers)
//
// ----------------------------------------------------------------------------

#ifndef COAP_H
#define COAP_H 1

#ifdef __cplusplus
extern "C" {
#endif

/* Global headers ------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "array.h"
/*============================================================================*/

/* Public defines ------------------------------------------------------------*/
#define MAXOPT 5
#define MAXWAIT 2000
#define MAXWAITTIME 10
#define MAXRELEASESTR 40
#define MEMORY_COAP 7
/*============================================================================*/

/* Public types --------------------------------------------------------------*/
//http://tools.ietf.org/html/rfc7252#section-3
typedef struct
{
    uint8_t ver;                /* CoAP version number */
    uint8_t t;                  /* CoAP Message Type */
    uint8_t tkl;                /* Token length: indicates length of the Token field */
    uint8_t code;               /* CoAP status code. Can be request (0.xx), success reponse (2.xx), 
                                 * client error response (4.xx), or rever error response (5.xx) 
                                 * For possible values, see http://tools.ietf.org/html/rfc7252#section-12.1 */
    uint8_t id[2];
} coap_header_t;
typedef struct
{
    uint8_t *p;
    size_t len;
} coap_buffer_t;
typedef struct
{
    uint8_t *p;
    size_t len;
} coap_rw_buffer_t;
typedef struct
{
    char *callback;
    char release[MAXRELEASESTR];
    uint8_t used;
    char p[6];
    size_t len;
    uint32_t tok_wait;
} coap_token_record;
typedef struct
{
    uint8_t num;                /* Option number. See http://tools.ietf.org/html/rfc7252#section-5.10 */
    coap_buffer_t buf;          /* Option value */
} coap_option_t;
typedef struct
{
    coap_header_t hdr;          /* Header of the packet */
    char tok_p[6];          /* Token value, size as specified by hdr.tkl */
    size_t tok_len;          /* Token value, size as specified by hdr.tkl */
    uint8_t numopts;            /* Number of options */
    coap_option_t opts[MAXOPT]; /* Options of the packet. For possible entries see
                                 * http://tools.ietf.org/html/rfc7252#section-5.10 */
    coap_buffer_t payload;      /* Payload carried by the packet */
} coap_packet_t;
//http://tools.ietf.org/html/rfc7252#section-12.2
typedef enum
{
    COAP_OPTION_IF_MATCH = 1,
    COAP_OPTION_URI_HOST = 3,
    COAP_OPTION_ETAG = 4,
    COAP_OPTION_IF_NONE_MATCH = 5,
    COAP_OPTION_OBSERVE = 6,
    COAP_OPTION_URI_PORT = 7,
    COAP_OPTION_LOCATION_PATH = 8,
    COAP_OPTION_URI_PATH = 11,
    COAP_OPTION_CONTENT_FORMAT = 12,
    COAP_OPTION_MAX_AGE = 14,
    COAP_OPTION_URI_QUERY = 15,
    COAP_OPTION_ACCEPT = 17,
    COAP_OPTION_LOCATION_QUERY = 20,
    COAP_OPTION_BLOCK2 = 23,
    COAP_OPTION_BLOCK1 = 27,
    COAP_OPTION_PROXY_URI = 35,
    COAP_OPTION_PROXY_SCHEME = 39
} coap_option_num_t;
//http://tools.ietf.org/html/rfc7252#section-12.1.1
typedef enum
{
    COAP_METHOD_RESET = 0,
    COAP_METHOD_GET = 1,
    COAP_METHOD_POST = 2,
    COAP_METHOD_PUT = 3,
    COAP_METHOD_DELETE = 4
} coap_method_t;
//http://tools.ietf.org/html/rfc7252#section-12.1.1
typedef enum
{
    COAP_TYPE_CON = 0,
    COAP_TYPE_NONCON = 1,
    COAP_TYPE_ACK = 2,
    COAP_TYPE_RESET = 3
} coap_msgtype_t;
//http://tools.ietf.org/html/rfc7252#section-5.2
//http://tools.ietf.org/html/rfc7252#section-12.1.2
#define MAKE_RSPCODE(clas, det) ((clas << 5) | (det))
typedef enum
{
    COAP_RSPCODE_CONTENT = MAKE_RSPCODE(2, 5),
    COAP_RSPCODE_NOT_FOUND = MAKE_RSPCODE(4, 4),
    COAP_RSPCODE_BAD_REQUEST = MAKE_RSPCODE(4, 0),
    COAP_RSPCODE_CHANGED = MAKE_RSPCODE(2, 4)
} coap_responsecode_t;
//http://tools.ietf.org/html/rfc7252#section-12.3
typedef enum
{
    COAP_CONTENTTYPE_NONE = -1, // bodge to allow us not to send option block
    COAP_CONTENTTYPE_TEXT_PLAIN = 0,
    COAP_CONTENTTYPE_IMAGE_JPEG = 22,
    COAP_CONTENTTYPE_APPLICATION_LINKFORMAT = 40,
    COAP_CONTENTTYPE_APPLICATION_XML = 41,
    COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM = 42,
    COAP_CONTENTTYPE_APPLICATION_EXI = 47,
    COAP_CONTENTTYPE_APPLICATION_JSON = 50,
} coap_content_type_t;
typedef enum
{
    COAP_ERR_NONE = 0,
    COAP_ERR_HEADER_TOO_SHORT = 1,
    COAP_ERR_VERSION_NOT_1 = 2,
    COAP_ERR_TOKEN_TOO_SHORT = 3,
    COAP_ERR_OPTION_TOO_SHORT_FOR_HEADER = 4,
    COAP_ERR_OPTION_TOO_SHORT = 5,
    COAP_ERR_OPTION_OVERRUNS_PACKET = 6,
    COAP_ERR_OPTION_TOO_BIG = 7,
    COAP_ERR_OPTION_LEN_INVALID = 8,
    COAP_ERR_BUFFER_TOO_SMALL = 9,
    COAP_ERR_UNSUPPORTED = 10,
    COAP_ERR_OPTION_DELTA_INVALID = 11,
} coap_error_t;
typedef enum
{
    COAP_PART_SIZE_16 = 0,
    COAP_PART_SIZE_32 = 1,
    COAP_PART_SIZE_64 = 2,
    COAP_PART_SIZE_128 = 3,
    COAP_PART_SIZE_256 = 4,
    COAP_PART_SIZE_512 = 5,
    COAP_PART_SIZE_1024 = 6
} coap_option_part_size;
typedef int (*ParserCallback_t)(char *string);
#define MAX_SEGMENTS 2  // 2 = /foo/bar, 3 = /foo/bar/baz
typedef struct
{
    int count;
    const char *elems[MAX_SEGMENTS];
} coap_endpoint_path_t;
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
#ifdef DEBUG
    void coap_dumpPacket(coap_packet_t *pkt);
    void coap_dumpOptions(coap_option_t *opts, size_t numopt);
    void coap_dumpHeader(coap_header_t *hdr);
    void coap_dump(const uint8_t *buf, size_t buflen, bool bare);
    void coap_dump_char(const uint8_t *buf, size_t buflen, bool bare);
#endif
void coap_clock(void);
int coap_parse(coap_packet_t *pkt, const uint8_t *buf, size_t buflen);
int coap_buffer_to_string(char *strbuf, size_t strbuflen, const coap_buffer_t *buf);
const coap_option_t *coap_findOptions(const coap_packet_t *pkt, uint8_t num, uint8_t *count);
int coap_build(uint8_t *buf, size_t *buflen, const coap_packet_t *pkt, 
                const char *callback, const char *release_cmd);
int coap_make_msg(coap_rw_buffer_t *scratch, coap_packet_t *pkt, 
                        coap_option_t *opt_path, coap_option_t *opt_args, 
                        coap_option_t *opt_part,
                        const uint8_t *content, size_t content_len, 
                        uint8_t msgid_hi, uint8_t msgid_lo, 
                        const char* tok_p, size_t tok_len, coap_responsecode_t rspcode, 
                        coap_content_type_t content_type);
int coap_make_response(coap_rw_buffer_t *scratch, coap_packet_t *pkt,
        coap_option_t *opt_part,  const uint8_t *content, size_t content_len, 
        uint8_t msgid_hi, uint8_t msgid_lo, const char* tok_p, size_t tok_len, 
        coap_responsecode_t rspcode, coap_content_type_t content_type);
int coap_handle_req(coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, 
                                        coap_packet_t *outpkt,
                                        ParserCallback_t callback_function,
                                        char *_ip,uint32_t port);
void coap_option_nibble(uint32_t value, uint8_t *nibble);
void coap_setup(void);
Array *coap_get_waiting_list(void);
void endpoint_setup(void);
int make_part_option(coap_option_t *opt_part, uint32_t num, 
        coap_option_part_size sizep, uint8_t last);
int parse_part_option(const coap_buffer_t *opt_part,uint8_t *end);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif


#ifndef LIBCONFIG_H
#define LIBCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Public defines ------------------------------------------------------------*/
#ifdef MC
    #define LOGGER_SIZE 8
    #define BUFFER_SIZE 10
    #define STRING_SIZE 40
    #define MAX_NUM_OF_PARAMETERS                      (25)  /* Denotes the max   */
                                                             /* number of         */
                                                             /* parameters a      */
                                                             /* command can have. */
    #define PROTO_MAX 15
    #define NODE_MAX 3
    #define BUFFER_1ST_MAX 3 //power of 2 +1
    #define BUFFER_2ND_MAX 64 //power of 2 
    #define BUFFER_3ST_MAX 255
    #define BUFFER_SAMPLE_SIZE 8
    #define EEG_HISTORY_SIZE 32 //power of 2
    #define EXT_EEG_MAX_COUNT 1
#else
    #define LOGGER_SIZE 100
    #define BUFFER_SIZE 120
    #define STRING_SIZE 100
    #define MAX_NUM_OF_PARAMETERS                      (25)  /* Denotes the max   */
                                                             /* number of         */
                                                             /* parameters a      */
                                                             /* command can have. */
    #define PROTO_MAX 40
    #define NODE_MAX 15
    #define BUFFER_1ST_MAX 65 //power of 2 +1
    #define BUFFER_2ND_MAX 1024 //power of 2 
    #define BUFFER_3ST_MAX 255
    #define BUFFER_SAMPLE_SIZE 8
    #define EEG_HISTORY_SIZE 32 //power of 2
    #define EXT_EEG_MAX_COUNT 1
#endif
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* LIBCONFIG_H */


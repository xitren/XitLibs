
#ifndef LIBCONFIG_H
#define LIBCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Public defines ------------------------------------------------------------*/
#ifdef SMALL
    #define HANDLER_BUFFER_LENGTH   1024
    #define CIRCULAR_BUFFER_LENGTH  2
    #define LOGGER_SIZE 100
    #define BUFFER_SIZE 120
    #define STRING_SIZE 100
    #define MAX_NUM_OF_PARAMETERS                      (25)  /* Denotes the max   */
                                                             /* number of         */
                                                             /* parameters a      */
                                                             /* command can have. */
    #define BUFFER_SAMPLE_SIZE 8
    #define MAX_CSMACD_MSGS             16
    #define MAX_CSMACD_NODES            16
    #define CIRCULAR_BUFFER_SIZE        1024
#else
    #define HANDLER_BUFFER_LENGTH   4096
    #define CIRCULAR_BUFFER_LENGTH  48
    #define LOGGER_SIZE 100
    #define BUFFER_SIZE 120
    #define STRING_SIZE 100
    #define MAX_NUM_OF_PARAMETERS                      (25)  /* Denotes the max   */
                                                             /* number of         */
                                                             /* parameters a      */
                                                             /* command can have. */
    #define BUFFER_SAMPLE_SIZE 8
    #define MAX_CSMACD_MSGS             255
    #define MAX_CSMACD_NODES            255
    #define CIRCULAR_BUFFER_SIZE        4096
#endif
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* LIBCONFIG_H */


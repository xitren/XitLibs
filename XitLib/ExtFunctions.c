#ifdef CPU
    #ifdef PLATFORM_WINDOWS
        #pragma comment ( lib, "ws2_32.lib" )
    #endif
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ExtFunctions.h"
#include "Handler.h"
#include "LogModule.h"

#ifdef CPU
    #ifdef PLATFORM_WINDOWS
        #include <winsock2.h>
    #else
        #include <getopt.h> 
        #include <sys/socket.h>
        #include <netinet/in.h>
        #include <arpa/inet.h>
        #include <fcntl.h> 
        #include <errno.h>
        #include <unistd.h>
        #include <sys/ioctl.h>
        #include <sys/types.h>
        #include <sys/time.h>
        #include <sys/mman.h>
        typedef int SOCKET;
    #endif
#else
    #include "usart.h"
#endif
#ifdef PROXY
    #include "../COMtoUDP_Retransliator/ComPort.h"
#endif

#define TXTIMEOUT 10
#ifdef EXTMEMSERVER
    #define PORT_BACK 5683
#else        
    #define PORT_BACK 5683
#endif

/* Private variables ---------------------------------------------------------*/
#ifdef CPU
    struct sockaddr_in cliaddr_hd;
    int fd_hd;
    #ifdef PLATFORM_WINDOWS
        WORD wVersionRequested = MAKEWORD(2, 2);
        WSADATA wsaData;
    #else
    #endif
    int err1;
    int fd;
    #ifdef IPV6
        struct sockaddr_in6 servaddr, cliaddr;
    #else /* IPV6 */
        struct sockaddr_in servaddr, cliaddr;
    #endif /* IPV6 */
    int err;
#endif
/*============================================================================*/

/* Private constants ---------------------------------------------------------*/
/*============================================================================*/

#define PORT 5683

/* Private function prototypes -----------------------------------------------*/
int TransferDMA(const uint8_t *data, const uint32_t datalen);
int TransferUDP(const uint8_t *data, const uint32_t datalen,
        const char* address, const uint32_t port);
int TransferBroadbandUDP(const uint8_t *data, const uint32_t datalen,
        const uint32_t port);
void SetLeds(uint8_t q_green,uint8_t q_red,uint8_t q_blue);
int32_t ADC_read_data_c(uint32_t num);
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
void UserProtocolHandlerThread(void) {
    return;
}
void UserProtocolHandler(void) {
    ProtocolHandler();
    return;
}
void UserOperationHandler(void) {
    OperationHandler();
    return;
}

int32_t ADC_read_data_c(uint32_t num){
    return 0;
}

int TransferDMA(const uint8_t *data, const uint32_t datalen) {
    return 0;
}

int TransferUDP(const uint8_t *data, const uint32_t datalen,
        const char* address /* = "192.168.1.255" */,
        const uint32_t port /* = 5683 */) {
    AddToReceive(data, datalen, 16777343, 5683);
//    coap_dump(data, datalen, true);
    return 0;
}

int TransferBroadbandUDP(const uint8_t *data, const uint32_t datalen,
        const uint32_t port /* = 5683 */) {
    return 0;
}

#ifdef CPU

void InitUDP(void) {
    return;
}
#endif

void SetLeds(uint8_t q_green,uint8_t q_red,uint8_t q_blue)
{
    return;
}
/*============================================================================*/
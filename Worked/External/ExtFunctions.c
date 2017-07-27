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
#ifdef CPU
    int n, rc;
    int len = sizeof (cliaddr);
    uint8_t buf2[4096];

    memset(buf2, 0, sizeof (buf2));
    n = recvfrom(fd, buf2, sizeof (buf2), 0, (struct sockaddr *) &cliaddr, &len);
    cliaddr_hd = cliaddr;
    #ifdef PLATFORM_WINDOWS
    AddToReceive(buf2, n, (uint32_t)cliaddr.sin_addr.S_un.S_addr, 
                                                    ntohs(cliaddr.sin_port));
    #else
    AddToReceive(buf2, n, (uint32_t)cliaddr.sin_addr.s_addr, 
                                                    ntohs(cliaddr.sin_port));
    #endif
    DBG_LOG_INFO("Received %s: ", inet_ntoa(cliaddr.sin_addr));
    #ifdef DEBUG
        coap_dump(buf2, n, true);
    #endif
#else
#endif
    return;
}
void UserProtocolHandler(void) {
    ProtocolHandler();
    return;
}
void UserOperationHandler(void) {
    int i,j, k = 0, l = 0;
    char systemcmd[100];

    #ifdef EV3
    for (i=0;i < 4;i++)
    {
        if (ReadMem(REG_SERVO_1+i) != old_s[i])
        {
            if (ReadMem(REG_SERVO_1+i) == 0)
            {
                snprintf(systemcmd,sizeof(systemcmd),
                        "echo stop > /sys/class/tacho-motor/motor%d/command"
                                                    ,i);
                printf(systemcmd);
                printf("\n");
                system(systemcmd);
            }
            else
            {
                snprintf(systemcmd,sizeof(systemcmd),
                         "echo %d > /sys/class/tacho-motor/motor%d/speed_sp"
                                                    ,ReadMem(REG_SERVO_1+i),i);
                printf(systemcmd);
                printf("\n");
                system(systemcmd);
                snprintf(systemcmd,sizeof(systemcmd),
                         "echo run-forever > /sys/class/tacho-motor/motor%d/command"
                                                    ,i);
                printf(systemcmd);
                printf("\n");
                system(systemcmd);
            }
        }
        old_s[i] = ReadMem(REG_SERVO_1+i);
    }
    #endif

    OperationHandler();
    return;
}

int32_t ADC_read_data_c(uint32_t num){
    return 0;
}

int TransferDMA(const uint8_t *data, const uint32_t datalen) {
#ifndef CPU
    HAL_UART_Transmit_DMA(&huart1, (uint8_t *) data, datalen);
#endif
    return 0;
}

int TransferUDP(const uint8_t *data, const uint32_t datalen,
        const char* address /* = "192.168.1.255" */,
        const uint32_t port /* = 5683 */) {
#ifdef CPU
#ifdef DEBUG
    printf("TransferUDP %s port:%d.\n", address, port);
#endif   
    //        #ifdef EXTMEMSERVER
    //            printf("ext TransferUDP\n");
    //            cliaddr_hd.sin_port=htons(PORT_BACK);
    //            sendto(fd_hd, data, *datalen, 0, (struct sockaddr *) 
    //                    &cliaddr_hd,sizeof(cliaddr_hd));
    //        #else        
    //            SOCKET my_sock=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in dest_addr;
    int status;
    int yes = 1;

    dest_addr.sin_family = PF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(address);
    //dest_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    memset(dest_addr.sin_zero, '\0', sizeof (dest_addr.sin_zero));

    int m = sendto(fd, data, datalen, 0,
            (struct sockaddr *) &dest_addr, sizeof (dest_addr));

    //            #ifdef PLATFORM_WINDOWS
    //                closesocket(my_sock);
    //            #else
    //                close(my_sock);
    //            #endif
    //        #endif
#endif
    return 0;
}

int TransferBroadbandUDP(const uint8_t *data, const uint32_t datalen,
        const uint32_t port /* = 5683 */) {
#ifdef CPU
#ifdef DEBUG
    printf("TransferBroadbandUDP ALL port:%d.\n", port);
#endif       
    //        SOCKET my_sock=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in dest_addr;
    int yes = 1;

    if ((setsockopt(fd, SOL_SOCKET, SO_BROADCAST,
            (char *) &yes, sizeof (yes))) != 0) {
        printf("Setsockopt - SOL_SOCKET error\r\n\r");
    }

    dest_addr.sin_family = PF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    //dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(dest_addr.sin_zero, '\0', sizeof (dest_addr.sin_zero));

    int m = sendto(fd, data, datalen, 0,
            (struct sockaddr *) &dest_addr, sizeof (dest_addr));
    //        #ifdef PLATFORM_WINDOWS
    //            closesocket(my_sock);
    //        #else
    //            close(my_sock);
    //        #endif
#endif
    return 0;
}

#ifdef CPU

void InitUDP(void) {
#ifdef PLATFORM_WINDOWS
    // Инициализация WinSock
    err1 = WSAStartup(wVersionRequested, &wsaData);
    if (err1 != 0) {
        printf("WSAStartup error: %d\n", WSAGetLastError());
    }
#endif

#ifdef IPV6
    fd = socket(AF_INET6, SOCK_DGRAM, 0);
#else /* IPV6 */
    fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    printf("Socket create complete.\n");
#endif /* IPV6 */

    //bzero(&servaddr,sizeof(servaddr));
#ifdef IPV6
    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_addr = in6addr_any;
    servaddr.sin6_port = htons(PORT);
#else /* IPV6 */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    memset(servaddr.sin_zero, '\0', sizeof (servaddr.sin_zero));
#endif /* IPV6 */

    err = bind(fd, (struct sockaddr *) &servaddr, sizeof (servaddr));
    printf("Socket bind complete %d port:%d.\n", err, PORT);
    fd_hd = fd;

    return;
}
#endif

void SetLeds(uint8_t q_green,uint8_t q_red,uint8_t q_blue)
{
    #ifndef CPU
        if (q_green)
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
        else
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
        if (q_red)
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        else
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        if (q_blue)
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
        else
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
    #endif
    return;
}
/*============================================================================*/
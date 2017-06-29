
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ExtFunctions_models.h"
#include "Handler.h"

#define TXTIMEOUT 10
#ifdef EXTMEMSERVER
    #define PORT_BACK 5683
#else        
    #define PORT_BACK 5683
#endif

/* Private variables ---------------------------------------------------------*/
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
void UserProtocolHandler(void) {
//    ProtocolHandler();
    return;
}
void UserOperationHandler(void) {
//    OperationHandler();
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
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "CSMACD.h"
#include "LogModule.h"

#define SERVICE_OVERHEAD            5
#define MSG_HEADER                  0x55
#define MAX_ATTEMPT                 5

#define SIZE_OF_MSG sizeof(MsgDesc_t)

#define RECEIVE_BUFFER_OVERLOAD                    (-1)
#define SEND_BUFFER_OVERLOAD                       (-2)
#define RECEIVE_BUFFER_EMPTY                       (-3)
#define SEND_BUFFER_EMPTY                          (-4)
#define SEND_BUFFER_LOCKED                         (-5)
#define RECEIVE_STATE_ERROR                        (-6)
#define SEND_BUS_LOCKED                            (-7)
    
/* Private constants ---------------------------------------------------------*/
const uint16_t CRC16ANSIoTBL[256] = {
  0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
  0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
  0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
  0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
  0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
  0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
  0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
  0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
  0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
  0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
  0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
  0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
  0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
  0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
  0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
  0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
  0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
  0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
  0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
  0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
  0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
  0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
  0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
  0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
  0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
  0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
  0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
  0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
  0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
  0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
  0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
  0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 
  };
/*============================================================================*/

uint16_t ParseFromRecv(CSMACDController_t *controller, 
                        const uint16_t ptr, const uint16_t size,
                        uint8_t *id, uint8_t *data);
int csma_check_send_msgs(CSMACDController_t *controller);
int delete_msg_in_controller(CSMACDController_t *controller, uint8_t i);

uint16_t ParseFromRecv(CSMACDController_t *controller, 
                        const uint16_t ptr, const uint16_t size,
                        uint8_t *id, uint8_t *data)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    uint16_t    CRC_MB = 0xFFFF;
    uint32_t    DATA = ptr;
    uint16_t    N = size+6;
    uint16_t    CRC_MB_other = 0;
    uint16_t    SIZE = 0;
    uint16_t    N_d = 0;
    uint8_t     item;
    if (data == NULL)
        return 0;
    if (size == 0)
        return 0;
    if (controller->msg_cnt <= 0)
        return 0;
    item = controller->recv_buffer[(DATA++) % CIRCULAR_BUFFER_SIZE];
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (item)];
    *id = item = controller->recv_buffer[(DATA++) % CIRCULAR_BUFFER_SIZE];
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (item)];
    SIZE = (item = controller->recv_buffer[(DATA++) % CIRCULAR_BUFFER_SIZE])*255;
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (item)];
    SIZE += (item = controller->recv_buffer[(DATA++) % CIRCULAR_BUFFER_SIZE]);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (item)];
    while (N--)
    {
        data[N_d++] = (item = controller->recv_buffer[(DATA++) % CIRCULAR_BUFFER_SIZE]);
        CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (item)];
    }
    CRC_MB_other = controller->recv_buffer[(DATA++) % CIRCULAR_BUFFER_SIZE] * 255;
    CRC_MB_other += controller->recv_buffer[(DATA++) % CIRCULAR_BUFFER_SIZE];
    if (CRC_MB != CRC_MB_other)
        return 0;
    DBG_LOG_TRACE("Received message from buffer\n");
    return SIZE;
}
uint16_t PacketizeToSend(CSMACDController_t *controller,
            uint8_t *bytes,const uint8_t id,const uint16_t size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    uint16_t    CRC_MB = 0xFFFF;
    uint8_t     *DATA = bytes;
    uint16_t    N = size;
    if (bytes == NULL)
        return 0;
    if (size == 0)
        return 0;
    if (controller->msg_cnt >= MAX_CSMACD_MSGS)
        return 0;
    controller->msg_area[controller->msg_cnt].msg_addr = controller->send_buffer_head;
    controller->msg_area[controller->msg_cnt].msg_size = (size)+6;
    controller->msg_area[controller->msg_cnt].msg_type = CSMACD_SENDING_MSG;
    controller->msg_area[controller->msg_cnt].msg_attempt = MAX_ATTEMPT;
    controller->msg_cnt++;
    controller->send_buffer[
            (controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE
            ] = MSG_HEADER;
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (MSG_HEADER)];
    controller->send_buffer[
            (controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE
            ] = id;
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (id)];
    controller->send_buffer[
            (controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE
            ] = ((size)/256)&255;
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (((size)/256)&255)];
    controller->send_buffer[
            (controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE
            ] = (size)&255;
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ ((size)&255)];
    while (N--)
    {
        controller->send_buffer[
                (controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE
                ] = (*DATA);
        CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (*DATA++)];
    }
    controller->send_buffer[
            (controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE
            ] = ((CRC_MB)/256)&255;
    controller->send_buffer[
            (controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE
            ] = (CRC_MB)&255;
    return (size)+6;
}

void csma_clock_cycle(CSMACDController_t *controller)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
#if defined(_WIN32) || defined(_WIN64)
    pthread_mutex_lock(&(controller->mutex));
#endif
    controller->no_bytes_cnt++;
    if ( (controller->recv_state != CSMACD_RECV_READY) 
            && (controller->no_bytes_cnt > 3) )
        controller->recv_state = CSMACD_RECV_READY;
    if (controller->state == CSMACD_WAIT)
    {
        controller->wait--;
        if (controller->wait <= 0)
        {
            DBG_LOG_TRACE("Wait over => CSMACD_READY\n");
            controller->state = CSMACD_READY;
        }
    }
#if defined(_WIN32) || defined(_WIN64)
    pthread_mutex_unlock(&(controller->mutex));
#endif
    return;
}

void csma_init(CSMACDController_t *controller, ByteSender_t func)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    memset(controller,0,sizeof(CSMACDController_t));
#if defined(_WIN32) || defined(_WIN64)
    if (pthread_mutex_init(&(controller->mutex), NULL) != 0)
    {
        return;
    }
#endif
    controller->sender = func;
    controller->state = CSMACD_READY;
    controller->recv_state = CSMACD_RECV_READY;
    return;
}

uint16_t csma_main_cycle(CSMACDController_t *controller,
                            uint8_t *id, uint8_t *data)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
#if defined(_WIN32) || defined(_WIN64)
    pthread_mutex_lock(&(controller->mutex));
#endif
    uint8_t i;
    uint16_t size;
    csma_check_send_msgs(controller);
    for (i=0;i < controller->msg_cnt;i++)
    {
        if ( controller->msg_area[i].msg_type == CSMACD_RECEIVED_MSG )
        {
            DBG_LOG_TRACE("Found CSMACD_RECEIVED_MSG\n");
            size = ParseFromRecv(
                    controller,
                    controller->msg_area[i].msg_addr,
                    controller->msg_area[i].msg_size,
                    id,
                    data
            );
            DBG_LOG_TRACE("Delete MSG\n");
            delete_msg_in_controller(controller,i);
            #if defined(_WIN32) || defined(_WIN64)
                pthread_mutex_unlock(&(controller->mutex));
            #endif
            return size;
        }
    }
#if defined(_WIN32) || defined(_WIN64)
    pthread_mutex_unlock(&(controller->mutex));
#endif
    return 0;
}

int csma_receiver(CSMACDController_t *controller, uint8_t byte)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
#if defined(_WIN32) || defined(_WIN64)
    pthread_mutex_lock(&(controller->mutex));
#endif
    controller->no_bytes_cnt = 0;
    switch (controller->recv_state)
    {
        case CSMACD_RECV_READY:
            if (byte == MSG_HEADER)
            {
                DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_KEY\n");
                controller->recv_state = CSMACD_RECV_KEY;
                controller->recv_addr = controller->recv_buffer_head;
            }
            break;
        case CSMACD_RECV_KEY:
            DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_ID\n");
            controller->recv_state = CSMACD_RECV_ID;
            break;
        case CSMACD_RECV_ID:
            DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_SIZE1\n");
            controller->recv_state = CSMACD_RECV_SIZE1;
            controller->recv_data = ((int)byte)*255;
            break;
        case CSMACD_RECV_SIZE1:
            DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_SIZE2\n");
            controller->recv_state = CSMACD_RECV_DATA;
            controller->recv_data += byte;
            controller->recv_data_s = controller->recv_data;
            DBG_LOG_TRACE("Receive counter %d\n",controller->recv_data_s);
            break;
        case CSMACD_RECV_SIZE2: 
            if (controller->recv_data <= 0)
            {
                DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_CRC1\n");
                controller->recv_state = CSMACD_RECV_CRC1;
            }
            else
            {
                DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_DATA\n");
                controller->recv_state = CSMACD_RECV_DATA;
            }
            break;
        case CSMACD_RECV_DATA:
            controller->recv_data--;   
            if (controller->recv_data <= 0)
            {
                DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_CRC1\n");
                controller->recv_state = CSMACD_RECV_CRC1;
            }
            break;
        case CSMACD_RECV_CRC1:
            DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_CRC2\n");
            controller->recv_state = CSMACD_RECV_CRC2;
            break;
        case CSMACD_RECV_CRC2:
            DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_READY\n");
            controller->recv_state = CSMACD_RECV_READY;
            controller->msg_area[controller->msg_cnt].msg_addr = 
                    controller->recv_buffer_head-(6+controller->recv_data_s-1);
            controller->msg_area[controller->msg_cnt].msg_size = 
                    controller->recv_data_s;
            controller->msg_area[controller->msg_cnt].msg_type = 
                    CSMACD_RECEIVED_MSG;
            controller->msg_area[controller->msg_cnt].msg_attempt = 0;
            DBG_LOG_TRACE(
                    "Added msg: \nhead %d\nsize %d\n", 
                    controller->msg_area[controller->msg_cnt].msg_addr,
                    controller->msg_area[controller->msg_cnt].msg_size
            );
            controller->msg_cnt++;
            break;
        default:
        #if defined(_WIN32) || defined(_WIN64)
            pthread_mutex_unlock(&(controller->mutex));
        #endif
            return controller->error_state=RECEIVE_STATE_ERROR;
    }
    
    controller->recv_buffer[
            (controller->recv_buffer_head++) % CIRCULAR_BUFFER_SIZE
            ] = byte;
    
#if defined(_WIN32) || defined(_WIN64)
    pthread_mutex_unlock(&(controller->mutex));
#endif
}

int csma_sender(CSMACDController_t *controller)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
#if defined(_WIN32) || defined(_WIN64)
    pthread_mutex_lock(&(controller->mutex));
#endif
    uint8_t i;
    if (controller->state == CSMACD_READY)
    {
        csma_check_send_msgs(controller); 
        for (i=0;i < controller->msg_cnt;i++)
        {
            if ( controller->msg_area[i].msg_type == CSMACD_SENDING_MSG )
            {
                controller->bus_send = controller->msg_area[i].msg_addr; 
                controller->bus_recv = controller->msg_area[i].msg_size; 
                controller->msg_area[i].msg_attempt--;
                controller->bus_id = i;  
                controller->state = CSMACD_BUS_TRANSMIT;   
                DBG_LOG_TRACE("Send state changed => CSMACD_BUS_TRANSMIT\n");
                break;
            }
        }
    } 
    if (controller->state == CSMACD_BUS_TRANSMIT)
    {
        if (controller->bus_id < 0)
        {
            controller->state = CSMACD_WAIT;
            DBG_LOG_TRACE("Send state changed => CSMACD_WAIT\n");
            controller->wait = 1;
        }
        uint8_t send_byte = controller->send_buffer[
                (controller->bus_send) % CIRCULAR_BUFFER_SIZE
                ];
        DBG_LOG_TRACE("%02X\n ",send_byte);
        //Transmit 
        uint8_t recv_byte = controller->sender(send_byte);
        //Receive
        if (send_byte != recv_byte)
        {
            controller->error_state = SEND_BUS_LOCKED;
            DBG_LOG_TRACE("Send error => SEND_BUS_LOCKED\n");
            DBG_LOG_TRACE("Send state changed => CSMACD_WAIT\n");
            controller->state = CSMACD_WAIT;
            controller->wait = 1+(rand()/1000);
            controller->bus_send = 0;
            controller->bus_recv = 0;
        }
        else
        {
            controller->bus_recv--;
            controller->bus_send++;
            if (controller->bus_recv <= 0)
            {
                controller->state = CSMACD_WAIT;
                DBG_LOG_TRACE("Send state changed => CSMACD_WAIT\n");
                controller->wait = 1;
                if (controller->bus_id >= 0)
                    delete_msg_in_controller(controller,controller->bus_id);
            }
        }
    }
#if defined(_WIN32) || defined(_WIN64)
    pthread_mutex_unlock(&(controller->mutex));
#endif
    return controller->state;
}

int csma_check_send_msgs(CSMACDController_t *controller)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    uint8_t i;
    uint32_t min_ptr;
    if (controller->send_buffer_head < CIRCULAR_BUFFER_SIZE)
        min_ptr = 0;
    else
        min_ptr = controller->send_buffer_head - CIRCULAR_BUFFER_SIZE;
    for (i=0;i < controller->msg_cnt;i++)
    {
        if ( controller->msg_area[i].msg_type == CSMACD_SENDING_MSG )
            if ( (controller->msg_area[i].msg_addr < min_ptr) 
                    || (controller->msg_area[i].msg_attempt <= 0) )
                delete_msg_in_controller(controller,i);
        else
            if ( controller->msg_area[i].msg_addr < min_ptr )
                delete_msg_in_controller(controller,i);
    }
    return 0;
}

#define SIZE_OF_MSG sizeof(MsgDesc_t)
int delete_msg_in_controller(CSMACDController_t *controller, uint8_t i)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    memcpy(
            controller->msg_area+i*SIZE_OF_MSG,
            controller->msg_area+(i+1)*SIZE_OF_MSG,
            (controller->msg_cnt-(i+1))*SIZE_OF_MSG
    );
    controller->msg_cnt--;
    if (controller->bus_id == i)
        controller->bus_id = -1;
    return 0;
}
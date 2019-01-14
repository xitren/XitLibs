/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CSMACD.h
 * Author: xitre
 *
 * Created on 1 сентября 2018 г., 1:33
 */

#ifndef CSMACD_H
#define CSMACD_H

#include <pthread.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_CSMACD_MSGS             255
#define MAX_CSMACD_NODES            255
#define CIRCULAR_BUFFER_SIZE        1024
    
enum State
{ 
    CSMACD_READY, 
    CSMACD_BUS_TRANSMIT, 
    CSMACD_WAIT
};
    
enum ReceiverState
{ 
    CSMACD_RECV_READY, 
    CSMACD_RECV_KEY, 
    CSMACD_RECV_ID, 
    CSMACD_RECV_SIZE1, 
    CSMACD_RECV_SIZE2, 
    CSMACD_RECV_DATA, 
    CSMACD_RECV_CRC1, 
    CSMACD_RECV_CRC2
};

enum GlobalState
{ 
    CSMACD_FIND_NODES, 
    CSMACD_TIMETABLE, 
    CSMACD_REBUILD
};

enum SenderState
{ 
    CSMACD_RECEIVED_MSG, 
    CSMACD_SENDING_MSG
};

typedef uint8_t (*ByteSender_t)(uint8_t output);  

typedef struct _tagMsgDesc_t
{
    uint32_t                        msg_addr;
    size_t                          msg_size;
    uint8_t                         msg_type;
    uint8_t                         msg_attempt;
} MsgDesc_t;

typedef struct _tagNodeDesc_t
{
    char                            node_name[10];
    uint8_t                         node_crc;
} NodeDesc_t;

typedef struct _tagCSMACDController_t
{
    MsgDesc_t                       msg_area[MAX_CSMACD_MSGS];
    uint8_t                         msg_cnt;
    NodeDesc_t                      nodes_area[MAX_CSMACD_NODES];
    uint8_t                         nodes_cnt;
    uint8_t                         nodes_crc;
#if defined(_WIN32) || defined(_WIN64)
    pthread_mutex_t                 mutex;
#endif
    uint8_t                         no_bytes_cnt;
    uint8_t                         recv_state;
    uint16_t                        recv_data;
    uint16_t                        recv_data_s;
    uint16_t                        recv_addr;
    uint8_t                         recv_buffer[CIRCULAR_BUFFER_SIZE];
    uint16_t                        recv_buffer_head;
    uint8_t                         send_buffer[CIRCULAR_BUFFER_SIZE];
    uint16_t                        send_buffer_head;
    uint8_t                         bus_send;
    size_t                          bus_recv;
    int                             bus_id;
    uint8_t                         state;
    uint8_t                         error_state;
    uint8_t                         wait;
    ByteSender_t                    sender;
} CSMACDController_t;  

void csma_clock_cycle(CSMACDController_t *controller);
void csma_init(CSMACDController_t *controller, ByteSender_t func);
uint16_t csma_main_cycle(CSMACDController_t *controller,
                            uint8_t *id, uint8_t *data);
int csma_receiver(CSMACDController_t *controller, uint8_t byte);
int csma_sender(CSMACDController_t *controller);
uint16_t PacketizeToSend(CSMACDController_t *controller,
            uint8_t *bytes,const uint8_t id,const uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* CSMACD_H */


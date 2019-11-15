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
#include "CRC16ANSI.h"

/* Private constants ---------------------------------------------------------*/
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
	uint16_t CRC_MB = 0xFFFF;
	uint32_t DATA = ptr;
	uint16_t N = size;
	uint16_t CRC_MB_other = 0;
	uint16_t SIZE = 0;
	uint16_t N_d = 0;
	uint8_t item;
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
	SIZE = (item = controller->recv_buffer[(DATA++) % CIRCULAR_BUFFER_SIZE]) << 8;
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (item)];
	SIZE += (item = controller->recv_buffer[(DATA++) % CIRCULAR_BUFFER_SIZE]);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (item)];
	while (N--)
	{
		data[N_d++] = (item = controller->recv_buffer[(DATA++) % CIRCULAR_BUFFER_SIZE]);
		CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (item)];
	}
	CRC_MB_other = (item = controller->recv_buffer[(DATA++) % CIRCULAR_BUFFER_SIZE]) << 8;
	CRC_MB_other += (item = controller->recv_buffer[(DATA++) % CIRCULAR_BUFFER_SIZE]);
	if (CRC_MB != CRC_MB_other)
	{
		DBG_LOG_ERROR("Error CRC %04X <> %04X\n", CRC_MB, CRC_MB_other);
		return 0;
	}
	DBG_LOG_TRACE("Received message from buffer\n");
	return SIZE;
}

uint16_t PacketizeToSend(CSMACDController_t *controller,
		uint8_t *bytes, const uint8_t id, const uint16_t size)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	uint16_t CRC_MB = 0xFFFF;
	uint8_t *DATA = bytes;
	uint16_t N = size;
	//    DATA = bytes;

	if (bytes == NULL)
		return 0;
	if (size == 0)
		return 0;
	if (controller->msg_cnt >= MAX_CSMACD_MSGS)
		return 0;
	controller->msg_area[controller->msg_cnt].msg_addr =
			(uint32_t) (controller->send_buffer + controller->send_buffer_head);
	DBG_LOG_TRACE(
			"Data in copy 0x%08X <0x%08X[%d]> 0x%08X\n",
			controller->send_buffer,
			controller->send_buffer + controller->send_buffer_head,
			size + 6,
			controller->send_buffer + CIRCULAR_BUFFER_SIZE
			);
	controller->msg_area[controller->msg_cnt].msg_size = size + 6;
	controller->msg_area[controller->msg_cnt].msg_type = CSMACD_SENDING_MSG;
	controller->msg_area[controller->msg_cnt].msg_attempt = MAX_ATTEMPT;
	controller->msg_cnt++;
	controller->send_buffer[(controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE]
			= MSG_HEADER;
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^
			(MSG_HEADER)];
	controller->send_buffer[(controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE]
			= id;
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^
			(id)];
	controller->send_buffer[(controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE]
			= (size >> 8) & 0xFF;
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^
			((size >> 8) & 0xFF)];
	controller->send_buffer[(controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE]
			= size & 0xFF;
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^
			(size & 0xFF)];
	while (N--)
	{
		controller->send_buffer[(controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE]
				= (*DATA);
		CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^
				(*DATA++)];
	}
	controller->send_buffer[(controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE]
			= (CRC_MB >> 8) & 0xFF;
	controller->send_buffer[(controller->send_buffer_head++) % CIRCULAR_BUFFER_SIZE]
			= CRC_MB & 0xFF;
	return (size) + 6;
}

void csma_clock_cycle(CSMACDController_t *controller)
{
	//    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
	//            __LINE__, __FILE__, __func__);
	controller->no_bytes_cnt++;
	if ((controller->recv_state != CSMACD_RECV_READY)
			&& (controller->no_bytes_cnt > 3))
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
	return;
}

void csma_init(CSMACDController_t *controller, ByteSender_t func, uint8_t *id)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	memset(controller, 0, sizeof (CSMACDController_t));
	controller->node_id = *id;
	controller->sender = func;
	controller->state = CSMACD_READY;
	controller->recv_state = CSMACD_RECV_READY;
	return;
}

uint16_t csma_main_cycle(CSMACDController_t *controller,
		uint8_t *id, uint8_t *data)
{
	uint8_t i;
	uint16_t size;
	csma_check_send_msgs(controller);
	for (i = 0; i < controller->msg_cnt; i++)
	{
		if (controller->msg_area[i].msg_type == CSMACD_RECEIVED_MSG)
		{
			DBG_LOG_TRACE("Found CSMACD_RECEIVED_MSG i[%d]\n", i);
			size = ParseFromRecv(
					controller,
					controller->msg_area[i].msg_addr,
					controller->msg_area[i].msg_size,
					id,
					data
					);
			DBG_LOG_TRACE("Delete MSG\n");
			delete_msg_in_controller(controller, i);
			return size;
		}
	}
	return 0;
}

uint16_t csma_get_msg_to_transmitte(CSMACDController_t *controller,
		uint8_t *id, uint8_t *data)
{
	uint8_t i = *id;
	uint16_t size, j;
	uint32_t buffer_head;
	csma_check_send_msgs(controller);
	for (i = 0; i < controller->msg_cnt; i++)
	{
		if (controller->msg_area[i].msg_type == CSMACD_SENDING_MSG)
		{
			DBG_LOG_TRACE("Found CSMACD_SENDING_MSG i[%d]\n", i);
			buffer_head = (controller->msg_area[i].msg_addr
					- (uint32_t) controller->send_buffer);
			size = controller->msg_area[i].msg_size;
			DBG_LOG_TRACE(
					"Data out copy 0x%08X <0x%08X[%d]> 0x%08X\n",
					controller->send_buffer,
					controller->send_buffer + buffer_head,
					size,
					controller->send_buffer + CIRCULAR_BUFFER_SIZE
					);
			for (j = 0; j < size; j++)
			{
				data[j] = controller->send_buffer
						[(buffer_head + j) % CIRCULAR_BUFFER_SIZE];
			}
			DBG_LOG_TRACE("Delete MSG\n");
			delete_msg_in_controller(controller, i);
			return size;
		}
	}
	return 0;
}

int csma_receiver(CSMACDController_t *controller, uint8_t byte)
{
	//    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
	//            __LINE__, __FILE__, __func__);
	controller->no_bytes_cnt = 0;
	switch (controller->recv_state)
	{
		case CSMACD_RECV_READY:
			if (byte == MSG_HEADER)
			{
				//                DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_KEY\n");
				controller->recv_state = CSMACD_RECV_KEY;
				controller->recv_addr = controller->recv_buffer_head;
				controller->msg_loose = 0;
			}
			break;
		case CSMACD_RECV_KEY:
			//            DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_ID\n");
			controller->recv_state = CSMACD_RECV_ID;
			if (byte != controller->node_id)
			{
				controller->recv_state = CSMACD_RECV_READY;
				controller->msg_loose = 1;
			}
			break;
		case CSMACD_RECV_ID:
			//            DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_SIZE1\n");
			controller->recv_state = CSMACD_RECV_SIZE1;
			controller->recv_data = (uint16_t) byte << 8;
			break;
		case CSMACD_RECV_SIZE1:
			//            DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_DATA\n");
			controller->recv_state = CSMACD_RECV_DATA;
			controller->recv_data += byte;
			controller->recv_data_s = controller->recv_data;
			//            DBG_LOG_TRACE("Receive counter %d\n", controller->recv_data_s);
			break;
		case CSMACD_RECV_DATA:
			controller->recv_data--;
			if (controller->recv_data <= 0)
			{
				//                DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_CRC1\n");
				controller->recv_state = CSMACD_RECV_CRC1;
			}
			break;
		case CSMACD_RECV_CRC1:
			//            DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_CRC2\n");
			controller->recv_state = CSMACD_RECV_CRC2;
			break;
		case CSMACD_RECV_CRC2:
			//            DBG_LOG_TRACE("Recv state changed => CSMACD_RECV_READY\n");
			controller->recv_state = CSMACD_RECV_READY;
			controller->msg_area[controller->msg_cnt].msg_addr =
					controller->recv_buffer_head -
					(6 + controller->recv_data_s - 1);
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
			return controller->error_state = RECEIVE_STATE_ERROR;
	}

	controller->recv_buffer[(controller->recv_buffer_head++) % CIRCULAR_BUFFER_SIZE]
			= byte;
	return 0;
}

int csma_sender(CSMACDController_t *controller)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	uint8_t i;
	if (controller->state == CSMACD_READY)
	{
		csma_check_send_msgs(controller);
		for (i = 0; i < controller->msg_cnt; i++)
		{
			if (controller->msg_area[i].msg_type == CSMACD_SENDING_MSG)
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
		uint8_t send_byte = controller->send_buffer[(controller->bus_send) % CIRCULAR_BUFFER_SIZE];
		DBG_LOG_TRACE("%02X\n ", send_byte);
		// Transmit
		uint8_t recv_byte = controller->sender(send_byte);
		// Receive
		if (send_byte != recv_byte)
		{
			controller->error_state = SEND_BUS_LOCKED;
			DBG_LOG_TRACE("Send error => SEND_BUS_LOCKED\n");
			DBG_LOG_TRACE("Send state changed => CSMACD_WAIT\n");
			controller->state = CSMACD_WAIT;
			controller->wait = 1 + (rand() / 1000);
			controller->bus_send = 0;
			controller->bus_recv = 0;
		} else
		{
			controller->bus_recv--;
			controller->bus_send++;
			if (controller->bus_recv <= 0)
			{
				controller->state = CSMACD_WAIT;
				DBG_LOG_TRACE("Send state changed => CSMACD_WAIT\n");
				controller->wait = 1;
				if (controller->bus_id >= 0)
					delete_msg_in_controller(controller, controller->bus_id);
			}
		}
	}
	return controller->state;
}

int csma_check_send_msgs(CSMACDController_t *controller)
{
	//    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
	//            __LINE__, __FILE__, __func__);
	uint8_t i;
	uint32_t min_ptr;
	if (controller->send_buffer_head < CIRCULAR_BUFFER_SIZE)
		min_ptr = 0;
	else
		min_ptr = controller->send_buffer_head - CIRCULAR_BUFFER_SIZE;
	for (i = 0; i < controller->msg_cnt; i++)
	{
		if (controller->msg_area[i].msg_type == CSMACD_SENDING_MSG)
		{
			if ((controller->msg_area[i].msg_addr < min_ptr)
					|| (controller->msg_area[i].msg_attempt <= 0))
				delete_msg_in_controller(controller, i);
			else
				if (controller->msg_area[i].msg_addr < min_ptr)
				delete_msg_in_controller(controller, i);
		} else
		{
		}
	}
	return 0;
}

#define SIZE_OF_MSG sizeof(MsgDesc_t)

int delete_msg_in_controller(CSMACDController_t *controller, uint8_t i)
{
	DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
			__LINE__, __FILE__, __func__);
	memcpy(
			controller->msg_area + i * SIZE_OF_MSG,
			controller->msg_area + (i + 1) * SIZE_OF_MSG,
			(controller->msg_cnt - (i + 1)) * SIZE_OF_MSG
			);
	controller->msg_cnt--;
	if (controller->bus_id == i)
		controller->bus_id = -1;
	return 0;
}
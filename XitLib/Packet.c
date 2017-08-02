
/* Local headers -------------------------------------------------------------*/
#include "CRC16ANSI.h"
#include "Packet.h"
#include "LogModule.h"
#include <stdio.h>
#include <string.h>
/*============================================================================*/

/* Defines -------------------------------------------------------------------*/
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
char pocket_buffer[STRING_SIZE];
uint32_t PRxCnt = 0;
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
int AddToPocketReceive(char str)
{
    if (PRxCnt < STRING_SIZE)
        pocket_buffer[PRxCnt++] = str;
    return 0;
}

int ClearPocketBuffer()
{
    PRxCnt = 0;
    return 0;
}

char* GetPocketBuffer(unsigned char *size)
{
    if ((size == NULL))
    {
        DBG_LOG_ERROR("GetPocketBuffer argument is NULL\n");
        return 0;
    }
    *size = PRxCnt;
    pocket_buffer[PRxCnt] = '\0';
    PRxCnt = 0;
    return pocket_buffer;
}

uint16_t Packetize(uint8_t *bytes,const uint16_t size, const uint16_t buffer_size)
{
    int i;
    if ((bytes == NULL))
    {
        DBG_LOG_ERROR("Packetize argument is NULL\n");
        return 0;
    }
    if (size == 0)
        return 0;
    if (buffer_size > ((size)+22))
        return 0;
    for (i=(size-1);i >= 3;i-=4)
    {
        bytes[i+9] = bytes[i-3];
        bytes[i+8] = bytes[i-2];
        bytes[i+7] = bytes[i-1];
        bytes[i+6] = bytes[i];
    }
    bytes[0] = 1;
    bytes[1] = 28;
    bytes[2] = 32;
    bytes[3] = bytes[9];
    bytes[4] = bytes[10];
    bytes[5] = bytes[11];
    bytes[6] = bytes[12];
    bytes[7] = ((size)/256)&255;
    bytes[8] = (size)&255;
    uint16_t crc = CRC16ANSI(bytes,(size)+9); 
    bytes[(size)+9] = ((crc)/256)&255;
    bytes[(size)+10] = (crc)&255;
    bytes[(size)+11] = 1;
    bytes[(size)+12] = 28;
    bytes[(size)+13] = 64;
    bytes[(size)+14] = 0;
    bytes[(size)+15] = 0;
    bytes[(size)+16] = 0;
    bytes[(size)+17] = 0;
    bytes[(size)+18] = 0;
    bytes[(size)+19] = 0;
    crc = CRC16ANSI(bytes+(size)+11,9); 
    bytes[(size)+20] = ((crc)/256)&255;
    bytes[(size)+21] = (crc)&255;
    return (size)+22;
}
uint16_t DePacketize(uint8_t *bytes,const uint16_t size)
{
    if ((bytes == NULL))
    {
        DBG_LOG_ERROR("DePacketize argument is NULL\n");
        return 0;
    }
    if (size <= 11)
        return 0;
    uint16_t _crc = (bytes[(size)-2] << 8) + bytes[(size)-1];
    if (_crc != CRC16ANSI(bytes,size-2)) 
        return 0;
    uint16_t _size = (bytes[7] << 8) + bytes[8];
    if (_size != ((size)-11)) 
        return 0;
    uint16_t i;
    for (i=9;i < (_size-2);i+=4)
    {
        bytes[i-9] = bytes[i+3];
        bytes[i-8] = bytes[i+2];
        bytes[i-7] = bytes[i+1];
        bytes[i-6] = bytes[i];
    }
    for (i=_size;i < (size);i++)
        bytes[i] = 0;
    return (size)-11;
}
/*============================================================================*/

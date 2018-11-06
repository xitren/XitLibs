// ----------------------------------------------------------------------------
//
// StreamDataRecorder.c - Recorder to store and process stream data with speed
//                          more than 20 milliseconds.
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include "StreamDataRecorder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  //вызов функции asctime()
#include <math.h>
#include "DistCalc.h"
#include "LogModule.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
int32_t ADC_records[BUFFER_SAMPLE_SIZE][BUFFER_1ST_MAX];
int32_t Data_samples[BUFFER_SAMPLE_SIZE][BUFFER_2ND_MAX];
int32_t EEG_history[EEG_HISTORY_SIZE];
uint32_t history_cnt = 0;
uint32_t samples_cnt = 0;
//uint32_t samples_nmbr = 0;
uint32_t readed_cnt = 0;
uint32_t sample_frequency = 250;
uint32_t signal_amplitude[BUFFER_SAMPLE_SIZE-1] = 
                                    {10,100,1000,10000,1000,100,10};
uint32_t noise_amplitude[BUFFER_SAMPLE_SIZE-1] = 
                                    {100,100,100,100,100,100,100};
uint32_t power_amplitude[BUFFER_SAMPLE_SIZE-1] = 
                                    {100,1000,10000,1000,1000,1000,1000};
uint32_t signal_frequency[BUFFER_SAMPLE_SIZE-1] = {10,20,30,40,50,60,70};
uint8_t signal_type = 0;
//uint8_t path_eeg_arg_buf[5000];
FILE *fp_rec;
uint32_t rec_cnt = 0;
/*============================================================================*/

/* Private constants ---------------------------------------------------------*/
const double TwoPi = 6.283185307179586;
char *path_ext_eeg="EEGSETTOEXTMEM";
/*============================================================================*/

/* Private function prototypes -----------------------------------------------*/
int32_t GetMiddleADC(uint8_t _channel);
void EEG_unreaded_dump(void);
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
#ifdef EXTMEMSERVER
    int EEGPutExtMem(ParameterList_t *TempParam)
    {
        int  ret_val = 0;
        uint32_t i,j,k;
        uint32_t _sizep;
        uint32_t _part[EXT_EEG_MAX_COUNT];
        char tempbuff[4];
        uint32_t *_ptr[EXT_EEG_MAX_COUNT];
        uint32_t _size[EXT_EEG_MAX_COUNT];
        uint32_t *load_ptr = scratch_buf.p;

        #ifdef DEBUG
           printf("--//internal//-- Into EEGPutExtMem.\r\n\r");
        #endif
        AddToTransmit("<EEGEXTMEMSET>\r\n\r");
        /* First check to see if the parameters required for the execution of*/
        /* this function appear to be semi-valid.                            */
        if ((TempParam) && (scratch_buf.len > 0))
        {
            _sizep = scratch_buf.len/4;
            printf("--//internal//-- size of load %d.\r\n\r",_sizep);
            if (_sizep > 0)
            {
                for (j=0;j<_sizep;j++)
                {
                    _part[j] = *(load_ptr+j);
                    _ptr[j] = (uint32_t *)GetPointer(_part[j]);
                    _size[j] = GetSize(_part[j]);
                }
                Clear();
                printf("--//internal//-- Previous EEG was cleared.\r\n\r");
                for (j=0;j<_sizep;j++)
                {
                    uint32_t cnt = _size[j] / 4;
                    int *ptr;
                    for (ptr=_ptr[j];ptr<(_ptr[j]+cnt);)
                    {
                        for(k=0;k<BUFFER_SAMPLE_SIZE;k++)
                        {
                            Data_samples[k][samples_cnt%BUFFER_2ND_MAX] = 
                                                                       *(ptr++);
                        }
                        samples_cnt++;
                        if ((samples_cnt - readed_cnt) > BUFFER_2ND_MAX)
                            readed_cnt = samples_cnt - BUFFER_2ND_MAX;
                    }
                }
                EEG_unreaded_dump();            
            }
        }
        else
        {
            /* One or more of the necessary parameters are invalid.           */
            ret_val = INVALID_PARAMETERS_ERROR;
            AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
            #ifdef DEBUG
               printf("--//internal//--  Invalid parameters.\r\n\r");
            #endif
        }
        AddToTransmit("</EEGEXTMEMSET>\r\n\r");

        return(ret_val);
    }
#else
#ifdef CPU
    int MakeEEGFromFile(char *filename)
    {
        char ch;
        int i,j,sd[8];
        int ret;
        int byN = 64;
        FILE *fp;
        int32_t bufsa[4096];
        int intextid = 2;
        uint32_t history_eeg[1000];
        uint32_t history_eeg_cnt = 0;
        uint32_t history_eeg_ext[1000];
        uint32_t history_eeg_cnt_ext = 0;
        if ((filename == NULL))
        {
            DBG_LOG_ERROR("MakeEEGFromFile argument is NULL\n");
            return 0;
        }

        fp = fopen(filename,"r"); // read mode

        if( fp == NULL )
        {
           DBG_LOG_ERROR("Error while opening the file eeg.\n");
           exit(EXIT_FAILURE);
        }

        ClearExtMem();
        for(i=0;i < 41024;i++)
        {
            fscanf(fp,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n\r",
                    sd,sd+1,sd+2,sd+3,sd+4,sd+5,sd+6,sd+7);
            for(j=0;j<BUFFER_SAMPLE_SIZE;j++)
                Data_samples[j][samples_cnt%BUFFER_2ND_MAX] = sd[j];
            samples_cnt++;
            if ((samples_cnt - readed_cnt) > BUFFER_2ND_MAX)
                readed_cnt = samples_cnt - BUFFER_2ND_MAX;
            if (GetCnt() >= byN)
            {
                int hlen = GetDataReadyCnt(byN,bufsa);
                hlen*=4;
                if (ret < 0)
                {       
                    return -1;
                }
            }
        }
        for(i=0;i < history_eeg_cnt;i++)
        {
            //history_eeg_ext[history_eeg_cnt_ext++] = GetMemExtByInt(history_eeg[i]);
        }
        //printf("---------------> Setted ext history\r\n\r");
        //EEGPutExtMemReq((uint32_t*)history_eeg_ext,history_eeg_cnt_ext);
        //printf("---------------> EEG reconstruction\r\n\r");

        fclose(fp);
        return 0;
    }
    int WorkEEGFromFile(char *filename,StreamDataCallback_t _callback)
    {
        char ch;
        int i,j,sd[8];
        int ret;
        int byN = 64;
        FILE *fp;
        int32_t bufsa[4096];
        int intextid = 2;
        uint32_t history_eeg[1000];
        uint32_t history_eeg_cnt = 0;
        uint32_t history_eeg_ext[1000];
        uint32_t history_eeg_cnt_ext = 0;
        if ((filename == NULL))
        {
            DBG_LOG_ERROR("WorkEEGFromFile argument is NULL\n");
            return 0;
        }

        fp = fopen(filename,"r"); // read mode

        if( fp == NULL )
        {
           DBG_LOG_ERROR("Error while opening the file eeg.\n");
           exit(EXIT_FAILURE);
        }

        for(i=0;i < 41024;i++)
        {
            fscanf(fp,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n\r",
                    sd,sd+1,sd+2,sd+3,sd+4,sd+5,sd+6,sd+7);
//            printf("%09d\t%09d\t%09d\t%09d\t%09d\t%09d\t%09d\t%09d\r\n\r",
//                    *sd,*(sd+1),*(sd+2),*(sd+3),*(sd+4),*(sd+5),*(sd+6),*(sd+7));
            for(j=0;j<BUFFER_SAMPLE_SIZE;j++)
                Data_samples[j][samples_cnt%BUFFER_2ND_MAX] = sd[j];
            samples_cnt++;
            if ((samples_cnt - readed_cnt) > BUFFER_2ND_MAX)
                readed_cnt = samples_cnt - BUFFER_2ND_MAX;
            if (GetCnt() >= byN)
            {
                int hlen = GetDataReadyCnt(byN,bufsa);
                (*_callback)(bufsa, hlen);
            }
        }
        
        fclose(fp);
        return 0;
    }
#endif
#endif
int GetLastBlock(ParameterList_t *TempParam)
{
    //time_t seconds = time(NULL);
    //struct tm* timeinfo = localtime(&seconds);
    int  ret_val = 0;
    char buffer[STRING_SIZE];
    int i,l,k=0; //samples_nmbr
    uint32_t cnt = samples_cnt-readed_cnt;
    if ((TempParam == NULL))
    {
        DBG_LOG_ERROR("GetLastBlock argument is NULL\n");
        return 0;
    }
    if ((cnt) > ReadMem(REG_EEG_PocketSize))
		cnt = ReadMem(REG_EEG_PocketSize);
    k=samples_cnt-cnt;

    DBG_LOG_DEBUG("Into GetLastBlock.\n");
    content_type = COAP_CONTENTTYPE_APPLICATION_JSON;
    AddToTransmit("{\n \"DATABLOCK\": [\n");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    l = GetDataReadyCnt(ReadMem(REG_EEG_PocketSize),(int32_t *)scratch_raw);
    if (l > 0)
    {
        for (i=0;(i < l) && ((i+7) < l);i+=8)
        {
            if(i != 0)
            {
                AddToTransmit(",\n");
            }
            snprintf(buffer,STRING_SIZE,"  {\"sample\": %d, \"data\": [",
                                                                    k++);
            AddToTransmit(buffer);
            snprintf(buffer,STRING_SIZE,"%d, %d, " 
                                        ,((int*)scratch_raw)[i]
                                        ,((int*)scratch_raw)[i+1]);
            AddToTransmit(buffer);
            snprintf(buffer,STRING_SIZE,"%d, %d, " 
                                        ,((int*)scratch_raw)[i+2]
                                        ,((int*)scratch_raw)[i+3]);
            AddToTransmit(buffer);
            snprintf(buffer,STRING_SIZE,"%d, %d, " 
                                        ,((int*)scratch_raw)[i+4]
                                        ,((int*)scratch_raw)[i+5]);
            AddToTransmit(buffer);
            snprintf(buffer,STRING_SIZE,"%d, %d]}" 
                                        ,((int*)scratch_raw)[i+6]
                                        ,((int*)scratch_raw)[i+7]);
            AddToTransmit(buffer);
        }
    }
    else
    {
        AddToTransmit("</NO_DATA>\r\n\r");
    }
    AddToTransmit("\n ]\n}\n");

    return(ret_val);
}

int GetConcreteBlock(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int i,l,k=0; //samples_nmbr
    int  Number;
    int  Size;
    char buffer[STRING_SIZE];
    if ((TempParam == NULL))
    {
        DBG_LOG_ERROR("GetConcreteBlock argument is NULL\n");
        return 0;
    }
    
    DBG_LOG_DEBUG("Into GetConcreteBlock.\n");
    content_type = COAP_CONTENTTYPE_APPLICATION_JSON;
    AddToTransmit("{\n \"DATABLOCK\": [\n");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 3))
    {
       for (i=1;i<TempParam->NumberofParameters;i+=2)
       {
          if (!strcmp(TempParam->Params[i-1].strParam,"number"))
          {
             Number = (unsigned int)(TempParam->Params[i].intParam);
          }
          if (!strcmp(TempParam->Params[i-1].strParam,"size"))
          {
             Size = (unsigned int)(TempParam->Params[i].intParam);
          }
       }
       
       k=Number;
       DBG_LOG_TRACE("Current sample %d.",samples_cnt);
       if (Size > 0)
       {
        l=GetDataPtrCnt(Number,Size,(int32_t *)scratch_raw);
        if (l > 0)
        {
            for (i=0;(i < l) && ((i+7) < l);i+=8)
            {
                if(i != 0)
                {
                    AddToTransmit(",\n");
                }
                snprintf(buffer,STRING_SIZE,"  {\"sample\": %d, \"data\": [",
                                                                        k++);
                AddToTransmit(buffer);
                snprintf(buffer,STRING_SIZE,"%d, %d, " 
                                            ,((int*)scratch_raw)[i]
                                            ,((int*)scratch_raw)[i+1]);
                AddToTransmit(buffer);
                snprintf(buffer,STRING_SIZE,"%d, %d, " 
                                            ,((int*)scratch_raw)[i+2]
                                            ,((int*)scratch_raw)[i+3]);
                AddToTransmit(buffer);
                snprintf(buffer,STRING_SIZE,"%d, %d, " 
                                            ,((int*)scratch_raw)[i+4]
                                            ,((int*)scratch_raw)[i+5]);
                AddToTransmit(buffer);
                snprintf(buffer,STRING_SIZE,"%d, %d]}" 
                                            ,((int*)scratch_raw)[i+6]
                                            ,((int*)scratch_raw)[i+7]);
                AddToTransmit(buffer);
            }
        }
        else
        {
            AddToTransmit("</NO_DATA>\r\n\r");
        }
       }
        AddToTransmit("\n ]\n}\n");
        DBG_LOG_TRACE("Current sample - %d.\n",samples_cnt);
    }
    else
    {
         /* One or more of the necessary parameters are invalid.           */
         ret_val = INVALID_PARAMETERS_ERROR;
         AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
         DBG_LOG_WARNING("Invalid parameters.\n");
    }
    return(ret_val);
}

uint32_t GetDataPtrCnt(int32_t _pointer,int32_t _size,int32_t *_buffer)
{
    DBG_LOG_TRACE("Into GetDataPtrCnt.\n");
    if ((_buffer == NULL))
    {
        DBG_LOG_ERROR("GetDataPtrCnt argument is NULL\n");
        return 0;
    }
    int i,j,ptr=0;
    int cnt = (int)(samples_cnt - BUFFER_2ND_MAX);

    int temp2=(int)_pointer;

    if (cnt > temp2)
    {
        DBG_LOG_WARNING("Clear data query.\r\n\r");
    return 0;
    }
    if ((samples_cnt - _pointer) < _size)
    {
            DBG_LOG_WARNING("have data less than query.\r\n\r");
            return 0;
    }
            for(i=(_pointer);(i < samples_cnt) && (ptr < (_size*BUFFER_SAMPLE_SIZE));i++)
                for(j=0;j<BUFFER_SAMPLE_SIZE;j++)
                    _buffer[ptr++] = Data_samples[j][i%BUFFER_2ND_MAX];
    return ptr;
}

void EEG_unreaded_dump(void)
{
    DBG_LOG_TRACE("Into EEG_unreaded_dump.\n");
    int i,j;
    printf("\r\n\r");
    for(i=(readed_cnt);i<samples_cnt;i++)
    {
            for(j=0;j<BUFFER_SAMPLE_SIZE;j++)
                    printf("%08X ",Data_samples[j][i%BUFFER_2ND_MAX]);
            printf("\n");
    }
}
int EEGPutExtMemReq(uint32_t *data, uint32_t datalen)
{
    DBG_LOG_TRACE("Into EEGPutExtMemReq.\n");
    if ((data == NULL))
    {
        DBG_LOG_ERROR("EEGPutExtMemReq argument is NULL\n");
        return 0;
    }
//    uint8_t *pntr = path_eeg_arg_buf;
//    uint32_t i;
//    int rc;
//    
//    #ifdef DEBUG
//       printf("--//internal//-- Into EEGPutExtMemReq.\r\n\r");
//    #endif
//
//    pktlen = sizeof(buf);
//    opt_path.num = COAP_OPTION_URI_PATH;
//    opt_path.buf.p = path_ext_eeg;
//    opt_path.buf.len = strlen(path_ext_eeg);
//    pntr += sprintf((char *)pntr,"size=%d",datalen);
//    coap_make_msg(&scratch_buf, &pkt, &opt_path, 0, 0,
//                       (uint8_t *)data, datalen*4, 
//                       0, id_out++, 0, 0,
//                       COAP_METHOD_PUT, 
//                       COAP_CONTENTTYPE_NONE);
//    #ifdef DEBUG
//        printf("---------------> CoAP packet start.\r\n\r");
//        coap_dumpPacket(&pkt);
//        printf("---------------> CoAP packet end.\r\n\r");
//    #endif
//    if (!(rc = coap_build(buf, &pktlen, &pkt, NULL, NULL)))
//        Transfer((uint8_t*)buf,pktlen,"eeg");
    return 0;
}
void EEG_dump(const uint8_t *buf, uint32_t buflen)
{
    DBG_LOG_TRACE("Into EEG_dump.\n");
    uint32_t g=1;
    if ((buf == NULL))
    {
        DBG_LOG_ERROR("EEG_dump argument is NULL\n");
        return;
    }
    while(buflen--)
    {
        printf("%02X", *buf++);
        if (!((g)%4))
            printf(" ");
        if (!((g++)%32))
            printf("\r\n\r");
    }
}
int32_t GetMiddleADC(uint8_t _channel)
{
    DBG_LOG_TRACE("Into GetMiddleADC.\n");
    int i,sum=0,cnt;
    cnt = ADC_records[_channel][0];
    ADC_records[_channel][0] = 0;
    for(i=1;i<cnt;i++)
            sum += ADC_records[_channel][i];
    return sum/cnt;
}
uint8_t EEGTestInit(uint32_t _signal_amplitude[7],uint32_t _signal_frequency[7])
{
    DBG_LOG_TRACE("Into EEGTestInit.\n");
    int i;
    if ((_signal_amplitude == NULL) && (_signal_frequency == NULL))
    {
        DBG_LOG_ERROR("EEGTestInit argument is NULL\n");
        return 0;
    }
    for(i=0;i<7;i++)
    {
        signal_amplitude[i] = _signal_amplitude[i];
        signal_frequency[i] = _signal_frequency[i];
    }
    return 0;
}
uint8_t EEGRecorderInit(uint8_t _signal_type,uint32_t _sample_frequency)
{
    DBG_LOG_TRACE("Into EEGRecorderInit.\n");
    Clear();
    signal_type = _signal_type;
    sample_frequency = _sample_frequency;
    return 0;
}
uint8_t MakeEEGSample(uint8_t _channel, int32_t _value)
{
    DBG_LOG_TRACE("Into MakeEEGSample.\n");
    if (_channel < BUFFER_SAMPLE_SIZE)
        return 1;
    ADC_records[_channel][(uint32_t)ADC_records[_channel][0]] = _value;
    ADC_records[_channel][0]++;
    return 0;
}
uint32_t AddHistoryExtId(uint32_t _extid)
{
    DBG_LOG_TRACE("Into AddHistoryExtId.\n");
    uint32_t ret = EEG_history[(history_cnt)%EEG_HISTORY_SIZE];
    EEG_history[(history_cnt++)%EEG_HISTORY_SIZE] = _extid;
    return ret;
}
void AddSample()
{
    DBG_LOG_TRACE("Into AddSample.\n");
    int i;
    if (signal_type == 1)
    {
        for(i=0;i<BUFFER_SAMPLE_SIZE;i++)
        {
//        #ifdef CPU
//            Data_samples[i][samples_cnt%BUFFER_2ND_MAX] = GetMiddleADC(i);
//        #else
            uint32_t selAD = (ReadMem(REG_ADC_ORDER) >> (i*4)) & 0x0000000F;
            if (selAD < 8) 
            {
                Data_samples[i][samples_cnt%BUFFER_2ND_MAX] = 
                        ReadMem(REG_ADC_CH1+selAD);
            }
            else if (selAD < 11)
            {
                selAD -= 8;
                Data_samples[i][samples_cnt%BUFFER_2ND_MAX] = 
                        ReadMem(REG_ADC_CHA+selAD);
            }
            else
            {
                Data_samples[i][samples_cnt%BUFFER_2ND_MAX] = 0;
            }
//        #endif
        }
    }
    else if (signal_type == 2)
        for(i=0;i < 4;i++)
            Data_samples[i][samples_cnt%BUFFER_2ND_MAX] = 
                    (int32_t)ReadMem(REG_ACCEL_X+i);
    else if (signal_type == 3)
    {

    }
    else
    {
        double phase = (TwoPi*samples_cnt)/sample_frequency;
        Data_samples[0][samples_cnt%BUFFER_2ND_MAX] = ReadMem(REG_ADC_CHA);
        Data_samples[1][samples_cnt%BUFFER_2ND_MAX] = ReadMem(REG_ADC_CHB);
        for(i=2;i<BUFFER_SAMPLE_SIZE;i++)
            Data_samples[i][samples_cnt%BUFFER_2ND_MAX] 
                                = ((int32_t)
                                    (signal_amplitude[i-1]*
                                         sin(signal_frequency[i-1]*phase)) +
                                    (int32_t)
                                    (power_amplitude[i-1]*sin(0.5*phase)) +
                                    (int32_t)
                                    ((rand()*noise_amplitude[i-1])/RAND_MAX) );
    }

    #ifdef CPU
        if( ReadMem(REG_STREAM_REC) > 0 )
        {
            WriteMem(REG_STREAM_REC,ReadMem(REG_STREAM_REC)-1);
            if( fp_rec == NULL )
            {
                fp_rec = fopen("stream_rec.json","w"); // write mode
                if( fp_rec == NULL )
                {
                    DBG_LOG_ERROR("Error while opening the file json.\r\n\r");
                    exit(EXIT_FAILURE);
                }
                fprintf(fp_rec, "{\n \"DATABLOCK\": [\n");
                rec_cnt = samples_cnt;
            }
            if(rec_cnt != samples_cnt)
            {
                fprintf(fp_rec, ",\n");
            }
            fprintf(fp_rec, "  {\"sample\": %d, \"data\": [",samples_cnt);
            fprintf(fp_rec, "%d, %d, " 
                                ,Data_samples[0][samples_cnt%BUFFER_2ND_MAX]
                                ,Data_samples[1][samples_cnt%BUFFER_2ND_MAX]);
            fprintf(fp_rec, "%d, %d, " 
                                ,Data_samples[2][samples_cnt%BUFFER_2ND_MAX]
                                ,Data_samples[3][samples_cnt%BUFFER_2ND_MAX]);
            fprintf(fp_rec, "%d, %d, " 
                                ,Data_samples[4][samples_cnt%BUFFER_2ND_MAX]
                                ,Data_samples[5][samples_cnt%BUFFER_2ND_MAX]);
            fprintf(fp_rec, "%d, %d]}" 
                                ,Data_samples[6][samples_cnt%BUFFER_2ND_MAX]
                                ,Data_samples[7][samples_cnt%BUFFER_2ND_MAX]);
        }
        else
        {
            if( fp_rec != NULL )
            {
                fprintf(fp_rec, "\n ]\n}\n");
                fclose(fp_rec);
                fp_rec = NULL;
            }
        }
    #endif
    samples_cnt++;
    if ((samples_cnt - readed_cnt) > BUFFER_2ND_MAX)
        readed_cnt = samples_cnt - BUFFER_2ND_MAX;
    return;
}
int GetRecord(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  i,ind_i = -1;
    FILE *fp;
    int num;
    int sizefp;
    int end;
    uint16_t allhash = 0;
    
    #ifdef DEBUG
        DBG_LOG_DEBUG("--//internal//-- Into GetRecord.\r\n\r");
    #endif
    AddToTransmit("<GETRECORD>\r\n\r");
    
    #ifndef MC
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            if (!strcmp(TempParam->Params[i-1].strParam,"part"))
            {
                ind_i = TempParam->Params[i].intParam;
            }
            if (!strcmp(TempParam->Params[i-1].strParam,"size"))
            {
                size_parts = TempParam->Params[i].intParam;
            }
        }

        fp = fopen("stream_rec.json","r"); // read mode
        content_type = COAP_CONTENTTYPE_APPLICATION_JSON;

        if( fp == NULL )
        {
           printf("Error while opening update the file update.\r\n\r");
        }
        else 
        {
            end = 0;
            num = 0;
            DBG_LOG_TRACE("Part %d .\r\n\r",ind_i);
            if (ind_i == -1)
            {
                sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
                DBG_LOG_TRACE("%d readed from file.\n",sizefp);
                printf("%d readed from file.\n",sizefp);
                if (sizefp == 0)
                    return(INVALID_PARAMETERS_ERROR);
                if (sizefp != size_parts)
                    end = 1;
                allhash += CRC16ANSI(&opt_part,sizefp);
                printf("allhash: %X\n",allhash);
                make_part_option(&opt_part,num,COAP_PART_SIZE_1024,end);
                size_parts_cur = sizefp;
                num++;

            }
            else
            {
                while (num <= ind_i)
                {
                    sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
                    DBG_LOG_TRACE("%d readed from file.\n",sizefp);
                    printf("%d readed from file.\n",sizefp);
                    
                    if (sizefp == 0)
                        return(INVALID_PARAMETERS_ERROR);
                    if (sizefp != size_parts)
                    {
                        end = 1;
                    }
                    num++;
                } 
                num--;
                allhash += CRC16ANSI(&opt_part,sizefp);
                printf("allhash: %X\n",allhash);
                make_part_option(&opt_part,num,COAP_PART_SIZE_1024,end);
                size_parts_cur = sizefp;
            }
            fclose(fp);
        }
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        //AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
        DBG_LOG_WARNING("Invalid parametest.\n");
    }
    #endif

    AddToTransmit("</UPDATE>\r\n\r");
    DBG_LOG_DEBUG("Into END of Update.\n");
    return(ret_val);
}
uint32_t GetCnt()
{
    //DBG_LOG_TRACE("Into GetCnt.\n");
    return (samples_cnt-readed_cnt); 
}
uint32_t GetSamplesCnt()
{
    DBG_LOG_TRACE("Into GetSamplesCnt.\n");
    return (samples_cnt); 
}
uint32_t GetDataReady(int32_t *_buffer)
{
    DBG_LOG_TRACE("Into GetDataReady.\n");
    if ((_buffer == NULL))
    {
        DBG_LOG_ERROR("GetDataReady argument is NULL\n");
        return 0;
    }
    int i,j,ptr=0;
    uint32_t cnt = (samples_cnt-readed_cnt);
    DBG_LOG_TRACE("Out: cnt+%d+samples_cnt-%d-readed_cnt-%d-\n",cnt,samples_cnt,readed_cnt);
    for(i=(samples_cnt-cnt);i<samples_cnt;i++)
            for(j=0;j<BUFFER_SAMPLE_SIZE;j++)
                    _buffer[ptr++] = Data_samples[j][i%BUFFER_2ND_MAX];
    return ptr;
}
uint32_t GetDataReadyCnt(int32_t _size,int32_t *_buffer)
{
    DBG_LOG_TRACE("Into GetDataReadyCnt.\n");
    if ((_buffer == NULL))
    {
        DBG_LOG_ERROR("GetDataReadyCnt argument is NULL\n");
        return 0;
    }
    int i,j,ptr=0;
    uint32_t cnt = (samples_cnt-readed_cnt);
    DBG_LOG_TRACE("---- Current sample %d\n",samples_cnt);
    DBG_LOG_TRACE("---- Readed sample %d\n",readed_cnt);
    DBG_LOG_TRACE("---- Count no read %d\n",cnt);
    if ((cnt) > _size)
            cnt = _size;
    if ((cnt) < _size)
            return 0;

    for(i=(samples_cnt-cnt);i<samples_cnt;i++)
            for(j=0;j<BUFFER_SAMPLE_SIZE;j++)
                    _buffer[ptr++] = Data_samples[j][i%BUFFER_2ND_MAX];
    readed_cnt = samples_cnt;
    return ptr;
}
void Clear(void)
{
    DBG_LOG_TRACE("Into Clear.\n");
    int i;
    for(i=0;i<EEG_HISTORY_SIZE;i++)
            EEG_history[i] = 0;
    history_cnt = 0;
    for(i=0;i<BUFFER_SAMPLE_SIZE;i++)
            ADC_records[i][0] = 0;
    samples_cnt = 0;
    return;
}
/*============================================================================*/

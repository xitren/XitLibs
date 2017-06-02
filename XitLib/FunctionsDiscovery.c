
/* Local headers -------------------------------------------------------------*/
#include "FunctionsDiscovery.h"
#include "SymbolBuffer.h"
#include "Handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "generatorModule.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
function_node nodes[NODE_MAX];
uint32_t nodes_cnt = 0;
/*============================================================================*/

/* Private constants ---------------------------------------------------------*/
const char *token_well_core="wknown";
const char *path_well_core=".well-known/core";
const char *path_well_core_clb="/CALLBACK/.WELL-KNOWN/CORE";
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
int EEGGetFile(ParameterList_t *TempParam)
    {
        int  ret_val = 0;
        
        if ((TempParam))
        {
            content_type = COAP_CONTENTTYPE_APPLICATION_LINKFORMAT;
        }
        else
        {
        }
       return(ret_val); 
    }
    
   
    
    int EEGGetListFiles(ParameterList_t *TempParam)
    {
        int  ret_val = 0;
        
        if ((TempParam))
        {
            content_type = COAP_CONTENTTYPE_APPLICATION_LINKFORMAT;
        }
        else
        {
        }
       return(ret_val); 
    }
    
    int EEGWriteInFile(ParameterList_t *TempParam)
{
   int  ret_val = 0;
   int  Adress= 60;
   int  Value=1;
   int  i;
   uint32_t res;

   #ifdef DEBUG
      printf("--//internal//-- Into EEGWriteInFile.\r\n\r");
      Log("--//internal//-- Into EEGWriteInFile.\r\n\r");
   #endif
   AddToTransmit("<EEGWRITE>\r\n\r");
   /* First check to see if the parameters required for the execution of*/
   /* this function appear to be semi-valid.                            */
   if ((TempParam))
   {
         res=ReadMem(60);
         #ifdef DEBUG
         printf("Value REG WriteInFile %d",res);
         #endif
         WriteMem(60,Value);
         res=ReadMem(60);
         #ifdef DEBUG
         printf("New value REG WriteInFile %d",res);
         #endif
         AddToTransmit("<WR/>\r\n\r");
         #ifdef DEBUG
            printf("--//internal//-- Mem[%d] setted to %d.\r\n\r",60,Value);
         #endif
        content_type = COAP_CONTENTTYPE_APPLICATION_LINKFORMAT;
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
   AddToTransmit("</EEGWRITE>\r\n\r");

   return(ret_val);
}
    
int QueryNodes(ParameterList_t *TempParam) 
{   //AddCommand("/GET/QUERYNODES", QueryNodes);
    #ifdef DEBUG
      printf("--//internal//-- Into QUERYNodes.\r\n\r");
    #endif 
    int  ret_val = 0;
      
    int i,j,k=0;
    char *strptr;
    char strbuf[80];
    
    memset(strbuf,0,80);
    strptr = (char*)strbuf;
    
    //AddToTransmit("<NODES>\r\n\r");  // "<NODES>\r\n\r"     "{\n \"EEGBLOCK\": [\n"
   /* First check to see if the parameters required for the execution of*/
   /* this function appear to be semi-valid.                            */
   if ((TempParam))
   {
          
    if(nodes_cnt==0) 
    {
       AddToTransmit("<ERROR_NODES_NULL>\r\n\r"); 
    }
    else 
    {
        for (i=0;i < nodes_cnt;i++)
        {
            for (j=0;j < nodes[i].len;j++)
            {
                if((i==nodes_cnt-1)&&(j==nodes[i].len-1))
                {
                    sprintf(strptr,
                        "<coap://%s%s>;if=\"controller\"\n",
                        nodes[i].ip,nodes[i].proto[j].name);
                    AddToTransmit(strptr);
                    break;
                }
            sprintf(strptr,
                        "<coap://%s%s>;if=\"controller\",\n",
                        nodes[i].ip,nodes[i].proto[j].name);
            AddToTransmit(strptr);
            }
        }
    }
    content_type = COAP_CONTENTTYPE_APPLICATION_LINKFORMAT;
   }
   else
   {
        /* One or more of the necessary parameters are invalid.           */

        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        #ifdef DEBUG
           printf("--//internal//--  Invalid param test.\r\n\r");
        #endif
   }
   //AddToTransmit("</NODES>\r\n\r");
     
   return ret_val;
}

void put_node_msg(char *_ip,char *_name)
{
    //char _name_buf[20];
    int ip_id = -1;
    uint32_t name_ptr = 0;
    int i;
    #ifdef DEBUG
        printf("--//internal//-- Into put_node_msg.\r\n\r");
    #endif
    for (i=0;i < nodes_cnt;i++)
    {
        if (!strcmp(_ip,nodes[i].ip))
        {    
            ip_id = i;
            break;
        }        
    }
    if (ip_id < 0)
    {
        if (nodes_cnt < NODE_MAX)
        {
            strncpy(nodes[nodes_cnt].ip,_ip,strlen(_ip));
            ip_id = nodes_cnt;
            nodes_cnt++;
        }
    }
    if (nodes[ip_id].len >= PROTO_MAX)
    {
        return;
    }
    for (name_ptr=1;name_ptr < strlen(_name);name_ptr++) 
        if ((_name[name_ptr-1] == '<') && (_name[name_ptr] == '/'))
        {
            nodes[ip_id].proto[nodes[ip_id].len].len = 0;
            while ((_name[name_ptr] != '>') && (name_ptr < strlen(_name)))
            {
                //printf("%d %d %c %c\n",nodes[ip_id].proto[nodes[ip_id].len].len,name_ptr,_name[name_ptr],'>');
                nodes[ip_id].proto[nodes[ip_id].len].name
                        [nodes[ip_id].proto[nodes[ip_id].len].len++] 
                        = _name[name_ptr];
                name_ptr++;
            }
            nodes[ip_id].proto[nodes[ip_id].len].name
                        [nodes[ip_id].proto[nodes[ip_id].len].len++] 
                        = 0;
//            printf("--//internal//-- %s\r\n\r",
//                    nodes[ip_id].proto[nodes[ip_id].len].name);
            for (i=0;i < (nodes[ip_id].len);i++)
            {
                printf("%s = %s\n",nodes[ip_id].proto[i].name,nodes[ip_id].proto[nodes[ip_id].len].name);
                if (!strcmp(nodes[ip_id].proto[i].name,nodes[ip_id].proto[nodes[ip_id].len].name))
                {
                    break;
                }
            }
            if (i < nodes[ip_id].len)
                continue;
            //printf("%d %d name: %s\n",nodes[i].len,ip_id,_name);
            //strncpy(nodes[ip_id].proto[nodes[ip_id].len].name,_name,strlen(_name));
            nodes[ip_id].proto[nodes[ip_id].len].len = 
                    strlen(nodes[ip_id].proto[nodes[ip_id].len].name);
            nodes[ip_id].len++;
        }
    return;
}
char* get_first_node_by_func(const char *_name)
{
    int i,j;
    #ifdef DEBUG
        printf("--//internal//-- Into get_first_node_by_func.\r\n\r");
    #endif
    for (i=0;i < nodes_cnt;i++)
    {
        for (j=0;j < nodes[i].len;j++)
        {
            if (strcmp(nodes[i].proto[j].name,_name))
            {
                return nodes[i].ip;
            }
        }     
    }
    return 0;
}

/*
int serverIP(char *ServerIP)
{
    int ret_val=0;
    int i,j;
    int found =0;
    char *strptr;
    char strbuf[10000];
    memset(strbuf,0,10000);
    strptr = (char*)strbuf;
    for (i=0;i < nodes_cnt;i++)
    {
        //printf("LENGTH%d\n",nodes[i].len);
        for (j=0;j < nodes[i].len;j++)
        {
            strptr += snprintf(strptr,
                    10000-((int)strptr-(int)strbuf),
                    "<coap://%s%s>;if=\"controller\",\n",
                    nodes[i].ip,nodes[i].proto[j].name);
            if (strcmp(nodes[i].proto[j].name, "/techupdate")==0) {
                ServerIP = nodes[i].ip;
                found =1;
            }
        }     
    }
    *(strptr-2) = 0;
    
    if (found==1) {
        ret_val = 1;
    }
    return ret_val;
}
*/


void print_node_and_func(void)
{
    int i,j;
    char *strptr;
    char strbuf[10000];
    memset(strbuf,0,10000);
    strptr = (char*)strbuf;
    printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
    
    for (i=0;i < nodes_cnt;i++)
    {
        //printf("LENGTH%d\n",nodes[i].len);
        for (j=0;j < nodes[i].len;j++)
        {
            strptr += snprintf(strptr,
                    10000-((int)strptr-(int)strbuf),
                    "<coap://%s%s>;if=\"controller\",\n",
                    nodes[i].ip,nodes[i].proto[j].name);
        }     
    }
    *(strptr-2) = 0;
    printf("%s\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n",strbuf);
    return;
}

void function_beakon(void)
{
    int rc,i;
    #ifdef CPU
    coap_buffer_t tokfb;
    #ifdef DEBUG
        printf("--//internal//-- Into function_beakon.\r\n\r");
    #endif
    pktlen = sizeof(buf);
    opt_path.num = COAP_OPTION_URI_PATH;
    opt_path.buf.len = strlen(path_well_core);
    opt_path.buf.p = (uint8_t*)path_well_core;
    pkt.tok_len = strlen(token_well_core);
    memcpy(pkt.tok_p, token_well_core, pkt.tok_len);
    coap_make_msg(&scratch_buf, &pkt, &opt_path, 0, 0,
                       0, 0, 
                       0, id_out+=5, pkt.tok_p, pkt.tok_len, 
                       COAP_METHOD_GET, 
                       COAP_CONTENTTYPE_NONE);
    if (!(rc = coap_build(buf, &pktlen, &pkt, path_well_core_clb, 0)))
    {
        TransferBand((uint8_t*)buf,pktlen);
    }
/*
    for (i=0;i < nodes_cnt;i++)
    {
        if (nodes[i].len>14)
        {
            printf("Error: nodes_length less PROTO_MAX\n");
            PROTO_MAX=nodes[i].len;
        }
    }
*/
    #endif
return;
}
  
   /* The following function is responsible for Giving current          */
   /* functions. This function returns zero is successful or a negative */
   /* return value if there was an error.                               */
int WELLKnown(ParameterList_t *TempParam)
{
   int  ret_val = 0,i;

    #ifdef DEBUG
        printf("--//internal//-- Into WELLKnown.\r\n\r");
    #endif
    //AddToTransmit("<WELLKNOWN>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        #ifdef DEBUG
           printf("--//internal//--  id %02X %02X\r\n\r",pkt.hdr.id[0], pkt.hdr.id[1]);
        #endif
           //pkt->hdr.t
        for (i=0;i < GetCommandsNumber();i++)
        {
            AddToTransmit(GetCommandLink(i));
            AddToTransmit(",");
        }
        content_type = COAP_CONTENTTYPE_APPLICATION_LINKFORMAT;
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
    //AddToTransmit("</WELLKNOWN>\r\n\r");

    return(ret_val);
}
   /* The following function is responsible for Giving current          */
   /* functions. This function returns zero is successful or a negative */
   /* return value if there was an error.                               */
int CallbackWELLKnown(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  i,ind_i;
    char *ip;

    #ifdef DEBUG
        printf("--//internal//-- Into CallbackWELLKnown.\r\n\r");
    #endif
    //AddToTransmit("<CALLBACKWELLKNOWN>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            if (!strcmp(TempParam->Params[i-1].strParam,"ip"))
            {
                ip = (char*)(TempParam->Params[i].strParam);
                ind_i = i+1;
            }
        }
        for (i=ind_i;i < TempParam->NumberofParameters; i++)
        {
            put_node_msg(ip,TempParam->Params[i].strParam);
        }
        scratch_buf.p[scratch_buf.len] = 0;
        put_node_msg(ip,scratch_buf.p);
        #ifdef DEBUG
            print_node_and_func();
        #endif
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        //AddToTransmit("<INVALID_PARAMETERS_ERROR>\r\n\r");
        #ifdef DEBUG
            printf("--//internal//--  Invalid parametest.\r\n\r");
        #endif
    }
    //AddToTransmit("</CALLBACKWELLKNOWN>\r\n\r");

    #ifdef DEBUG
        printf("--//internal//-- Into END of CallbackWELLKnown.\r\n\r");
    #endif
    return(ret_val);
}
/*============================================================================*/
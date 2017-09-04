// ----------------------------------------------------------------------------
//
// FunctionsDiscovery.c - REST API for .WELL-KNOWN/CORE
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FunctionsDiscovery.h"
#include "Handler.h"
#include "generatorModule.h"
#include "LogModule.h"
#include "UpdateModule.h"
#include "array.h"
#include "umm_malloc.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
static Array *NodesArray;
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
    
    return(ret_val); 
}

int EEGGetListFiles(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    
    return(ret_val); 
}

int EEGWriteInFile(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  Adress = 60;
    int  Value = 1;
    uint32_t res;
   
    DBG_LOG_DEBUG("Into EEGWriteInFile.\n");
    AddToTransmit("<EEGWRITE>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        WriteMem(60,Value);
        res=ReadMem(60);
        AddToTransmit("<WR/>\r\n\r");
        content_type = COAP_CONTENTTYPE_APPLICATION_LINKFORMAT;
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</EEGWRITE>\r\n\r");

    return(ret_val);
}
    
int QueryNodes(ParameterList_t *TempParam) 
{   
    int  ret_val = 0;
    int  i,j;
    char strbuf[STRING_SIZE];
    function_node *node;
    function_proto *proto;
    
    memset(strbuf,0,80);
    
    DBG_LOG_DEBUG("Into QUERYNodes.\n");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (NodesArray))
    {
        if(array_size(NodesArray)==0) 
        {
            AddToTransmit("<ERROR_NODES_NULL>\r\n\r"); 
            DBG_LOG_WARNING("Into QUERYNodes.\n");
        }
        else 
        {
            for (i=0;i < array_size(NodesArray);i++)
            {
                array_get_at(NodesArray, i, (void**)&node);
                if ((node == NULL))
                {
                    DBG_LOG_ERROR("node argument is NULL\n");
                    continue;
                }
                for (j=0;j < array_size(node->proto);j++)
                {
                    array_get_at(node->proto, j, (void**)&proto);
                    if ((proto == NULL))
                    {
                        DBG_LOG_ERROR("proto argument is NULL\n");
                        continue;
                    }
                    if( (i==array_size(NodesArray)-1) 
                            && (j==array_size(node->proto)-1) )
                    {
                        snprintf(strbuf,STRING_SIZE,
                            "<coap://%s%s>;if=\"controller\"\n",
                            node->ip,proto->name);
                        AddToTransmit(strbuf);
                        break;
                    }
                    snprintf(strbuf,STRING_SIZE,
                            "<coap://%s%s>;if=\"controller\",\n",
                                node->ip,proto->name);
                    AddToTransmit(strbuf);
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
        DBG_LOG_WARNING("Invalid parameters.\n");
    }

    return ret_val;
}

int FindUpdateServer()
{
    int  ret_val = 0;
    int i,j,k=0;
    char *strptr;
    char strbuf[80];
    function_node *node;
    function_proto *proto;
    
    memset(strbuf,0,80);
    strptr = (char*)strbuf;
    
    DBG_LOG_DEBUG("Into FindUpdateServer.\n");
    if(NodesArray==NULL) 
    {
        DBG_LOG_WARNING("Nodes are null.\n");
    }
    else 
    {

        //printf("array_size(NodesArray) %d\n", array_size(NodesArray));
        for (i=0;i < array_size(NodesArray);i++)
        {
            array_get_at(NodesArray, i, (void**)&node);
            //printf("array_size(node->proto) %d\n", array_size(node->proto));
            for (j=0;j < array_size(node->proto);j++)
            {
                array_get_at(node->proto, j, (void**)&proto);
                //printf("(void**)&proto %d node->proto %d\n", proto, node->proto);
                if(strcmp(proto->name,"/techupdate")==0) {
                    DBG_LOG_DEBUG("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                    DBG_LOG_DEBUG("Tech Server IP: %s\n",node->ip);
                    DBG_LOG_DEBUG("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                    SetUpdateServer(node->ip);
                                            ret_val = 1;
                }
            }
        }
    }


    return ret_val;
}

void put_node_msg(char *_ip,char *_name)
{
    int ip_id = -1;
    uint32_t name_ptr = 0;
    int i;
    function_node *node;
    function_proto *proto;
    function_proto *protoi;
    
    DBG_LOG_DEBUG("Into put_node_msg.\n");
    if ((_ip == NULL) && (_name == NULL))
    {
        DBG_LOG_ERROR("put_node_msg argument is NULL\n");
        return;
    }
    if (NodesArray == 0)
    {
        if (array_new(&NodesArray) != 0)
            return;
    }
    else
    {
    }
    for (i=0;i < array_size(NodesArray);i++)
    {
        array_get_at(NodesArray, i, (void**)&node);
        if ((node == NULL))
        {
            DBG_LOG_ERROR("node argument is NULL\n");
            continue;
        }
        if (!strcmp(_ip,node->ip))
        {    
            ip_id = i;
            break;
        }        
    }
    if (ip_id < 0)
    {
        node = (function_node *)umm_calloc(1,sizeof(function_node));
        if (node == NULL){return;}
        if (array_new(&(node->proto)) != 0)
            return;
        strncpy(node->ip,_ip,strlen(_ip));
        ip_id = array_size(NodesArray);
        if (array_add(NodesArray, (void *)node) != 0)
        {
            array_destroy_free(node->proto);
            umm_free((void *)node);
            return;
        }
    }
    for (name_ptr=1;name_ptr < strlen(_name);name_ptr++) 
        if ((_name[name_ptr-1] == '<') && (_name[name_ptr] == '/'))
        {
            proto = (function_proto *)umm_calloc(1,sizeof(function_proto));
            if (proto == NULL){return;}
            proto->len = 0;
            while ((_name[name_ptr] != '>') && (name_ptr < strlen(_name)))
            {
                proto->name[proto->len++] = _name[name_ptr];
                name_ptr++;
            }
            proto->name[proto->len++] = 0;
            for (i=0;i < array_size(node->proto);i++)
            {
                array_get_at(node->proto, i, (void**)&protoi);
                if ((protoi == NULL))
                {
                    DBG_LOG_ERROR("protoi argument is NULL\n");
                    continue;
                }
                if (!strcmp(protoi->name,proto->name))
                {
                    break;
                }
            }
            if (i < array_size(node->proto))
            {
                umm_free((void *)proto);
                continue;
            }
            proto->len = strlen(proto->name);
            if (array_add(node->proto, (void *)proto) != 0)
            {
                umm_free((void *)proto);
                return;
            }
        }
    return;
}
char* get_first_node_by_func(const char *_name)
{
    int i,j;
    function_node *node;
    function_proto *proto;
    
    DBG_LOG_DEBUG("Into get_first_node_by_func.\n");
    for (i=0;i < array_size(NodesArray);i++)
    {
        array_get_at(NodesArray, i, (void**)&node);
        if ((node == NULL))
        {
            DBG_LOG_ERROR("node argument is NULL\n");
            continue;
        }
        for (j=0;j < array_size(node->proto);j++)
        {
            array_get_at(node->proto, i, (void**)&proto);
            if ((proto == NULL))
            {
                DBG_LOG_ERROR("proto argument is NULL\n");
                continue;
            }
            if (strcmp(proto->name,_name))
            {
                return node->ip;
            }
        }     
    }
    return 0;
}

void print_node_and_func(void)
{
    int i,j;
    char *strptr;
    char strbuf[10000];
    function_node *node;
    function_proto *proto;
    
    memset(strbuf,0,10000);
    strptr = (char*)strbuf;
    DBG_LOG_DEBUG("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
    
    for (i=0;i < array_size(NodesArray);i++)
    {
        array_get_at(NodesArray, i, (void**)&node);
        if ((node == NULL))
        {
            DBG_LOG_ERROR("node argument is NULL\n");
            continue;
        }
        for (j=0;j < array_size(node->proto);j++)
        {
            array_get_at(node->proto, j, (void**)&proto);
            if ((proto == NULL))
            {
                DBG_LOG_ERROR("proto argument is NULL\n");
                continue;
            }
            strptr += snprintf(strptr,
                    10000-((int)(strptr-strbuf)),
                    "<coap://%s%s>;if=\"controller\",\n",
                    node->ip,proto->name);
        }     
    }
    *(strptr-2) = 0;
    DBG_LOG_DEBUG((const char*)strbuf);
    DBG_LOG_DEBUG("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
    return;
}

void function_beakon(void)
{
    int rc,i;
    #ifdef CPU
    coap_buffer_t tokfb;
    
    DBG_LOG_DEBUG("Into function_beakon.\n");
    pktlen = sizeof(scratch_raw);
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
    if (!(rc = coap_build(scratch_raw, &pktlen, &pkt, path_well_core_clb, 0)))
    {
        TransferBand((uint8_t*)scratch_raw,pktlen);
    }
    #endif
return;
}
  
   /* The following function is responsible for Giving current          */
   /* functions. This function returns zero is successful or a negative */
   /* return value if there was an error.                               */
int WELLKnown(ParameterList_t *TempParam)
{
    int  ret_val = 0,i;

    DBG_LOG_DEBUG("Into WELLKnown.\n");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        //snprintf(buf_local,60,"id %02X %02X\r\n\r",pkt.hdr.id[0], pkt.hdr.id[1]);
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
        DBG_LOG_WARNING("Invalid parameters.\n");
    }

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

    DBG_LOG_DEBUG("Into CallbackWELLKnown.\n");
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
        DBG_LOG_WARNING("Invalid parameters.\n");
    }

    DBG_LOG_DEBUG("Into END of CallbackWELLKnown.\n");
    return(ret_val);
}
/*============================================================================*/
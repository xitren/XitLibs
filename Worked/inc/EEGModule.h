/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EEGModule.h
 * Author: Ershova_o
 *
 * Created on 8 сентября 2017 г., 9:45
 */

#ifndef EEGMODULE_H
#define EEGMODULE_H

#ifdef __cplusplus
extern "C" {
#endif
    
/* Global headers ------------------------------------------------------------*/
#include "xitlibtypes.h"             /* Application Header.            */
/*============================================================================*/

    
    
int SubscribeEEGFile(ParameterList_t *TempParam);
//void ReadLineEEG();
void ReadFileEEG();
int CheckEEGSubscription();
int CheckEEGStatus();
void ReadEEGPart();
void SendEEGPart(size_t iter, char *part);

#ifdef __cplusplus
}
#endif

#endif /* EEGMODULE_H */


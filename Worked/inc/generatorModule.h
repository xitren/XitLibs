/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   generatorModule.h
 * Author: olga
 *
 * Created on 20 апреля 2017 г., 17:12
 */

#ifndef GENERATORMODULE_H
#define GENERATORMODULE_H
#include "xitlibtypes.h"             /* Application Header.            */
#include "LibConfig.h"

int RunGenerator(ParameterList_t *TempParam);
int StopGenerator(ParameterList_t *TempParam);


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* GENERATORMODULE_H */


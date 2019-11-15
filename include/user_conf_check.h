/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   user_conf_check.h
 * Author: gusev_a
 *
 * Created on 10 ноября 2017 г., 12:37
 */

#ifndef USER_CONF_CHECK_H
#define USER_CONF_CHECK_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CPU) && (!defined(PLATFORM_WINDOWS) && !defined(PLATFORM_LINUX)) && !defined(MC)
#error "Please define platform: PLATFORM_WINDOWS or PLATFORM_LINUX or MC"
#endif

#if !defined(__CMDMODULE_H__)
#error "Please add CommandModule.h"
#endif

#if !defined(__MEMORY_CONFIG_H__)
#error "Please add ConfigMem.h"
#endif

#if !defined(__DMARETRANSMITTER_H__)
#error "Please add DMAretransmitterh"
#endif

#if !defined(__CALCMODULE_H__)
#error "Please add DistCalc.h"
#endif

#if !defined(__EXTERNAL_H__)
#error "Please add ExtFunctions.h"
#endif

#if !defined(FUNCTIONSDISCOVERY_H)
#error "Please add FunctionsDiscovery.h"
#endif

#if !defined(__HANDLER_H__)
#error "Please add handler.h"
#endif

#if !defined(__BUFFERMODULE_H__)
#error "Please add InOutBuffer.h"
#endif

#if !defined(LIBCONFIG_H)
#error "Please add LibConfig.h"
#endif

#if !defined(__LOGGERMODULE_H__)
#error "Please add LogModule.h"
#endif

#if !defined(__LEDCODE_H__)
#error "Please add PWMModule.h"
#endif

#if !defined(__INPUTPOCKET_H__)
#error "Please add Packet.h"
#endif

#if !defined(__EEGRECORDER_H__)
#error "Please add StreamDataRecorder.h"
#endif

#if !defined(UPDATEMODULE_H)
#error "Please add UpdateModule.h"
#endif

	//#if !defined(GENERATORMODULE_H)
	//#error "Please add generatorModule.h"
	//#endif

#if !defined(__FUNCPARAMS_H__)
#error "Please add xitlibtypes.h"
#endif


#ifdef __cplusplus
}
#endif

#endif /* USER_CONF_CHECK_H */


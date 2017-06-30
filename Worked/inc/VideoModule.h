
/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "xitlibtypes.h"
#include "LibConfig.h"
/*============================================================================*/

#ifndef VIDEOMODULE_H
#define VIDEOMODULE_H

#ifdef __cplusplus
extern "C" {
#endif

int VIDEOThread(ParameterList_t *TempParam);
int Snap(ParameterList_t *TempParam);
int Light(ParameterList_t *TempParam);
int lamp();

#ifdef PLATFORM_LINUX
    void errno_exit(const char *s);
    int xioctl(int fh, int request, void *arg);
    void process_image(const void *p, int size);
    int read_frame(void);
    void mainloop(void);
    void stop_capturing(void);
    void start_capturing(void);
    void uninit_device(void);
    void init_read(unsigned int buffer_size);
    void init_mmap(void);
    void init_userp(unsigned int buffer_size);
    void init_device(void);
    void close_device(void);
    void open_device(char* device_name);
    void usage(FILE *fp, int argc, char **argv);
#endif


#ifdef __cplusplus
}
#endif

#endif /* VIDEOMODULE_H */
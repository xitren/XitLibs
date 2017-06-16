
/* Local headers -------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#ifdef PLATFORM_LINUX
    #include <getopt.h>             /* getopt_long() */
    #include <fcntl.h>              /* low-level i/o */
    #include <unistd.h>
    #include <errno.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/time.h>
    #include <sys/mman.h>
    #include <sys/ioctl.h>
    #include <linux/videodev2.h>
#endif
#include "VideoModule.h"
#include "xitlibtypes.h"             /* Application Header.            */
#include "CommandModule.h"
#include "../CoAP/coap.h"
#include "Handler.h"
/*============================================================================*/

/* Private defines -----------------------------------------------------------*/
#define CLEAR(x) memset(&(x), 0, sizeof(x))
#define HEIGHT 640
#define WIDTH 480
#ifdef PLATFORM_LINUX
    enum io_method {
            IO_METHOD_READ,
            IO_METHOD_MMAP,
            IO_METHOD_USERPTR,
    };
    struct buffer {
            void   *start;
            size_t  length;
    };
    char             dev_name[100];
    enum io_method   io = IO_METHOD_MMAP;
    int              fd = -1;
    struct buffer     *buffers;
    unsigned int     n_buffers;
    int              out_buf;
    int              force_format;
    int              frame_count = 70;
#endif
/*============================================================================*/
    
/* Private variables ---------------------------------------------------------*/
uint8_t          *image_buffer_rows[WIDTH];
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
#ifdef CPU

int Light(ParameterList_t *TempParam)
{
    int  ret_val = 0;
//    #ifdef DEBUG
//       printf("--//internal//-- Into Light.\r\n\r");
//       //printf("Number k first sample %d  count %d.\r\n\r");
//    #endif
//    content_type = COAP_CONTENTTYPE_APPLICATION_JSON;
//    AddToTransmit("<LIGHT>\r\n\r");
//    
//        lamp();
//    #ifdef PI
//    //system("sudo java -classpath .:classes:/opt/pi4j/lib/'*' Rasp"); ///home/pi/Progs/
//    #endif
//
//    AddToTransmit("Have light!!!");
//        
//    AddToTransmit("</LIGHT>\r\n\r");
//    #ifdef DEBUG
//        printf("--//internal//-- Into END of Snap.\r\n\r");
//    #endif
    return(ret_val);
    
}

int lamp()
{
//        int i,pin=0;
//    printf("Raspberi Pi wiringPi test\r\n\r");
//
//    if( wiringPiSetup() == -1 )
//    {
//        printf("WiringPi initialisation failed!\r\n\r");
//        exit(1);
//    }
//    else
//    {
//        printf("WiringPi enable...\r\n\r");
//        pinMode(pin, OUTPUT);
//
//        for(i=0;i<10;i++) //int i=0;i<10;i++
//        {
//            printf("light ON\n\r");
//            digitalWrite(pin, 1);
//            delay(250);
//            printf("light Off\n\r");
//            digitalWrite(pin, 0);
//            delay(250);
//        }
//    }
    return 0;

}

int Snap(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  i,ind_i = -1;
    FILE *fp;
    int num;
    int sizefp;
    int end;
    #ifdef DEBUG
        printf("--//internal//-- Into Snap.\r\n\r");
        printf("--//internal//-- Here head Snap.\r\n\r");
    #endif
    size_parts = 1024;
    AddToTransmit("<SNAP>\r\n\r");
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

        printf("Send query snap pre.jpg\r\n\r");
        #ifdef PI
        if (ind_i == 0)
        {
            system("sudo raspistill -w 480 -h 320 -q 20 -o snap.jpg");
            printf("Send query snap.jpg\r\n\r");
        }
        #endif
        fp = fopen("snap.jpg","rb"); // read mode
        content_type = COAP_CONTENTTYPE_IMAGE_JPEG;
        if( fp == NULL )
        {
           printf("Error no file snap.jpg\r\n\r");
           return(INVALID_PARAMETERS_ERROR);
        }
        fseek ( fp , 0 , SEEK_SET );
        
        fseek (fp , 0 , SEEK_END);
        int lSize = ftell (fp);
        rewind (fp);

        end = 0;
        num = 0;
        
        #ifdef DEBUG
            printf("--//internal//-- Part %d .\r\n\r",ind_i);
            printf("--//internal//-- File size %d .\r\n\r",lSize);
        #endif
        if (ind_i == -1)
        {
            sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
            #ifdef DEBUG
                printf("--//internal//-- %d readed from file of %d.\r\n\r",sizefp,size_parts);
            #endif
            if (sizefp == 0)
                return(INVALID_PARAMETERS_ERROR);
            if (sizefp != size_parts)
                end = 1;
            make_part_option(&opt_part,num,COAP_PART_SIZE_1024,end);
            size_parts_cur = sizefp;
            num++;
        }
        else
        {
            fseek ( fp , ind_i*size_parts , SEEK_SET );
            #ifdef DEBUG
                printf("--//internal//-- from %d to %d readed from file of %d.\r\n\r"
                        ,ind_i*size_parts,(ind_i+1)*size_parts-1,lSize);
            #endif
//            while (num <= ind_i)
//            {
                sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
                #ifdef DEBUG
                    printf("--//internal//-- %d readed from file of %d.\r\n\r",sizefp,size_parts);
                #endif
                if (sizefp == 0)
                    return(INVALID_PARAMETERS_ERROR);
                if (sizefp != size_parts)
                {
                    end = 1;
                }
                num+=1 + ind_i;
//            } 
            num--;
            make_part_option(&opt_part,num,COAP_PART_SIZE_1024,end);
            size_parts_cur = sizefp;
        }
        fclose(fp);
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

    AddToTransmit("</SNAP>\r\n\r");
    #ifdef DEBUG
        printf("--//internal//-- Into END of Snap.\r\n\r");
    #endif
    return(ret_val);
}

int VIDEOThread(ParameterList_t *TempParam)
{
   int  ret_val = 0;
    int  i,ind_i = -1;
    FILE *fp;
    int num;
    int sizefp;
    int end;
    #ifdef DEBUG
        printf("--//internal//-- Into VIDEOThread.\r\n\r");
        printf("--//internal//-- Here head VIDEOThread.\r\n\r");
    #endif
    size_parts = 1024;
    AddToTransmit("<VIDEOTHREAD>\r\n\r");
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

        #ifdef PI
        if (ind_i == 0)
        {
            system("sudo raspivid -o video.h264 -t 10000");
            printf("Send query VIDEO\r\n\r");
        }
        #endif
/*
        fp = fopen("snap.jpg","rb"); // read mode
        content_type = COAP_CONTENTTYPE_IMAGE_JPEG;
        if( fp == NULL )
        {
           printf("Error no file VIDEO\r\n\r");
           return(INVALID_PARAMETERS_ERROR);
        }
        fseek ( fp , 0 , SEEK_SET );
        
        fseek (fp , 0 , SEEK_END);
        int lSize = ftell (fp);
        rewind (fp);

        end = 0;
        num = 0;
        
        #ifdef DEBUG
            printf("--//internal//-- Part %d .\r\n\r",ind_i);
            printf("--//internal//-- File size %d .\r\n\r",lSize);
        #endif
        if (ind_i == -1)
        {
            sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
            #ifdef DEBUG
                printf("--//internal//-- %d readed from file of %d.\r\n\r",sizefp,size_parts);
            #endif
            if (sizefp == 0)
                return(INVALID_PARAMETERS_ERROR);
            if (sizefp != size_parts)
                end = 1;
            make_part_option(&opt_part,num,COAP_PART_SIZE_1024,end);
            size_parts_cur = sizefp;
            num++;
        }
        else
        {
            fseek ( fp , ind_i*size_parts , SEEK_SET );
            #ifdef DEBUG
                printf("--//internal//-- from %d to %d readed from file of %d.\r\n\r"
                        ,ind_i*size_parts,(ind_i+1)*size_parts-1,lSize);
            #endif
//            while (num <= ind_i)
//            {
                sizefp = fread(bufsa,sizeof(uint8_t),size_parts,fp);
                #ifdef DEBUG
                    printf("--//internal//-- %d readed from file of %d.\r\n\r",sizefp,size_parts);
                #endif
                if (sizefp == 0)
                    return(INVALID_PARAMETERS_ERROR);
                if (sizefp != size_parts)
                {
                    end = 1;
                }
                num+=1 + ind_i;
//            } 
            num--;
            make_part_option(&opt_part,num,COAP_PART_SIZE_1024,end);
            size_parts_cur = sizefp;
        }
        fclose(fp);
*/
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

    AddToTransmit("</VIDEOTHREAD>\r\n\r");
    #ifdef DEBUG
        printf("--//internal//-- Into END of VIDEOThread.\r\n\r");
    #endif
    return(ret_val);
}
#endif
#ifdef PLATFORM_LINUX
    void errno_exit(const char *s)
    {
            fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
            exit(EXIT_FAILURE);
    }

    int xioctl(int fh, int request, void *arg)
    {
            int r;

            do {
                    r = ioctl(fh, request, arg);
            } while (-1 == r && EINTR == errno);

            return r;
    }

    void process_image(const void *p, int size)
    {
    //        if (out_buf)
    //                fwrite(p, size, 1, stdout);

            int i;
            for (i=0;i < HEIGHT; i++)
                memcpy(image_buffer_rows[i],(p+i*WIDTH*2),WIDTH*2);
            printf("%d.",size);
    //        fflush(stderr);
    //        fprintf(stderr, ".");
    //        fflush(stdout);
    }

    int read_frame(void)
    {
            struct v4l2_buffer buf;
            unsigned int i;

            switch (io) {
            case IO_METHOD_READ:
                    if (-1 == read(fd, buffers[0].start, buffers[0].length)) {
                            switch (errno) {
                            case EAGAIN:
                                    return 0;

                            case EIO:
                                    /* Could ignore EIO, see spec. */

                                    /* fall through */

                            default:
                                    errno_exit("read");
                            }
                    }

                    process_image(buffers[0].start, buffers[0].length);
                    break;

            case IO_METHOD_MMAP:
                    CLEAR(buf);

                    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                    buf.memory = V4L2_MEMORY_MMAP;

                    if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) {
                            switch (errno) {
                            case EAGAIN:
                                    return 0;

                            case EIO:
                                    /* Could ignore EIO, see spec. */

                                    /* fall through */

                            default:
                                    errno_exit("VIDIOC_DQBUF");
                            }
                    }

                    assert(buf.index < n_buffers);

                    process_image(buffers[buf.index].start, buf.bytesused);

                    if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
                            errno_exit("VIDIOC_QBUF");
                    break;

            case IO_METHOD_USERPTR:
                    CLEAR(buf);

                    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                    buf.memory = V4L2_MEMORY_USERPTR;

                    if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) {
                            switch (errno) {
                            case EAGAIN:
                                    return 0;

                            case EIO:
                                    /* Could ignore EIO, see spec. */

                                    /* fall through */

                            default:
                                    errno_exit("VIDIOC_DQBUF");
                            }
                    }

                    for (i = 0; i < n_buffers; ++i)
                            if (buf.m.userptr == (unsigned long)buffers[i].start
                                && buf.length == buffers[i].length)
                                    break;

                    assert(i < n_buffers);

                    process_image((void *)buf.m.userptr, buf.bytesused);

                    if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
                            errno_exit("VIDIOC_QBUF");
                    break;
            }

            return 1;
    }

    void mainloop(void)
    {
    //        unsigned int count;
    //
    //        count = frame_count;
    //
    //        while (count-- > 0) {
                    for (;;) {
                            fd_set fds;
                            struct timeval tv;
                            int r;

                            FD_ZERO(&fds);
                            FD_SET(fd, &fds);

                            /* Timeout. */
                            tv.tv_sec = 2;
                            tv.tv_usec = 0;

                            r = select(fd + 1, &fds, NULL, NULL, &tv);

                            if (-1 == r) {
                                    if (EINTR == errno)
                                            continue;
                                    errno_exit("select");
                            }

                            if (0 == r) {
                                    fprintf(stderr, "select timeout\n");
                                    exit(EXIT_FAILURE);
                            }

                            if (read_frame())
                                    break;
                            /* EAGAIN - continue select loop. */
                    }
    //        }
    }

    void stop_capturing(void)
    {
            enum v4l2_buf_type type;

            switch (io) {
            case IO_METHOD_READ:
                    /* Nothing to do. */
                    break;

            case IO_METHOD_MMAP:
            case IO_METHOD_USERPTR:
                    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                    if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &type))
                            errno_exit("VIDIOC_STREAMOFF");
                    break;
            }
    }

    void start_capturing(void)
    {
            unsigned int i;
            enum v4l2_buf_type type;

            switch (io) {
            case IO_METHOD_READ: 
                    /* Nothing to do. */
                    break;

            case IO_METHOD_MMAP:
                    for (i = 0; i < n_buffers; ++i) {
                            struct v4l2_buffer buf;

                            CLEAR(buf);
                            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                            buf.memory = V4L2_MEMORY_MMAP;
                            buf.index = i;

                            if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
                                    errno_exit("VIDIOC_QBUF");
                    }
                    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                    if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
                            errno_exit("VIDIOC_STREAMON");
                    break;

            case IO_METHOD_USERPTR:
                    for (i = 0; i < n_buffers; ++i) {
                            struct v4l2_buffer buf;

                            CLEAR(buf);
                            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                            buf.memory = V4L2_MEMORY_USERPTR;
                            buf.index = i;
                            buf.m.userptr = (unsigned long)buffers[i].start;
                            buf.length = buffers[i].length;

                            if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
                                    errno_exit("VIDIOC_QBUF");
                    }
                    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                    if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
                            errno_exit("VIDIOC_STREAMON");
                    break;
            }
    }

    void uninit_device(void)
    {
            unsigned int i;

            switch (io) {
            case IO_METHOD_READ:
                    free(buffers[0].start);
                    break;

            case IO_METHOD_MMAP:
                    for (i = 0; i < n_buffers; ++i)
                            if (-1 == munmap(buffers[i].start, buffers[i].length))
                                    errno_exit("munmap");
                    break;

            case IO_METHOD_USERPTR:
                    for (i = 0; i < n_buffers; ++i)
                            free(buffers[i].start);
                    break;
            }

            free(buffers);
    }

    void init_read(unsigned int buffer_size)
    {
            buffers = calloc(1, sizeof(*buffers));

            if (!buffers) {
                    fprintf(stderr, "Out of memory\n");
                    exit(EXIT_FAILURE);
            }

            buffers[0].length = buffer_size;
            buffers[0].start = malloc(buffer_size);

            if (!buffers[0].start) {
                    fprintf(stderr, "Out of memory\n");
                    exit(EXIT_FAILURE);
            }
    }

    void init_mmap(void)
    {
            struct v4l2_requestbuffers req;

            CLEAR(req);

            req.count = 4;
            req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            req.memory = V4L2_MEMORY_MMAP;

            if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
                    if (EINVAL == errno) {
                            fprintf(stderr, "%s does not support "
                                     "memory mapping\n", dev_name);
                            exit(EXIT_FAILURE);
                    } else {
                            errno_exit("VIDIOC_REQBUFS");
                    }
            }

            if (req.count < 2) {
                    fprintf(stderr, "Insufficient buffer memory on %s\n",
                             dev_name);
                    exit(EXIT_FAILURE);
            }

            buffers = calloc(req.count, sizeof(*buffers));

            if (!buffers) {
                    fprintf(stderr, "Out of memory\n");
                    exit(EXIT_FAILURE);
            }

            for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
                    struct v4l2_buffer buf;

                    CLEAR(buf);

                    buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                    buf.memory      = V4L2_MEMORY_MMAP;
                    buf.index       = n_buffers;

                    if (-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
                            errno_exit("VIDIOC_QUERYBUF");

                    buffers[n_buffers].length = buf.length;
                    buffers[n_buffers].start =
                            mmap(NULL /* start anywhere */,
                                  buf.length,
                                  PROT_READ | PROT_WRITE /* required */,
                                  MAP_SHARED /* recommended */,
                                  fd, buf.m.offset);

                    if (MAP_FAILED == buffers[n_buffers].start)
                            errno_exit("mmap");
            }
    }

    void init_userp(unsigned int buffer_size)
    {
            struct v4l2_requestbuffers req;

            CLEAR(req);

            req.count  = 4;
            req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            req.memory = V4L2_MEMORY_USERPTR;

            if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
                    if (EINVAL == errno) {
                            fprintf(stderr, "%s does not support "
                                     "user pointer i/o\n", dev_name);
                            exit(EXIT_FAILURE);
                    } else {
                            errno_exit("VIDIOC_REQBUFS");
                    }
            }

            buffers = calloc(4, sizeof(*buffers));

            if (!buffers) {
                    fprintf(stderr, "Out of memory\n");
                    exit(EXIT_FAILURE);
            }

            for (n_buffers = 0; n_buffers < 4; ++n_buffers) {
                    buffers[n_buffers].length = buffer_size;
                    buffers[n_buffers].start = malloc(buffer_size);

                    if (!buffers[n_buffers].start) {
                            fprintf(stderr, "Out of memory\n");
                            exit(EXIT_FAILURE);
                    }
            }
    }

    void init_device(void)
    {
            struct v4l2_capability cap;
            struct v4l2_cropcap cropcap;
            struct v4l2_crop crop;
            struct v4l2_format fmt;
            unsigned int min;

            int i;
            for (i=0;i < HEIGHT; i++)
                image_buffer_rows[i] = (uint8_t*) malloc(WIDTH*2);

            if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap)) {
                    if (EINVAL == errno) {
                            fprintf(stderr, "%s is no V4L2 device\n",
                                     dev_name);
                            exit(EXIT_FAILURE);
                    } else {
                            errno_exit("VIDIOC_QUERYCAP");
                    }
            }

            if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
                    fprintf(stderr, "%s is no video capture device\n",
                             dev_name);
                    exit(EXIT_FAILURE);
            }

            switch (io) {
            case IO_METHOD_READ:
                    if (!(cap.capabilities & V4L2_CAP_READWRITE)) {
                            fprintf(stderr, "%s does not support read i/o\n",
                                     dev_name);
                            exit(EXIT_FAILURE);
                    }
                    break;

            case IO_METHOD_MMAP:
            case IO_METHOD_USERPTR:
                    if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
                            fprintf(stderr, "%s does not support streaming i/o\n",
                                     dev_name);
                            exit(EXIT_FAILURE);
                    }
                    break;
            }


            /* Select video input, video standard and tune here. */


            CLEAR(cropcap);

            cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

            if (0 == xioctl(fd, VIDIOC_CROPCAP, &cropcap)) {
                    crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                    crop.c = cropcap.defrect; /* reset to default */

                    if (-1 == xioctl(fd, VIDIOC_S_CROP, &crop)) {
                            switch (errno) {
                            case EINVAL:
                                    /* Cropping not supported. */
                                    break;
                            default:
                                    /* Errors ignored. */
                                    break;
                            }
                    }
            } else {
                    /* Errors ignored. */
            }


            CLEAR(fmt);

            fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            if (force_format) {
                    fmt.fmt.pix.width       = HEIGHT;
                    fmt.fmt.pix.height      = WIDTH;
                    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
                    fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;

                    if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
                            errno_exit("VIDIOC_S_FMT");

                    /* Note VIDIOC_S_FMT may change width and height. */
            } else {
                    /* Preserve original settings as set by v4l2-ctl for example */
                    if (-1 == xioctl(fd, VIDIOC_G_FMT, &fmt))
                            errno_exit("VIDIOC_G_FMT");
            }

            /* Buggy driver paranoia. */
            min = fmt.fmt.pix.width * 2;
            if (fmt.fmt.pix.bytesperline < min)
                    fmt.fmt.pix.bytesperline = min;
            min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
            if (fmt.fmt.pix.sizeimage < min)
                    fmt.fmt.pix.sizeimage = min;

            switch (io) {
            case IO_METHOD_READ:
                    init_read(fmt.fmt.pix.sizeimage);
                    break;

            case IO_METHOD_MMAP:
                    init_mmap();
                    break;

            case IO_METHOD_USERPTR:
                    init_userp(fmt.fmt.pix.sizeimage);
                    break;
            }
    }

     void close_device(void)
    {
            if (-1 == close(fd))
                    errno_exit("close");

            fd = -1;

            int i;
            for (i=0;i < HEIGHT; i++)
                if (image_buffer_rows[i] == 0)
                    free(image_buffer_rows[i]);
    }

    void open_device(char* device_name)
    {
            struct stat st;
            strcpy(dev_name,device_name);

            if (-1 == stat(dev_name, &st)) {
                    printf("Cannot identify '%s': %d, %s\n",
                             dev_name, errno, strerror(errno));
                    exit(EXIT_FAILURE);
            }

            if (!S_ISCHR(st.st_mode)) {
                    printf("%s is no device\n", dev_name);
                    exit(EXIT_FAILURE);
            }

            fd = open(dev_name, O_RDWR /* required */ | O_NONBLOCK, 0);

            if (-1 == fd) {
                    printf("Cannot open '%s': %d, %s\n",
                             dev_name, errno, strerror(errno));
                    exit(EXIT_FAILURE);
            }
    }
#endif
int VIDEOLNRead(ParameterList_t *TempParam)
{
   int  ret_val = 0;
   int  Adress = -1;
   char buffer[STRING_SIZE];
   int i;

   #ifdef DEBUG
      printf("--//internal//-- Into VIDEOLNRead.\r\n\r");
   #endif
   AddToTransmit("<VIDEOLINE>\r\n\r");
   /* First check to see if the parameters required for the execution of*/
   /* this function appear to be semi-valid.                            */
   if ((TempParam) && (TempParam->NumberofParameters > 1))
   {
      for (i=1;i<TempParam->NumberofParameters;i+=2)
      {
         if (!strcmp(TempParam->Params[i-1].strParam,"address"))
         {
            Adress = (unsigned int)(TempParam->Params[i].intParam);
         }
      }
      if (Adress >= HEIGHT)
          Adress = HEIGHT - 1;
      if (Adress >= 0)
      {
         AddToTransmit(" <ADDRESS>\r\n\r");
         sprintf((char*)buffer,"  %d\r\n\r",(int)Adress);
         AddToTransmit((char*)buffer);
         AddToTransmit(" </ADDRESS>\r\n\r");
         AddToTransmit(" <VALUE>\r\n\r");
         if (image_buffer_rows[Adress] == 0)
            AddToTransmit(" <NO/>\r\n\r");
         else
            for (i=0;i < WIDTH*2; i++)
            {
               sprintf((char*)buffer,"  %x\r\n\r",image_buffer_rows[Adress][i]);
               AddToTransmit((char*)buffer);
            }
         AddToTransmit(" <VALUE>\r\n\r");
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
   AddToTransmit("</VIDEOLINE>\r\n\r");

   return(ret_val);
}
/*============================================================================*/
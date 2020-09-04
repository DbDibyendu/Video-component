

/*! Include Guard */
#ifndef __PARSE_CONF_H__
#define __PARSE_CONF_H__



/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */
#include <stdint.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <errno.h>

/* --- include/rapidjson Includes --- */

#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/ostreamwrapper.h"
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/error/en.h"


/* --- Project Includes --- */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/v4l2-common.h>
#include <linux/v4l2-controls.h>
#include <linux/videodev2.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <string.h>
#include <fstream>
#include <string>
#include <tsanalyser/tsanalyser.h>
#include <assert.h>
#include <getopt.h>             /* getopt_long() */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <linux/videodev2.h>
#include <linux/videodev.h>
#include <glob.h>
#include <unistd.h>


/**
 * @brief Parse and store JSON document into global variable
 *
 * @return int8_t 0 on SUCCESS and -1 on FAILURE
 * 
 */

int8_t loadJsonConfig();

/** 
 *  @brief List all the active cameras present
 *  
 *  @return -1 If device is not found and else 0 on Success
 */


int ListActiveCameras();


// creating a structure for capturing image and saving it into file

struct initCapture{
    
    char loc[100];                                  // stores the device location
    int fd;                                         
    v4l2_buffer bufferinfo;
    v4l2_buffer queryBuffer;
    v4l2_format imageFormat;

};

/** 
 *  @brief Reads the respective Camera settings of a particular device
 *  
 *  @return -1 on failure and 0 on success 
 */

int ReadCameraSettings(struct initCapture device);


/** 
 *  @brief  Capture Image and save it into memory
 *  
 *
 *  @return 0 on success and 1 on failure
 */


 int CaptureFrametoMem(struct initCapture device);



#endif



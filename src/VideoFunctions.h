/**
 * @file   	VideoFunctions.h
 * @brief  	Includes all the function prototype
 */


/*! Include Guard */
#ifndef CAMERA_H
#define CAMERA_H

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
#include <getopt.h>         
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <linux/videodev2.h>
#include <linux/videodev.h>
#include <glob.h>
#include <unistd.h>
#include "opencv2/core.hpp"

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
    
    IplImage* frame[10000];                      // OpenCV file format
    char loc[100];                               // stores the device location
    char* buffer;
    char ** array = (char **) malloc(sizeof(char*));            // for storing the buffers into a 2d pointer array

};



/** 
 *  @brief Initialises the Camera by opening the device location
 *  
 *  @return -1 on failure and fd on success 
 */

int initCamera(struct initCapture device);


/** 
 *  @brief Reads the respective Camera settings of a particular device
 *  
 *  @return -1 on failure and 0 on success 
 */

int ReadCameraSettings(struct initCapture device, int fd);

/** 
 *  @brief  Capture Image and save it into memory
 *  
 *
 *  @return 0 on success and 1 on failure
 */

int CaptureFrametoMem(struct initCapture device,int fd);

/** 
 *  @brief  Take 10 frames at a time and save it into an array
 *  
 *
 *  @return 0 on success and 1 on failure
 */

int CaptureStreamtoMem(struct initCapture device, int fd);



/* End of Include Guard */
#endif



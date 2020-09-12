/**
 * @file   	VideoFunctions.h
 * @brief  	Includes all the function prototype
 */


/*! Include Guard */
#ifndef CAMERA_H
#define CAMERA_H

/*! CPP guard */
#ifdef camera
extern "C" {
#endif



/* --- Project Includes --- */

#include <stdint.h>
#include <cstdlib>
#include <string>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include "opencv2/core.hpp"


/**
 *  @brief List all the active cameras present
 *
 *  @return -1 If device is not found and else 0 on Success
 */

extern int ListActiveCameras();


// creating a structure for capturing image and saving it into file

struct initCapture {

    IplImage* frame[10000];                      // OpenCV file format
    char loc[100];                               //  Char Member which stores the device location
    char ** array = (char **) malloc(sizeof(char*));            // for storing the buffers into a 2d pointer array

};



/**
 * @brief Parse and store JSON document into global variable
 *
 * @return int8_t 0 on SUCCESS and -1 on FAILURE
 *
 */

extern int8_t loadJsonConfig(struct initCapture device, char* name);

/**
 *  @brief Initialises the Camera by opening the device location
 *
 *  @param  device the object
 *
 *  @return -1 on failure and fd on success
 */

extern int initCamera(struct initCapture device);


/**
 *  @brief Reads the respective Camera settings of a particular device
 *  @param  fd integer Variable for opening camera
 *  @param  device the object
 *
 *  @return -1 on failure and 0 on success
 */

extern int ReadCameraSettings(struct initCapture device, int fd);

/**
 *  @brief  Capture Image and save it into memory
 *  @param  fd integer Variable for opening camera
 *  @param  device the object
 *
 *  @return 0 on success and 1 on failure
 */

extern int CaptureFrametoMem(struct initCapture device,int fd);

/**
 *  @brief  Take 10 frames at a time and save it into an array
 *  @param  fd integer Variable for opening camera
 *  @param  device the object
 *
 *
 *  @return 0 on success and 1 on failure
 */

extern int CaptureStreamtoMem(struct initCapture device, int fd);

#ifdef camera
}
#endif /* End of CPP guard */

/* End of Include Guard */
#endif



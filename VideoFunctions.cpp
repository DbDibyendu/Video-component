/**
* @file shunyaVideoFunctions.cpp
* @brief 
* Contains all the functions for Camera Initialisation, load JSON config
* and Capture Frame
*
* @author Dibyendu Biswas
* @bug No bugs from my side
*/

/*
 *#####################################################################
 *  Initialization block
 *  ---------------------
 *  This block contains initialization code for this particular file.
 *  It typically contains Includes, constants or global variables used
 *  throughout the file.
 *#####################################################################
 */

/* --- Standard Includes --- */


#include "VideoFunctions.h"
#include <fstream>
#include <cstdlib>
#include <string>
#include <errno.h>

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


using namespace std;

/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */


/** 
 *  @brief List all the active cameras present
 *  
 *  @return -1 If device is not found and else 0 on Success
 */

int ListActiveCameras() {
  int i;
  glob_t globbuf;
  if (glob("/dev/v4l/by-path/*", 0, NULL, &globbuf) != 0) {
    perror("glob");
    return -1;
  }
  for (i=0; i < globbuf.gl_pathc; i++) {
    char buf[256] = {};
    if (readlink(globbuf.gl_pathv[i], buf, sizeof(buf)-1) > 0) {
      puts(buf);
    }
  }
  return 0;
}


/** 
 *  @brief Reads the respective Camera settings of a particular device
 *  
 *  @return -1 on failure and 0 on success 
 */
int ReadCameraSettings(struct initCapture device){
     

    struct video_capability video_cap;
    struct video_window     video_win;
    struct video_picture   video_pic;

    if((device.fd = open(device.loc, O_RDONLY)) == -1){
        perror("cam_info: Can't open device");
        return -1;
    }

    if(ioctl(device.fd, VIDIOCGCAP, &video_cap) == -1)
        perror("cam_info: Can't get capabilities");
    else {
        printf("Name:\t\t '%s'\n", video_cap.name);
        printf("Minimum size:\t%d x %d\n", video_cap.minwidth, video_cap.minheight);
        printf("Maximum size:\t%d x %d\n", video_cap.maxwidth, video_cap.maxheight);
    }

    if(ioctl(device.fd, VIDIOCGWIN, &video_win) == -1)
        perror("cam_info: Can't get window information");
    else
        printf("Current size:\t%d x %d\n", video_win.width, video_win.height);

    if(ioctl(device.fd, VIDIOCGPICT, &video_pic) == -1)
        perror("cam_info: Can't get picture information");
    else
        printf("Current depth:\t%d\n", video_pic.depth);

    close(device.fd);
    return 0;

}

/** 
 *  @brief  Capture Image and save it into memory
 *  
 *
 *  @return 0 on success and 1 on failure
 */

int CaptureFrametoMem(struct initCapture device){

    // 1.  Open the device
    device.fd = open(device.loc,O_RDWR);
    if(device.fd < 0){
        perror("Failed to open device, OPEN");
        return 1;
    }

    // 2. Ask the device if it can capture frames
    v4l2_capability capability;
    if(ioctl(device.fd, VIDIOC_QUERYCAP, &capability) < 0){
        // something went wrong... exit
        perror("Failed to get device capabilities, VIDIOC_QUERYCAP");
        return 1;
    }

    // 3. Set Image format
    v4l2_format imageFormat={0};
    imageFormat.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    imageFormat.fmt.pix.width = 1024;
    imageFormat.fmt.pix.height = 1024;
    imageFormat.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    imageFormat.fmt.pix.field = V4L2_FIELD_NONE;
    
    // tell the device you are using this format
    if(ioctl(device.fd, VIDIOC_S_FMT, &imageFormat) < 0){
        perror("Device could not set format, VIDIOC_S_FMT");
        return 1;
    }

     // 4. Request Buffers from the device
    v4l2_requestbuffers requestBuffer = {0};
    requestBuffer.count = 1; // one request buffer
    requestBuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; // request a buffer wich we an use for capturing frames
    requestBuffer.memory = V4L2_MEMORY_MMAP;

    if(ioctl(device.fd, VIDIOC_REQBUFS, &requestBuffer) < 0){
        perror("Could not request buffer from device, VIDIOC_REQBUFS");
        return 1;
    }


    // 5. Quety the buffer to get raw data ie. ask for the you requested buffer
    // and allocate memory for it

    device.queryBuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    device.queryBuffer.memory = V4L2_MEMORY_MMAP;
    device.queryBuffer.index = 0;
    if(ioctl(device.fd, VIDIOC_QUERYBUF, &device.queryBuffer) < 0){
        perror("Device did not return the buffer information, VIDIOC_QUERYBUF");
        return 1;
    }
    // use a pointer to point to the newly created buffer
    // mmap() will map the memory address of the device to
    // an address in memory
    char* buffer = (char*)mmap(NULL, device.queryBuffer.length, PROT_READ | PROT_WRITE, MAP_SHARED,
                        device.fd, device.queryBuffer.m.offset);
    memset(buffer, 0, device.queryBuffer.length);

    
    // 6. Get a frame
    // Create a new buffer type so the device knows whichbuffer we are talking about


    memset(&device.bufferinfo, 0, sizeof(device.bufferinfo));
    device.bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    device.bufferinfo.memory = V4L2_MEMORY_MMAP;
    device.bufferinfo.index = 0;

    // Activate streaming
    int type = device.bufferinfo.type;
    if(ioctl(device.fd, VIDIOC_STREAMON, &type) < 0){
        perror("Could not start streaming, VIDIOC_STREAMON");
        return 1;
    }



/***************************** Begin looping here *********************/
    // Queue the buffer
    if(ioctl(device.fd, VIDIOC_QBUF, &device.bufferinfo) < 0){
        perror("Could not queue buffer, VIDIOC_QBUF");
        return 1;
    }

    // Dequeue the buffer
    if(ioctl(device.fd, VIDIOC_DQBUF, &device.bufferinfo) < 0){
        perror("Could not dequeue the buffer, VIDIOC_DQBUF");
        return 1;
    }
    // Frames get written after dequeuing the buffer

    cout << "Buffer has: " << (double)device.bufferinfo.bytesused / 1024
            << " KBytes of data" << endl;


    // Write the data out to file
    v4l2_buffer bufferinfo;

     // Open the file
    ofstream outFile;
    outFile.open("webcam_output.jpeg", ios::binary| ios::app);
    
    // Write the data out to file
    outFile.write(buffer, (double)device.bufferinfo.bytesused);

    // Close the file
    outFile.close();


    // end streaming
     if(ioctl(device.fd, VIDIOC_STREAMOFF, &device.bufferinfo.type) < 0){
         perror("Could not end streaming, VIDIOC_STREAMOFF");
          return 1;
          }

    close(device.fd);

}

/** 
 *  @brief  Take 20 frames at a time and save it into an array
 *  
 *
 *  @return 0 on success and 1 on failure
 */

int StreamtoMem(struct initCapture device){

     // 1.  Open the device
    device.fd = open(device.loc,O_RDWR);
    if(device.fd < 0){
        perror("Failed to open device, OPEN");
        return 1;
    }

    // 2. Ask the device if it can capture frames
    v4l2_capability capability;
    if(ioctl(device.fd, VIDIOC_QUERYCAP, &capability) < 0){
        // something went wrong... exit
        perror("Failed to get device capabilities, VIDIOC_QUERYCAP");
        return 1;
    }

    // 3. Set Image format
    v4l2_format imageFormat={0};
    imageFormat.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    imageFormat.fmt.pix.width = 1024;
    imageFormat.fmt.pix.height = 1024;
    imageFormat.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    imageFormat.fmt.pix.field = V4L2_FIELD_NONE;
    
    // tell the device you are using this format
    if(ioctl(device.fd, VIDIOC_S_FMT, &imageFormat) < 0){
        perror("Device could not set format, VIDIOC_S_FMT");
        return 1;
    }

     // 4. Request Buffers from the device
    v4l2_requestbuffers requestBuffer = {0};
    requestBuffer.count = 1; // one request buffer
    requestBuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; // request a buffer wich we an use for capturing frames
    requestBuffer.memory = V4L2_MEMORY_MMAP;

    if(ioctl(device.fd, VIDIOC_REQBUFS, &requestBuffer) < 0){
        perror("Could not request buffer from device, VIDIOC_REQBUFS");
        return 1;
    }


    // 5. Quety the buffer to get raw data ie. ask for the you requested buffer
    // and allocate memory for it

    device.queryBuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    device.queryBuffer.memory = V4L2_MEMORY_MMAP;
    device.queryBuffer.index = 0;
    if(ioctl(device.fd, VIDIOC_QUERYBUF, &device.queryBuffer) < 0){
        perror("Device did not return the buffer information, VIDIOC_QUERYBUF");
        return 1;
    }
    // use a pointer to point to the newly created buffer
    // mmap() will map the memory address of the device to
    // an address in memory
    char* buffer = (char*)mmap(NULL, device.queryBuffer.length, PROT_READ | PROT_WRITE, MAP_SHARED,
                        device.fd, device.queryBuffer.m.offset);
    memset(buffer, 0, device.queryBuffer.length);

    
    // 6. Get a frame
    // Create a new buffer type so the device knows whichbuffer we are talking about


    memset(&device.bufferinfo, 0, sizeof(device.bufferinfo));
    device.bufferinfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    device.bufferinfo.memory = V4L2_MEMORY_MMAP;
    device.bufferinfo.index = 0;

    // Activate streaming
    int type = device.bufferinfo.type;
    if(ioctl(device.fd, VIDIOC_STREAMON, &type) < 0){
        perror("Could not start streaming, VIDIOC_STREAMON");
        return 1;
    }

    int i;

    double frame[100000000]={0};

    for(i=0;i<20;i++){


/***************************** Begin looping here *********************/
    // Queue the buffer
    if(ioctl(device.fd, VIDIOC_QBUF, &device.bufferinfo) < 0){
        perror("Could not queue buffer, VIDIOC_QBUF");
        return 1;
    }

    // Dequeue the buffer
    if(ioctl(device.fd, VIDIOC_DQBUF, &device.bufferinfo) < 0){
        perror("Could not dequeue the buffer, VIDIOC_DQBUF");
        return 1;
    }
    // Frames get written after dequeuing the buffer

    cout << "Buffer has: " << (double)device.bufferinfo.bytesused / 1024
            << " KBytes of data" << endl;

    // Save the frames in an array
    frame[i]=(double)device.bufferinfo.bytesused;

    
    }

    // end streaming
     if(ioctl(device.fd, VIDIOC_STREAMOFF, &device.bufferinfo.type) < 0){
         perror("Could not end streaming, VIDIOC_STREAMOFF");
          return 1;
          }

    close(device.fd);

    for(i=0;i<10;i++){

        cout<<frame[i]/1024<<endl;
    }

    // Write the data out to file

    // Open the file
    ofstream outFile;
    outFile.open("webcam_output.jpeg", ios::binary| ios::app);
    
    // Write the data out to file
    outFile.write(buffer, frame[0]);

    // Close the file
    outFile.close();

}
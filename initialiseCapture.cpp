/**
* @file initialiseCapture.cpp
* @brief 
*
*  Lists all the devices, let the user choose from them and print the settings of
*  selected Camera and then Initialise it and Capture Frame and save it into memory
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
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <errno.h>

/* --- Project Includes --- */
#include "VideoFunctions.h"


using namespace std;

/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */



/** 
 *  @brief 
 *  
 *  Lists all the devices, let the user choose from them and print the settings of
 *  selected Camera and then Initialise it and Capture Frame and save it into memory
 *  
 *  @return 0 on success and -1 on failure
 */


int main() {

    struct initCapture device1;                  // creates a new object device1

    int k;                                      // Integer to store the choice of device for the user
    char device_id[100];                        // char to store the device id

    loadJsonConfig();

    cout<<"Number of cameras available: \n";

    if(ListActiveCameras()==0){                                       //  Checks if device is present or not Prints and proceed on success else Abort
    
    cout<<"\nChoose from Devices:\n { 0 , 1 , 2 , 3 }"<<endl;           // Print out the options for User
    cin>>k;                                                             // Get the value of k

    if(k==0) strcpy(device_id,"/dev/video0");                               // Copey the device id according to the given input of k
    else if(k==1) strcpy(device_id,"/dev/video1");
    else if(k==2) strcpy(device_id,"/dev/video2");
    else if(k==3) strcpy(device_id,"/dev/video3");
    else {
    printf("Error, Enter a valid number \n");
    return -1;                                                      // if wrong input return -1 and print the error
    }
      

    strcpy(device1.loc,device_id);                   // copying the device id in device1.loc

    ReadCameraSettings(device1);                                // Read Camera settings from kernel
   
    CaptureFrametoMem(device1);                         // Captures frame and save it into memory

    }
    else
    {
        cout<<"Error:No Device Found!!!!"<<endl;              // Prints Error if no divice is found
        return -1;
    }
    
    return 0;
}



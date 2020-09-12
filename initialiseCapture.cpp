/**
* @file initialiseCapture.cpp
* @brief
*
*  Lists all the devices, Load device number from JSON file and print the settings of
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
#include <string>
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
 *  Lists all the devices, loads device loc from JSON and print the settings of
 *  selected Camera and then Initialise it and Capture Frame and save it into memory
 *
 *  @return 0 on success and -1 on failure
 */


int main() {

    initCapture device1;                  // creates a new object device1

    cout<<"Number of cameras available: \n";

    if(ListActiveCameras()==0) {                                      //  Checks if device is present or not Prints and proceed on success else Abort

        loadJsonConfig(device1,"device");                                             // Loads the JSON document for the device number

        int fd= initCamera(device1);                             // Initialise Camera and opens it

        ReadCameraSettings(device1,fd);                                // Read Camera settings from kernel

        CaptureFrametoMem(device1,fd);                         // Captures frame and save it into memory

    }
    else
    {
        cout<<"Error:No Device Found!!!!"<<endl;              // Prints Error if no divice is found
        return -1;
    }

    return 0;
}



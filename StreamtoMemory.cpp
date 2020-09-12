/**
* @file StreamtoMemory.cpp
* @brief
*   Captures to Stream of frames into OpenCV array
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
 *  Captures to Stream of frames into Mat array
 *
 *  @return 0 on success and -1 on failure
 */

int main() {
    
    struct initCapture device1;                  // creates a new object device1

    cout<<"Number of cameras available: \n";

    if(ListActiveCameras()==0) {                                      //  Checks if device is present or not Prints and proceed on success else Abort

        loadJsonConfig(device1,"device");                                             // Loads the JSON document for the device number

        int fd=initCamera(device1);                                 // Initialise Camera

        CaptureStreamtoMem(device1,fd);                             // call function to CaptureStreamtoMem
        

    }
    else
    {
        cout<<"Error:No Device Found!!!!"<<endl;              // Prints Error if no divice is found
        return -1;
    }

    return 0;

}
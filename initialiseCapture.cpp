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
#include <fstream>

/* --- include/rapidjson Includes --- */

#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/ostreamwrapper.h"
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/error/en.h"

/* --- Project Includes --- */
#include "VideoFunctions.h"

#define SI_CONFIG_FILE "config.json"
#define JSON_MAX_READ_BUF_SIZE 65536

using namespace rapidjson;
using namespace std;

/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */



/* Declare a JSON document. JSON document parsed will be stored in this variable */
static Document config;

/**
 * @brief Parse and store JSON document into global variable
 *
 * @return int8_t 0 on SUCCESS and -1 on FAILURE
 * 
 */

int8_t loadJsonConfig()
{
    int8_t ret = -1;
    /* Open the example.json file in read mode */
    FILE *fp = fopen(SI_CONFIG_FILE, "rb");

    if (fp != NULL) {
        /* Declare read buffer */
        char readBuffer[JSON_MAX_READ_BUF_SIZE];
        /* Declare stream for reading the example stream */
        FileReadStream frstream(fp, readBuffer, sizeof(readBuffer));
        /* Parse example.json and store it in `d` */
        config.ParseStream(frstream);
        ParseResult ok = config.ParseStream(frstream);

        if (!ok) {
            fprintf(stderr, "Error Reading JSON config file: JSON parse error: %s (%u)",
                    GetParseError_En(ok.Code()), ok.Offset());
        }

        ret = 0;

    } else {
        fprintf(stderr,"Error Reading JSON config file: %s", strerror(errno));
    }

    /* Close the example.json file*/
    fclose(fp);
    return ret;
}

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



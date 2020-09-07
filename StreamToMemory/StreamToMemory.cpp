/**
* @file StreamToMemory.cpp
* @brief 
*
* Captures Stream and save it to memory
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

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/** 
 *  @brief 
 *  
 *  Capture Stream and Saves it into Memory
 *  
 *  @return 0 on success and -1 on failure
 */

int main(int argc, char* argv[])
{
    //Open the default video camera
    VideoCapture cap(0);

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video camera" << endl;
        return -1;
    }

    int frame_width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH)); //get the width of frames of the video
    int frame_height = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT)); //get the height of frames of the video
    
    Size frame_size(frame_width, frame_height);
    int frames_per_second = 10;

    //Create and initialize the VideoWriter object 
    VideoWriter oVideoWriter("MyVideo.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 
                                                               frames_per_second, frame_size, true); 
    
    //If the VideoWriter object is not initialized successfully, exit the program
    if (oVideoWriter.isOpened() == false) 
    {
        cout << "Cannot save the video to a file" << endl;
        return -1;
    }

    string window_name = "My Camera Feed";
    namedWindow(window_name); //create a window called "My Camera Feed"

    while (true)
    {
        Mat frame;
        bool isSuccess = cap.read(frame); // read a new frame from the video camera
        flip(frame, frame, 1);              // to see as in a mirror

        //Breaking the while loop if frames cannot be read from the camera
        if (isSuccess == false)
        {
            cout << "Video camera is disconnected" << endl;
            cin.get(); //Wait for any key press
            break;
        }

        /*
        Make changes to the frame as necessary
        e.g.  
         1. Change brightness/contrast of the image
         2. Smooth/Blur image
         3. Crop the image
         4. Rotate the image
         5. Draw shapes on the image
        */

        //write the video frame to the file
        oVideoWriter.write(frame); 

        //show the frame in the created window
        imshow(window_name, frame);

        //Wait for for 10 milliseconds until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If any other key is pressed, continue the loop 
        //If any key is not pressed within 10 milliseconds, continue the loop 
        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by the user. Stopping the video" << endl;
            break;
        }
    }

    //Flush and close the video file
    oVideoWriter.release();
    
    // Close the window file
    destroyWindow(window_name);

    return 0;
}


//  https://www.opencv-srf.com/2018/01/save-images-and-videos-to-file.html

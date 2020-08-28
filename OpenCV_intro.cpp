/** @file OpvenCV_intro.c
 *  @brief Capturing image and adding effects
 *  
 *  @author Dibyendu 
 *  @bug I didn't find any  
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
#include <opencv2/opencv.hpp>


/* --- Project Includes --- */
using namespace std; 
using namespace cv; 

/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */



/** 
 *  @brief Description on main
 *  
 * Taking clip from webcam and applying effects
 * 
 *
 *  @return List all Function returns 
 */

int main(){

// all variables for saving the changes made
    Mat frame;

    Mat BGR;
    Mat Grayscale;
    Mat cropped;
    Mat flipped;
    Mat Normalised;
    Mat resized;

    VideoCapture cap(0); 

   // Check if camera opened successfully
    if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    namedWindow("Webcam", CV_WINDOW_AUTOSIZE);

    while(1){

     
        // Capture frame-by-frame
        cap >> frame;
        
        // show the image taken
        imshow("Webcam", frame);

        // wait 1 sec, break immediately
        if (waitKey(1000)>=0)
                break;

    
}
    while(1){
        resize(frame, resized, Size(100, 100));

        imshow("Resized", resized);

        // wait 1 sec, break immediately
        if (waitKey(1000)>=0)
                break;
    }

    while(1){
        flip(frame, flipped, 1);

        imshow("flipped", flipped);

        // wait 1 sec, break immediately
        if (waitKey(1000)>=0)
                break;
    }

// convert the image to gray
    while(1){
          // convert the image to gray
        cvtColor(frame, Grayscale, CV_BGR2GRAY);
        // show the image taken
        imshow("greyscale", Grayscale);

        imwrite("me.jpg", Grayscale);

        // wait 1 sec, break immediately
        if (waitKey(1000)>=0)
        break;
}
// convert the image to BGR
    while(1){

        cvtColor(frame, BGR, CV_RGB2BGR);
        // show the image taken
        imshow("BGR", BGR);

        // wait 1 sec, break immediately
        if (waitKey(1000)>=0)
                break;
    }

    while(1){
        Rect crop_region(88,12,239,222);
        cropped = frame(crop_region).clone();
        
        imshow("Cropped", cropped);

        // wait 1 sec, break immediately
        if (waitKey(1000)>=0)
                break;
    }

    while(1){
         normalize(frame,Normalised, 0,1);

         imshow("Normalised", Normalised);

        // wait 1 sec, break immediately
        if (waitKey(1000)>=0)
        break;
    }
    
        
    return 0;
}
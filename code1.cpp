#include <iostream>
#include <cstdlib>
#include <tsanalyser/tsanalyser.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{

    /* Start Keeping time before the Key Task */
    startKeepingTime();

    //initialize and allocate memory to load the video stream from camera 
    cv::VideoCapture camera0(0);
  //  cv::VideoCapture camera1(1);

    if( !camera0.isOpened() ){
        cout<<"Error in opening Camera 0"<<endl;
        return -1;
    } 
   // if( !camera1.isOpened() ) return -1;

  //  while(true) {
        //grab and retrieve each frames of the video sequentially 
        cv::Mat3b frame0;
        camera0 >> frame0;
        

     //   cv::imshow("Video0", frame0);

        //wait for 40 milliseconds
    //    int c = cvWaitKey(40);

        //exit the loop if user press "Esc" key  (ASCII value of "Esc" is 27) 
       // if(27 == char(c)) break;
 //   }

    // Get the frame
    double fps = camera0.get(CAP_PROP_FPS); 
    cout << "Frames per seconds : " << fps << endl;
    Mat save_img; camera0 >> save_img;
    if(save_img.empty())
    {
        std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
    }

    // Save the frame into a file
    imwrite("test1.jpg", save_img); // A JPG FILE IS BEING SAVED

       getTimeTaken(DEBUG_MODE);

        /*Print total time taken and total RAM usage*/
       getTSAnlaysis(DEBUG_MODE);

    return 0;
}
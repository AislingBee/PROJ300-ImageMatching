// my header files
#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//My Headers
#include "matching.hpp"
#include "checkloaded.hpp"

using namespace std;
using namespace cv;

// paths to images used in code
#define TEMPLATE_PATH "../images/blackX_centre.png"
#define TEST_PATH "../images/blackX_more.png"


int main()
{
    Mat img_template;
    Mat test_input;

    const char *vid_window = "Video Feed with Match Square";
    namedWindow(vid_window, WINDOW_AUTOSIZE);
    const char *match_results = "Image Matching";
    namedWindow(match_results, WINDOW_AUTOSIZE);

    // Open the Default Camera on laptop
    VideoCapture input_cap;

    /* https://docs.opencv.org/4.x/d8/dfe/classcv_1_1VideoCapture.html
    open the default camera using default API
    cap.open(0);
    OR advance usage: select any API backend*/
    int deviceID = 0;             // 0 = open default camera
    int apiID = CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    input_cap.open(deviceID, apiID);

    // Check if camera is opened
    if (!CameraOpen(input_cap)){
        return-1;}

    // Open the template and test images
    img_template = imread(TEMPLATE_PATH);
    //cvtColor(img_template,img_template,COLOR_BGR2GRAY);
    if (!ImageLoad(img_template)){
        return -1;}

    test_input = imread(TEST_PATH);
    if (!ImageLoad(test_input)){
        return -1;}


    while(1){
        Mat img;
        Mat cap_frame;

        // Read the camera input
        input_cap.read(cap_frame);
        if (!ImageLoad(cap_frame)){
            return -1;}

        cap_frame.copyTo(img);
        //test_input.copyTo(img);
        //cvtColor(cap_frame,cap_frame,COLOR_BGR2GRAY);

        // match input frames to template
        Mat result = MatchFrames(cap_frame,img_template,img);
        //Mat result = MatchFrames(test_input,img_template,img);


        // Display the windows :)
        imshow(vid_window,img);
        imshow(match_results,result);
        waitKey(1);
    }

    return 0;
}





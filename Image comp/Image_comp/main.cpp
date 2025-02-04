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
//#define TEMPLATE_PATH "../images/blackX_centre.png"
//#define TEST_PATH "../images/blackX_more.png"
#define TEMPLATE_PATH "../images/cat_template.png"
#define TEST_PATH "../images/cat.png"
#define TEST true
#define CAMERA 1
// 0 = open default camera

int main()
{
    Mat img_template;
    VideoCapture input_cap;
    Mat test_input;

    // Load and name windows
    const char *vid_window = "Video Feed with Match Square";
    namedWindow(vid_window, WINDOW_AUTOSIZE);
   // const char *match_results = "Image Matching";
   // namedWindow(match_results, WINDOW_AUTOSIZE);

    // Open the template and test images
    img_template = imread(TEMPLATE_PATH);
    if (!ImageLoad(img_template))
    {
        return -1;
    }

    if (TEST==true)
    {
        test_input = imread(TEST_PATH);
        if (!ImageLoad(test_input))
        {
            return -1;
        }
    }
    else{
        /* https://docs.opencv.org/4.x/d8/dfe/classcv_1_1VideoCapture.html
        open the default camera using default API
        OR advance usage: select any API backend*/
        int deviceID = CAMERA;
        int apiID = CAP_ANY;      // 0 = autodetect default API
        input_cap.open(deviceID, apiID);

        // Check if camera is opened
        if (!CameraOpen(input_cap))
        {
            return-1;
        }
    }

    while(1)
    {
        double Val;
        Point Loc;
        Mat img;
        Mat result;
        Mat scalRot_templ;
        Mat scaled_templ;
        // see if we load the test frame or camera
        if (TEST==false)
        {
            // Read the camera input
            Mat cap_frame;
            input_cap.read(cap_frame);
            if (!ImageLoad(cap_frame)){
                return -1;
            }
            cap_frame.copyTo(img);

            double scales[]={0.25,0.5,1};
            double angles[]={0,45,90,135,180,225,270,315};
            for(double j:scales){
                for(int i:angles){

                    scaled_templ= ScaleTemplate(img_template,j);
                    scalRot_templ= RotateTemplate(scaled_templ,i);

                    result=CheckMatch(test_input,scalRot_templ,&Loc,&Val);
                    double match_high=0.2;
                    double match_low=0.0009;

                    if (match_low<Val&&Val<match_high)
                    {
                        DrawResults(img,img_template,Loc,draw_rectangle);
                    }
                }
            }
        }

        else
        {
            // TEST CODE FOR WHEN NEEDED //
            test_input.copyTo(img);
            //result = MatchFrames(test_input,img_template,img,i);
            // TO DO! MOVE THIS ALL TO MATCHING.CPP
            double scales[]={0.25,0.5,1};
            double angles[]={0,45,90,135,180,225,270,315};
            for(double j:scales){
                for(int i:angles){

                    scaled_templ= ScaleTemplate(img_template,j);
                    scalRot_templ= RotateTemplate(scaled_templ,i);

                    result=CheckMatch(test_input,scalRot_templ,&Loc,&Val);
                    double match_high=0.2;
                    double match_low=0.0009;

                    if (match_low<Val&&Val<match_high)
                    {
                        DrawResults(img,img_template,Loc,draw_rectangle);
                       // result = MatchFrames(test_input,scalRot_templ,img,i,j);
                    }
                    // match input frames to template
                    //result = MatchFrames(cap_frame,img_template,img);
                    // imshow("template",img_template);
                    //imshow("rot_template",scalRot_templ);
                    //waitKey(1);
                }
            }

        }

        // Display the windows :)
        imshow(vid_window,img);
        //imshow(match_results,result);
        waitKey(1);
    }
    return 0;
}





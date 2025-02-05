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
#define TEMPLATE_PATH "../images/cat_template_0.5.png"
#define TEST_PATH "../images/cat.png"
#define TEST true
#define CAMERA 1
// 0 = open default camera

int main()
{
    Mat img_template;
    VideoCapture input_cap;
    Mat test_input;
    Mat test_input2;
    Mat test_input3;

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
        test_input2 = imread("../images/cat_90.png");
        test_input3 = imread("../images/cat_90_0.5.png");
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
        Point Loc;
        Mat img, result, scalRot_templ, scaled_templ;
        double Val;
        double match_high=0.1;
        double match_low=0.0009;
        bool Match_found=false;
        double scales[]={0.25,0.5,1,1.5,2};
        double angles[]={0,45,90,135,180,225,270,315};
        Mat cats[]={test_input,test_input2,test_input3};
        // 8*3 = 24 checks for each frame... is that too much?

        //Mat result;
        //Mat scalRot_templ;
        //Mat scaled_templ;


        // see if we load the test frame or camera
        if (TEST==false)
        {
            // Read the camera input
            Mat cap_frame;
            input_cap.read(cap_frame);
            if (!ImageLoad(cap_frame))
            {
                return -1;
            }
            cap_frame.copyTo(img);

            // Check for match
            while(Match_found==false)
            {
                for(double j:scales)
                {
                    for(int i:angles)
                    {
                        scaled_templ= ScaleTemplate(img_template,j);

                        if((scaled_templ.size().height>img.size().height)||(scaled_templ.size().width>img.size().width)){
                            clog<<"skipped due to non matching sizes\n";
                        }
                        else{
                            scalRot_templ= RotateTemplate(scaled_templ,i);
                            result=CheckMatch(cap_frame,scalRot_templ,&Loc,&Val);

                        if (match_low<Val&&Val<match_high)
                        {
                            DrawResults(img,scalRot_templ,Loc,draw_rectangle);
                            Match_found=true;
                        }}
                    }
                }
            }
        }

        else
        {

            // TEST CODE FOR WHEN NEEDED //
            for (Mat c:cats)
            {
                Match_found=false;
                c.copyTo(img);
                cvtColor(img,img,COLOR_RGB2GRAY);
                // TO DO! MOVE THIS ALL TO MATCHING.CPP?

                // while means the for loops stop when match is found
                while(Match_found==false)
                {
                    for(double j:scales)
                    {
                        for(int i:angles)
                        {
                            scaled_templ= ScaleTemplate(img_template,j);
                            scalRot_templ= RotateTemplate(scaled_templ,i);

                            if((scalRot_templ.size().height>img.size().height)||(scalRot_templ.size().width>img.size().width))
                            {
                                clog<<"skipped due to non matching sizes\n";
                            }
                            else
                            {
                            result=CheckMatch(c,scalRot_templ,&Loc,&Val);

                            //clog<<"val: "<<Val<<"\n";
                            if (match_low<Val&&Val<match_high)
                            {
                                DrawResults(img,scalRot_templ,Loc,draw_rectangle);
                                Match_found=true;
                                // clog<<"match found \n";
                            }}
                        }
                    }
                    if (Match_found==false){
                        DrawResults(img,img_template,Point (0,0), draw_rectangle);
                    }
                }
                imshow(vid_window,img);//waitKey(1);
                waitKey(1);
            }

            // Display the windows :)
            // imshow("rot_template",scalRot_templ);

            //imshow(match_results,result);
        }
    }
    return 0;
}





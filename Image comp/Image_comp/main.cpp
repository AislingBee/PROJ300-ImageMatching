// my header files
#include <iostream>
#include <vector>
#include <thread>
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
#define TEST false
#define CAMERA 0
// 0 = open default camera
void displayWindows(Mat img_template,Mat img);
int main()
{
    Mat img_template;
    VideoCapture input_cap;
    Mat test_input;
    Mat test_input2;
    Mat test_input3;
    Mat test_input4;

    // Load and name windows
    // const char *vid_window = "Video Feed with Match Square";
    // namedWindow(vid_window, WINDOW_AUTOSIZE);
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
        test_input4 = imread("../images/blackX_more.png");
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
        // Point Loc;
        Mat img, result, scalRot_templ, scaled_templ;
        //double Val;
        bool Match_found=false;


        //thread display (displayWindows,img_template,cap_frame);
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


            //thread match (ScaleandMatch(cap_frame,img_template));
            // Check for match
            double scale;
            Match_found= ScaleandMatch(cap_frame,img_template,&scale);

            if (Match_found==false)
            {
                putText(img,"X",Point(img.size().width/2,img.size().height/2),2,2.0,Scalar(0,0,200),2,2,0);
                //Match_found=true;// figure out a better solution for this
            }
            else{
                putText(img,"match found",Point(img.size().width/2,img.size().height/2),2,2.0,Scalar(0,0,200),2,2,0);// DrawResults(img,scalRot_templ,Loc,draw_rectangle);
            }
        }

        imshow("template",img_template);
        imshow("vid_window",img);//waitKey(1);
        waitKey(1);

        }

        // else
        // {
        //     break;
        //     Mat cats[]={test_input,test_input2,test_input3,test_input4};
        //     // TEST CODE FOR WHEN NEEDED //
        //     for (Mat c:cats)
        //     {
        //         c.copyTo(img);
        //         Match_found=false;
        //         // TO DO! MOVE THIS ALL TO MATCHING.CPP?

        //         // while means the for loops stop when match is found
        //         while(Match_found==false)
        //         {
        //             for(double j:scales)
        //             {
        //                 for(int i:angles)
        //                 {
        //                     scalRot_templ=ScaleandRotateTemplate(img_template,i,j);

        //                     if((scalRot_templ.size().height>img.size().height)||(scalRot_templ.size().width>img.size().width))
        //                     {
        //                         //clog<<"skipped due to non matching sizes\n";
        //                         break;
        //                     }
        //                     else
        //                     {
        //                         result=CheckMatch(c,scalRot_templ,&Loc,&Val);

        //                         if (match_low<Val&&Val<match_high)
        //                         {
        //                             DrawResults(img,scalRot_templ,Loc,draw_rectangle);
        //                             Match_found=true;
        //                             // clog<<"match found \n";
        //                         }
        //                     }
        //                 }
        //             }
        //             if (Match_found==false)
        //             {
        //                 putText(img,"X",Point(img.size().width/2,img.size().height/2),2,2.0,Scalar(0,0,200),2,2,0);
        //                 Match_found=true;// figure out a better solution for this
        //             }
        //         }
        //         imshow(vid_window,img);//waitKey(1);
        //         waitKey(1);
        //     }

        //     // Display the windows :)
        //     // imshow("rot_template",scalRot_templ);
        //     // imshow(match_results,result);
        // }
        // putText(img,to_string(Val),Point(img.size().width/2,img.size().height/2),2,2.0,Scalar(0,0,200),2,2,0);

        // imshow(vid_window,img);//waitKey(1);
        //  waitKey(1);
    //}
    return 0;
}

void displayWindows(Mat img_template,Mat img)
{
    imshow("template",img_template);
    imshow("vid_window",img);//waitKey(1);
    waitKey(1);
}

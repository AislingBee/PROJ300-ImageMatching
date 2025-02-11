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
#include "testparams.hpp"

#define TEMPLATE_PATH "../images/cat_template_0.5.png"
#define TEST false
#define CAMERA 0    // 0 = open default camera

using namespace std;
using namespace cv;

void displayWindows(Mat img_template,Mat img);

int main()
{
    Mat img_template;
    VideoCapture input_cap;

    // Open the template and test images
    img_template = imread(TEMPLATE_PATH);
    if (!ImageLoad(img_template))
    {
        return -1;
    }

    // check if this is test, if so load test images
    if (TEST==true)
    {
        int i =0;
        for (const char *test_img:testpaths)
        {
            test_input = imread(test_img);
            if (!ImageLoad(test_input))
            {
                return -1;
            }
            testImgArr[i]=test_input;
            i++;
        }
    }
    else    // if not test open camera instead
    {
        /*
        https://docs.opencv.org/4.x/d8/dfe/classcv_1_1VideoCapture.html
        open the default camera using default API OR advance usage: select any API backend
        */
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
        Mat img, result, scalRot_templ, scaled_templ;
        bool Match_found=false;

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
            double scale;
            Point Loc;
            Match_found= ScaleandMatch(cap_frame,img_template,&scale,&Loc);

            if (Match_found==false)
            {
                putText(img,"X",Point(img.size().width/2,img.size().height/2),2,2.0,Scalar(0,0,200),2,2,0);
            }
            else
            {
                putText(img,"match found",Point(img.size().width/2,img.size().height/2),2,2.0,Scalar(0,0,200),2,2,0);
                scalRot_templ=ScaleandRotateTemplate(img_template,0.0,scale);
                DrawResults(img,scalRot_templ,Loc,draw_rectangle);
            }
            imshow("template",img_template);
            imshow("vid_window",img);//waitKey(1);
            waitKey(1);
        }
        else    //TEST=True
        {
            for (Mat c:testImgArr)
            {
                c.copyTo(img);
                double scale;
                Point Loc;
                Match_found= ScaleandMatch(c,img_template,&scale,&Loc);

                if (Match_found==false)
                {
                    putText(img,"X",Point(img.size().width/2,img.size().height/2),2,2.0,Scalar(0,0,200),2,2,0);
                    //Match_found=true;// figure out a better solution for this
                }
                else
                {
                    putText(img,"match found",Point(20,50),2,2.0,Scalar(0,0,200),2,2,0);
                    scalRot_templ=ScaleandRotateTemplate(img_template,0.0,scale);
                    DrawResults(img,scalRot_templ,Loc,draw_rectangle);
                }
                imshow("template",img_template);
                imshow("vid_window",img);//waitKey(1);
                waitKey(1);
            }

        }



        }
    return 0;
}

void displayWindows(Mat img_template,Mat img)
{
    // Load and name windows
    // const char *vid_window = "Video Feed with Match Square";
    // namedWindow(vid_window, WINDOW_AUTOSIZE);
    // const char *match_results = "Image Matching";
    // namedWindow(match_results, WINDOW_AUTOSIZE);
    imshow("template",img_template);
    imshow("vid_window",img);//waitKey(1);
    waitKey(1);
}

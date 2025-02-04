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
#define TEST false
#define CAMERA 1
// 0 = open default camera

int main()
{
    Mat img_template;

    // Load and name windows
    const char *vid_window = "Video Feed with Match Square";
    namedWindow(vid_window, WINDOW_AUTOSIZE);
    const char *match_results = "Image Matching";
    namedWindow(match_results, WINDOW_AUTOSIZE);

    /* https://docs.opencv.org/4.x/d8/dfe/classcv_1_1VideoCapture.html
    open the default camera using default API
    OR advance usage: select any API backend*/
    VideoCapture input_cap;
    int deviceID = CAMERA;
    int apiID = CAP_ANY;      // 0 = autodetect default API
    input_cap.open(deviceID, apiID);

    // Check if camera is opened
    if (!CameraOpen(input_cap))
    {
        return-1;
    }

    // Open the template and test images
    img_template = imread(TEMPLATE_PATH);
    if (!ImageLoad(img_template))
    {
        return -1;
    }

    Mat test_input;
    if (TEST==true)
    {
        test_input = imread(TEST_PATH);
        if (!ImageLoad(test_input))
        {
            return -1;
        }
    }

    while(1)
    {
        Mat img;
        Mat result;
        Mat rotated_templ;
        // see if we load the test frame or camera
        if (TEST==false)
        {
            Mat cap_frame;
            // Read the camera input
            input_cap.read(cap_frame);
            if (!ImageLoad(cap_frame)){
                return -1;
            }
            cap_frame.copyTo(img);

            //rotate template
// #include<iostream>
//             using namespace std;
//             int main()
//             {
//                 int arr[]={1,2,3,4,5};   //array initialization
//                 cout<<"The elements are: ";
//                 for(int i : arr)
//                 {
//                     cout<<i<<" ";
//                 }
//                 return 0;
//             }
            double arr[]={0,45,90,135,180,225,270,315};
            for(int i:arr){

                rotated_templ= RotateTemplate(img_template,i);
                result = MatchFrames(cap_frame,rotated_templ,img,i);
                // match input frames to template
                //result = MatchFrames(cap_frame,img_template,img);
                imshow("template",img_template);
                imshow("rot_template",rotated_templ);
            waitKey(1);
            }
        }

        else
        {
            test_input.copyTo(img);
            //result = MatchFrames(test_input,img_template,img,i);
            double arr[]={0,45,90,135,180,225,270,315};
            for(int i:arr){
                //clog<<i<<"\n";
                rotated_templ= RotateTemplate(img_template,i);
                result = MatchFrames(test_input,rotated_templ,img,i);
                // match input frames to template
                //result = MatchFrames(cap_frame,img_template,img);
                imshow("template",img_template);
                imshow("rot_template",rotated_templ);
            //test template scale and rotation
           // Mat scaled=ScaleTemplate(img_template,0.5);
            //imshow("0.5",scaled);
            //Mat rotate=RotateTemplate(img_template,90);
            //imshow("90",rotate);
            waitKey(1);

            }
            //
        }

        imshow(vid_window,img);
        imshow(match_results,result);
        // Display the windows :)

        waitKey(1);
    }

    return 0;
}





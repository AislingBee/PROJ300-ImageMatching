// my header files
#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "matching.hpp"

using namespace std;
using namespace cv;


bool ImageLoad(Mat);

int main()
{
    Mat img_template;
    Mat test_input;

    //QCoreApplication a(argc, argv);
    const char *vid_window = "Video Feed with Match Square";
    namedWindow(vid_window, WINDOW_AUTOSIZE);
    const char *match_results = "Image Matching";
    namedWindow(match_results, WINDOW_AUTOSIZE);

    // Open the Default Camera
    VideoCapture input_cap(0);
    if (!input_cap.isOpened()) {
        cerr << "Error: Unable to open camera\n";
        return -1;
    }

    // Open the template and test image
    img_template = imread("../images/blackX_centre.png");
    ImageLoad(img_template);
    test_input = imread("../images/blackX_more.png");
    ImageLoad(test_input);

    while(1){
        // Read the camera input
        Mat cap_frame;
        input_cap.read(cap_frame);
        ImageLoad(cap_frame);

        Mat img;
        cap_frame.copyTo(img);

        // match input image to template
        Mat result = MatchFrames(cap_frame,img_template,img);

        // Display the windows :)
        imshow(vid_window,img);
        imshow(match_results,result);
        waitKey(1);
    }

    return 0;
}

// Functions
bool ImageLoad(Mat image)
{
    if(image.empty())
    {
        cout<<"Error: Image cant be loaded"<<endl;
        return false;
    }
    return true;
}




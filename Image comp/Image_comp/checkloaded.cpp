#include "checkloaded.hpp"
#include <iostream>

#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

bool ImageLoad(Mat image)
{
    if(image.empty())
    {
        cerr<<"Error: Image "<<"do this later"<<" cant be loaded\n";
        return false;
    }
    return true;
}

bool CameraOpen(VideoCapture cap)
{
    if (!cap.isOpened()) {
        cerr << "Error: Unable to open camera\n";
        return false;
    }
    return true;
}

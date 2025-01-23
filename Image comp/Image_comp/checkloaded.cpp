#include "checkloaded.hpp"

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

#ifndef CHECKLOADED_HPP
#define CHECKLOADED_HPP
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace std;
using namespace cv;


bool ImageLoad(Mat);
bool CameraOpen(VideoCapture);



#endif // CHECKLOADED_HPP

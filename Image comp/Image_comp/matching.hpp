#ifndef MATCHING_HPP
#define MATCHING_HPP
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;



void SetupHoughGuilParams(Mat templ,Ptr<GeneralizedHoughGuil> guil);
Mat ScaleandRotateTemplate(Mat templ, double angle, double scale);
Mat CheckMatch(Mat frame, Mat templ,Point* matchLoc, double* matchVal);
bool ScaleandMatch(Mat frame, Mat templ, double* scale, Point* Loc);




#endif // MATCHING_HPP

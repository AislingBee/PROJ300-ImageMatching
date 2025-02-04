#ifndef MATCHING_HPP
#define MATCHING_HPP
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat RotateTemplate(Mat templ, double angle);
Mat ScaleTemplate(Mat templ, double scale);
Mat CheckMatch(Mat frame, Mat templ,Point* matchLoc, double* matchVal);
/*
    Uses rectangle, matchTemplate (TM_SQDIFF_NORMED) and normalize (NORM_MINMAX) from opencv2/imgproc, minMaxLoc from opencv2/core.
    Returns result from match template and draws rectangles around closest match over the 'img' frame.
*/

Mat MatchFrames(Mat frame,Mat image_template,Mat img,double angle,double scale);

// not really useful, may remove
enum draw{
    draw_rectangle=1,
    draw_text=2
};
void DrawResults(Mat frame,Mat templ,Point location,draw shape);


#endif // MATCHING_HPP

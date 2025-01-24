#ifndef MATCHING_HPP
#define MATCHING_HPP
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

/*
    Uses rectangle, matchTemplate (TM_SQDIFF_NORMED) and normalize (NORM_MINMAX) from opencv2/imgproc, minMaxLoc from opencv2/core.
    Returns result from match template and draws rectangles around closest match over the 'img' frame.
*/
Mat MatchFrames(Mat frame,Mat image_template,Mat img);

#endif // MATCHING_HPP

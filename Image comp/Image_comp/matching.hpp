#ifndef MATCHING_HPP
#define MATCHING_HPP

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

Mat MatchFrames(Mat,Mat,Mat);

// Mat MatchFrames(Mat frame, Mat templ, Mat img)
// {
//     Mat result;
//     // int result_cols = img.cols - templ.cols + 1;
//     // int result_rows = img.rows - templ.rows + 1;

//     // result.create( result_rows, result_cols, CV_32FC1 );

//     // match template to the camera frame
//     matchTemplate(frame, templ, result,TM_SQDIFF_NORMED);
//     normalize(result,result,0,1, NORM_MINMAX, -1,Mat());

//     double minVal, maxVal;
//     Point minLoc, maxLoc, matchLoc;

//     minMaxLoc(result,&minVal,&maxVal,&minLoc,&maxLoc,Mat());
//     matchLoc=minLoc;

//     // drawing the results
//     rectangle(img,matchLoc,Point(matchLoc.x+templ.cols,matchLoc.y+templ.rows),Scalar(0,0,0),2,8,0);
//     rectangle(result,matchLoc,Point(matchLoc.x+templ.cols,matchLoc.y+templ.rows),Scalar(0,0,0),2,8,0);
//     return result;

// }
#endif // MATCHING_HPP

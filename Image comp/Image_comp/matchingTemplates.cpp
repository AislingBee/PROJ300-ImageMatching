#include "matchingTemplates.h"

// void MatchFrames()
// {
//     cap_frame.copyTo(img);
//     int result_cols = img.cols - img_template.cols + 1;
//     int result_rows = img.rows - img_template.rows + 1;

//     result.create( result_rows, result_cols, CV_32FC1 );

//     // match template to the camera frame
//     matchTemplate(cap_frame, img_template, result,TM_SQDIFF_NORMED);
//     normalize(result,result,0,1, NORM_MINMAX, -1,Mat());

//     double minVal, maxVal;
//     Point minLoc, maxLoc, matchLoc;

//     minMaxLoc(result,&minVal,&maxVal,&minLoc,&maxLoc,Mat());
//     matchLoc=minLoc;

//     // drawing the results
//     rectangle(img,matchLoc,Point(matchLoc.x+img_template.cols,matchLoc.y+img_template.rows),Scalar(0,0,0),2,8,0);
//     rectangle(result,matchLoc,Point(matchLoc.x+img_template.cols,matchLoc.y+img_template.rows),Scalar(0,0,0),2,8,0);
//     return;

// }

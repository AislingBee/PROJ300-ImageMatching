#include "matching.hpp"
bool ScaleandMatch(Mat frame, Mat templ)
{
    Mat scalRot_templ, result;
    Point Loc;
    double Val;
    double scales[]={1,0.5,1.5};
    double angles[]={0,90,180,270};
    double match_high=0.235;
    double match_low=0.0009;
// maybe do a standard check of 1 and 0 for scale and angle and if Val is below certain number then do the various scales and angles?
    //result=CheckMatch(frame,templ,&Loc,&Val);
    // if (Val>0.6){
    //     return false;
    // }
    // else{
    for(double j:scales)
    {
        for(int i:angles)
        {
            scalRot_templ=ScaleandRotateTemplate(templ,i,j);
            if((scalRot_templ.size().height<frame.size().height)||(scalRot_templ.size().width<frame.size().width))
            {
                result=CheckMatch(frame,scalRot_templ,&Loc,&Val);

                if (match_low<Val&&Val<match_high)
                {

                    return true;

                }
            }
        }
    }
    return false;
    }//}

Mat ScaleandRotateTemplate(Mat templ, double angle, double scale)
{
    Mat scaled_temp, scaled_rotate_temp, rotMatrix;

    // scale
    if (scale<1){
        resize(templ, scaled_temp, Size(), scale, scale, INTER_AREA);
    }else if (scale==1){
        scaled_temp=templ;
    }
    else{
        resize(templ, scaled_temp, Size(), scale, scale, INTER_LINEAR);
    }

    // rotate
    Point centrePoint (scaled_temp.size().width/2, scaled_temp.size().height/2);
    rotMatrix=getRotationMatrix2D(centrePoint,angle,1.0);
    warpAffine(scaled_temp,scaled_rotate_temp,rotMatrix,Size(scaled_temp.size().width,scaled_temp.size().height));

    // return
    return scaled_rotate_temp;
}

Mat CheckMatch(Mat frame, Mat templ, Point* matchLoc, double* matchVal)
{
    Mat result;
    double minVal, maxVal;
    Point minLoc, maxLoc;

    matchTemplate(frame, templ, result,TM_SQDIFF_NORMED);
    minMaxLoc(result,&minVal,&maxVal,&minLoc,&maxLoc,Mat());

    *matchLoc=minLoc;
    *matchVal=minVal;

    return result;
}

void DrawResults(Mat frame,Mat templ,Point location,draw shape){
    switch(shape)
    {
        case draw_rectangle:
            rectangle(frame,location,Point(location.x+templ.cols,location.y+templ.rows),Scalar(0,0,0),2,8,0);
            break;
        case draw_text:
            break;
    }

}
// Mat MatchRotatedFrames(Mat frame, Mat templ, Mat img)
// {
//     angles = {0,45,90,135,180,225,270,315,360};
//     //for (angles){
//     for (int va)
//     Mat rotated_frame = RotateTemplate(templ,i);
//     MatchFrames(frame,rotated_frame,img);
//         }
// }

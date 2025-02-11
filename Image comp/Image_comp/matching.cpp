#include "matching.hpp"

void SetupHoughGuilParams(Mat templ,Ptr<GeneralizedHoughGuil> guil)
{
    //  create guil and set options // green
    guil->setMinDist(10);   //10
    guil->setLevels(360);   //360
    guil->setDp(5); //3
    guil->setMaxBufferSize(1000);    //1000

    guil->setMinAngle(0);   //0
    guil->setMaxAngle(360); //360
    guil->setAngleStep(45); //1
    guil->setAngleThresh(500);  //1500

    guil->setMinScale(0.5); //0.5
    guil->setMaxScale(2.0); //2.0
    guil->setScaleStep(0.25);   //0.05
    guil->setScaleThresh(50);   //50

    guil->setPosThresh(50); //10

    guil->setCannyLowThresh(50);    //30
    guil->setCannyHighThresh(100);  //110

    guil->setTemplate(templ);
}

bool ScaleandMatch(Mat frame, Mat templ, double* scale, Point* Loc)
{
    Mat scalRot_templ, result;
    Point matchLoc;
    double Val;
    double scales[]={1,0.25,0.5,1.25,1.5,2};
    //double angles[]={0,90,180,270};
    double match_high=0.22;
    double match_low=0.0001;

    for(double j:scales)
    {
        scalRot_templ=ScaleandRotateTemplate(templ,0,j);
        if((scalRot_templ.size().height<frame.size().height)&&(scalRot_templ.size().width<frame.size().width))
        {
            result=CheckMatch(frame,scalRot_templ,&matchLoc,&Val);

            if (match_low<Val&&Val<match_high)
            {
                *scale=j;
                *Loc=matchLoc;
                return true;

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

    // rotate only bother if angle is changing
    if (angle>0.0||angle<0.0)
    {
        Point centrePoint (scaled_temp.size().width/2, scaled_temp.size().height/2);
        rotMatrix=getRotationMatrix2D(centrePoint,angle,1.0);
        warpAffine(scaled_temp,scaled_rotate_temp,rotMatrix,Size(scaled_temp.size().width,scaled_temp.size().height));
    }
    // return
    //return scaled_rotate_temp;
    return scaled_temp;
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

// Mat MatchRotatedFrames(Mat frame, Mat templ, Mat img)
// {
//     angles = {0,45,90,135,180,225,270,315,360};
//     //for (angles){
//     for (int va)
//     Mat rotated_frame = RotateTemplate(templ,i);
//     MatchFrames(frame,rotated_frame,img);
//         }
// }

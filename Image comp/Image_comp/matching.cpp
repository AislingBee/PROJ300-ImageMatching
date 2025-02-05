#include "matching.hpp"


Mat RotateTemplate(Mat templ, double angle)
{
    Mat rotate_temp;
    Point centrePoint (templ.size().width/2, templ.size().height/2);
    Mat rotMatrix=getRotationMatrix2D(centrePoint,angle,1.0);
    warpAffine(templ,rotate_temp,rotMatrix,Size(templ.size().width,templ.size().height));
    //rotate_temp=templ;
    return rotate_temp;
}

// scale 0.5 is 2x smaller
Mat ScaleTemplate(Mat templ, double scale)
{
    Mat scaled_temp;
    if (scale<1){
        resize(templ, scaled_temp, Size(), scale, scale, INTER_AREA);
    }else if (scale==1){
        scaled_temp=templ;
    }
    else{
        resize(templ, scaled_temp, Size(), scale, scale, INTER_LINEAR);
    }
    //scaled_temp=templ;
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

//double match_filter=4.0e-8;
Mat MatchFrames(Mat frame, Mat templ, Mat img,double angle,double scale)
{

    Mat result;

    // match template to the camera frame
    matchTemplate(frame, templ, result,TM_SQDIFF_NORMED);

    double minVal, maxVal;
    Point minLoc, maxLoc, matchLoc;

    minMaxLoc(result,&minVal,&maxVal,&minLoc,&maxLoc,Mat());
    matchLoc=minLoc;


    double match_high=0.2;
    double match_low=0.0009;

    if (match_low<minVal&&minVal<match_high){
    // drawing the results
        //cout<<"match found\n";
        clog<<"match found. angle: ["<<angle<<"] scale: ["<<scale<<"] |||| minVal: "<<minVal<<"\n";
        DrawResults(img,templ,matchLoc,draw_rectangle);
        DrawResults(result,templ,matchLoc,draw_rectangle);
        //rectangle(result,matchLoc,Point(matchLoc.x+templ.cols,matchLoc.y+templ.rows),Scalar(0,0,0),2,8,0);
        return result;
    }
    else{
        //cout<<"no match found\n";
        clog<<"no match found. angle: ["<<angle<<"] scale: ["<<scale<<"] |||| minVal: "<<minVal<<"\n";
        putText(img,"X",Point(100,100),2,2.0,Scalar(0,0,0),2,2,0);
        return result;
    }

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

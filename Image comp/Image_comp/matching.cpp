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
    resize(templ, scaled_temp, Size(), scale, scale, INTER_AREA);
    //scaled_temp=templ;
    return scaled_temp;
}

//double match_filter=4.0e-8;
Mat MatchFrames(Mat frame, Mat templ, Mat img)
{
    double match_filter=4.0e-8;
    Mat result;

    // match template to the camera frame
    matchTemplate(frame, templ, result,TM_SQDIFF_NORMED);
    normalize(result,result,0,1, NORM_MINMAX, -1,Mat()); // puts all results in the scale of 0-1

    double minVal, maxVal;
    Point minLoc, maxLoc, matchLoc;

    minMaxLoc(result,&minVal,&maxVal,&minLoc,&maxLoc,Mat());
    matchLoc=minLoc;

    //cout<<minVal<<"\n";
    if (minVal<match_filter){
    // drawing the results
        cout<<"match found\n";
        rectangle(img,matchLoc,Point(matchLoc.x+templ.cols,matchLoc.y+templ.rows),Scalar(0,0,0),2,8,0);
        rectangle(result,matchLoc,Point(matchLoc.x+templ.cols,matchLoc.y+templ.rows),Scalar(0,0,0),2,8,0);
        return result;
    }
    else{
        cout<<"no match found\n";
        putText(img,"X",Point(100,100),2,2.0,Scalar(0,0,0),2,2,0);
        return result;
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

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main()
{
	Mat imgBefore_gray,imgAfter_gray;
	Mat imgBefore=imread("digitalglobe-philippines-before.jpg",1); 
	Mat imgAfter=imread("digitalglobe-philippines-after.jpg",1); 

	cvtColor( imgBefore, imgBefore_gray, CV_BGR2GRAY );
	imshow( "Gray1",imgBefore_gray);
	threshold( imgBefore_gray, imgBefore_gray, 127, 255, 0 );
	imshow( "Thresholded1",imgBefore_gray);

    //Prepare the image for findContours
	cvtColor( imgAfter, imgAfter_gray, CV_BGR2GRAY );
	imshow( "Gray2",imgAfter_gray);
	threshold( imgAfter_gray, imgAfter_gray, 128, 255, 0 );
	imshow( "Thresholded2",imgAfter_gray);


    //Find the contours. Use the contourOutput Mat so the original image doesn't get overwritten
    std::vector<std::vector<cv::Point> > contours;
    cv::Mat contourOutput = imgBefore_gray.clone();
    cv::findContours( contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );

    cv::Scalar colors[3];
    colors[0] = cv::Scalar(255, 0, 0);
    colors[1] = cv::Scalar(0, 255, 0);
    colors[2] = cv::Scalar(0, 0, 255);
    
    // for (int i = 0; i < contours.size(); ++i)
    // {
    // 	for (int j = 0; j < countours[i].size()-1; ++j)
    // 	{
	   //  	int ht=countours[i][j+1].x-countours[i][j].x;
	   //  	int bt=countours[i][j+1].y-countours[i][j].y;
	   //  	if( maxHT<ht ) maxHT=ht;
	   //  	if( maxBT<bt ) maxBT=bt;
    // 	}
    // 	if( maxBT*maxHT < 100 )
    // 		countours[i].clear();
    // }
    //Draw the contours
    cv::Mat contourImage(imgBefore.size(), CV_8UC3, cv::Scalar(0,0,0));
    for (size_t idx = 0; idx < contours.size(); idx++) {
        cv::drawContours(contourImage, contours, idx, colors[idx % 3]);
    }

    imshow("Contours", contourImage);

	//Find the contours. Use the contourOutput Mat so the original image doesn't get overwritten
    std::vector<std::vector<cv::Point> > contours1;
    cv::Mat contourOutput1 = imgAfter_gray.clone();
    cv::findContours( contourOutput1, contours1, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );

    cv::Mat contourImage1(imgAfter.size(), CV_8UC3, cv::Scalar(0,0,0));
    for (size_t idx = 0; idx < contours1.size(); idx++) {
        cv::drawContours(contourImage1, contours1, idx, colors[idx % 3]);
    }
    imshow("Contours1", contourImage1);

    cout<<"Number of buildings before disaster : "<<contours.size()<<endl;
    cout<<"Number of buildings after  disaster : "<<contours1.size()<<endl;

    float percentageDamage=(double)(contours.size()-contours1.size())/contours.size()*100;
    cout<<"Degree of damage of the Selected Area : "<<percentageDamage<<endl;

	waitKey(0);
	return 0;

}

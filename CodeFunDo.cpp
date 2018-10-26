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
    

    int maxHT=INT_MIN,maxBT=INT_MIN;

	vector<Point>::const_iterator col,bol;
    vector< vector<Point> >::const_iterator row;

    int buildingsBefore=contours.size();
	
	for (row = contours.begin(); row != contours.end(); row++) 
	{
    	for (col = row->begin(); col != row->end(); col++) 
    	{
    		bol=col;
    		bol++;


	    	int ht= (*bol).x - (*col).x;
	    	int bt= (*bol).y - (*col).y;
	    	if( maxHT<ht ) maxHT=ht;
	    	if( maxBT<bt ) maxBT=bt;
	
    	}
    	if( maxBT*maxHT < 10 )
    		buildingsBefore--;
	    		// contours.erase(col);
    }


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

    int buildingsAfter=contours1.size();

	for (row = contours1.begin(); row != contours1.end(); row++) 
	{
    	for (col = row->begin(); col != row->end(); col++) 
    	{
    		bol=col;
    		bol++;


	    	int ht= (*bol).x - (*col).x;
	    	int bt= (*bol).y - (*col).y;
	    	if( maxHT<ht ) maxHT=ht;
	    	if( maxBT<bt ) maxBT=bt;
	
    	}
    	if( maxBT*maxHT < 10 )
    		buildingsAfter--;
    }
    cv::Mat contourImage1(imgAfter.size(), CV_8UC3, cv::Scalar(0,0,0));
    for (size_t idx = 0; idx < contours1.size(); idx++) {
        cv::drawContours(contourImage1, contours1, idx, colors[idx % 3]);
    }
    imshow("Contours1", contourImage1);

    cout<<"Number of buildings before disaster : "<<buildingsBefore<<endl;
    cout<<"Number of buildings after  disaster : "<<buildingsAfter<<endl;

    float percentageDamage=(double)(buildingsBefore- buildingsAfter )/buildingsBefore*100;
    cout<<"Degree of damage of the Selected Area : "<<percentageDamage<<endl;

	waitKey(0);
	return 0;

}

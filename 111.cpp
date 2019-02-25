#include<iostream>
#include<unistd.h>
#include<vector>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>


//path of image file change this line for local file usage
#define path "/home/joe/Desktop/111.png"


using namespace std;
using namespace cv;
int x=0;
vector<vector<Point> > contours;
vector<vector<Point> >approximate_polyDP;
vector<Moments> moments_x;
Moments xaa;
Mat image,grey_image,thresh_image,free_image;
string fig;
string& geo_figure(int x){
   if(x==3)
      fig="triangle";
   else if(x==4)
      fig="rectangle";
   else if(x==6)
      fig="hexagon";
   else if(14<=x)
      fig="circle";
       
  return fig;
}


void color_track(int,void*){
    image.copyTo(free_image);
    contours.clear();
    approximate_polyDP.clear();
   threshold(grey_image,thresh_image,x,255,THRESH_BINARY_INV);
   findContours(thresh_image,contours,RETR_LIST,CHAIN_APPROX_SIMPLE);
   approximate_polyDP.resize(contours.size());
   moments_x.resize(contours.size());
   for(int x=0;x<contours.size();x++){
       if(contourArea(contours[x])>500){
           approxPolyDP(contours[x],approximate_polyDP[x],arcLength(contours[x],true)*0.01,true);
           drawContours(free_image,approximate_polyDP,x,Scalar(255,0,0));
           xaa=moments(approximate_polyDP[x]);
           putText(free_image,geo_figure(approximate_polyDP[x].size()),Point(xaa.m10/xaa.m00-10,xaa.m01/xaa.m00),FONT_ITALIC,0.4,Scalar(255,0,0));
       }
   }
   imshow("image",free_image);
   imshow("thresh_image",thresh_image);

}


int main(){
image=imread(path,IMREAD_COLOR);
image.copyTo(free_image);
cvtColor(image,grey_image,COLOR_BGR2GRAY);

namedWindow("image");
namedWindow("thresh_image");
createTrackbar("threshvalue","image",&x,255,color_track);
waitKey(0);

}
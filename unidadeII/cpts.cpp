#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "opencv2/opencv.hpp"

#define STEP 4

using namespace std;
using namespace cv;

int top_slider = 10;
int top_slider_max = 200;

char TrackbarName[50];

Mat image, border;

void on_trackbar_canny(int, void*){
  
}


int main(int argc, char** argv){
  vector<int> yrange;
  vector<int> xrange;
  int width, height;
  int x, y, raio = 4, jitter = 4;
	Mat points, roi;
	float passo;
	Vec3b val;

  image= imread(argv[1],CV_LOAD_IMAGE_COLOR);
  width=image.size().width;
  height=image.size().height;

	xrange.resize(height/STEP);
  yrange.resize(width/STEP);

  iota(xrange.begin(), xrange.end(), 0);
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++)
		xrange[i]= xrange[i]*STEP+STEP/2;

	for(uint i=0; i<yrange.size(); i++)
		yrange[i]= yrange[i]*STEP+STEP/2;

	points = Mat(height, width, CV_8UC3, Scalar(255,255,255));
	random_shuffle(xrange.begin(), xrange.end());
	for(auto i : xrange){
		random_shuffle(yrange.begin(),yrange.end());
		for(auto j : yrange){
		  x = i+rand()%(2*jitter)-jitter+1;
		  y = j+rand()%(2*jitter)-jitter+1;
			passo = (rand()%2)/10.0 +1.0;
		  val[0] = min((int)(image.at<Vec3b>(x,y)[0]*passo),255);
		  val[1] = min((int)(image.at<Vec3b>(x,y)[1]*passo),255);
		  val[2] = min((int)(image.at<Vec3b>(x,y)[2]*passo),255);
		  circle(points,
		         cv::Point(y,x),
		         raio,
		         cv::Scalar(val[0],val[1],val[2]),
		         -1);
		}
	}//*/
	jitter = 3;
	Mat tmp = image.clone();
	Mat out(373, 664, CV_8UC3, Scalar(255,255,255));
	char novo[] = {'0','B','.','p','n','g','\0'};
	for(int i=1; i<160 ;i+=20){
		Canny(image, border, i, 3*i);
		resize(border,out,Size(664,373));
		novo[1] = 'B';
		imwrite(novo,out);

		tmp = Scalar(255,255,255); //limpa tmp para receber a prox iteração

		for(int l=3; l<height-3 ;l++)
			for(int c=3; c<width-3 ;c++){
				if(border.at<uchar>(l,c) == 255){
					raio = 1+rand()%3;
					passo = (rand()%2)/10.0 +1.0;
					x = l+rand()%(2*jitter)-jitter+1;
		 			y = c+rand()%(2*jitter)-jitter+1;
					val[0] = min((int)(image.at<Vec3b>(x,y)[0]*passo),255);
					val[1] = min((int)(image.at<Vec3b>(x,y)[1]*passo),255);
					val[2] = min((int)(image.at<Vec3b>(x,y)[2]*passo),255);
					circle(points,
						     cv::Point(y,x),
						     raio,
						     cv::Scalar(val[0],val[1],val[2]),
						     -1);

					circle(tmp,
						     cv::Point(y,x),
						     raio,
						     cv::Scalar(val[0],val[1],val[2]),
						     -1);
					
				}
			}
		
		resize(tmp,out,Size(664,373));
		novo[1] = 'A';
		imwrite(novo,out);
		novo[0]++;
	}


  imshow("cannyborders.png", points);
  waitKey();
  imwrite("cannyborders.png", points);
  return 0;
}


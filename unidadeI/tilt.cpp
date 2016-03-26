#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;

int jan_slider = 50;
int jan_slider_max = 100;

int dec_slider = 0;
int dec_slider_max = 100;

int pos_slider = 50;
int pos_slider_max = 100;

int l1, l2;
Mat image1, image2, blended;
Mat dst; 

char TrackbarName[50];

void on_trackbar_config(int, void*){
	int tmp1, tmp2;
	dst = image1.clone();
	float alfa;

	tmp1 = pos_slider - jan_slider/2;
	tmp2 = pos_slider + jan_slider/2;
	//printf("t1 %d t2 %d\n", tmp1,tmp2);
	if(tmp1 >= 0 && tmp2 <= 100){
		l2 = tmp2;
		l1 = tmp1;
		l1 = (l1/100.0)*dst.rows;
		l2 = (l2/100.0)*dst.rows;
	}
	/*
	dst = Scalar(0,0,0);
	line(dst,Point(0,l1),Point(dst.cols,l1),Scalar(255,255,255),5);
	line(dst,Point(0,l2),Point(dst.cols,l2),Scalar(255,255,255),5);
	imwrite("linhas.png",dst);//*/

	for(int i=0; i<dst.rows ;i++){
			alfa = 0.5*(tanh((i-l1)/(dec_slider+1))-tanh((i-l2)/(dec_slider+1)));
			addWeighted(image2.row(i), alfa, image1.row(i), 1-alfa,0.0,dst.row(i));
	}
	imshow("Tiltshift",dst);
	imwrite("tiltshift.png",dst);
}

int main(int argc, char** argv){
	Mat mask, mask1, frame32f, frameFiltered;
  image1 = imread("foto.png");
	if(argc == 2)
  	image1 = imread(argv[1]);
  image2 = image1.clone();

  float media[] = {1,1,1,1,1,
									 1,1,1,1,1,
									 1,1,1,1,1,
									 1,1,1,1,1,
									 1,1,1,1,1};
	mask = Mat(5, 5, CV_32F, media); 
  scaleAdd(mask, 1/25.0, Mat::zeros(5,5,CV_32F), mask1);
  swap(mask, mask1);

// -------- criar imagem borrada---------------
  image2.convertTo(frame32f, CV_32F);
	filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);
	frame32f = frameFiltered;
	filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);
	frame32f = frameFiltered;
	filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);
	frameFiltered.convertTo(image1, CV_8U);
//----------------------------------------------


	
  namedWindow("Tiltshift", 1);

	sprintf( TrackbarName, "Centro do Foco x %d", pos_slider_max );
  createTrackbar( TrackbarName, "Tiltshift",
				  &pos_slider,
				  pos_slider_max,
				  on_trackbar_config); //funcao 

  sprintf( TrackbarName, "Largura da Janela x %d", jan_slider_max );
  createTrackbar( TrackbarName, "Tiltshift",
				  &jan_slider,
				  jan_slider_max,
				  on_trackbar_config); //funcao

	sprintf( TrackbarName, "Decaimento x %d", dec_slider_max );
  createTrackbar( TrackbarName, "Tiltshift",
				  &dec_slider,
				  dec_slider_max,
				  on_trackbar_config); //funcao


	on_trackbar_config(jan_slider,0);



  waitKey(0);
  return 0;
}


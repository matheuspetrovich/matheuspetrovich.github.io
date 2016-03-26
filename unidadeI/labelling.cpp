#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int nobjectsSB = 0, nobjectsCB = 0;
  CvPoint p,old;
	uchar oldc;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

	for(int i=0; i<image.rows ;i++){ //insere moldura
		image.at<uchar>(i,0) = 255;
		image.at<uchar>(i,image.cols-1) = 255;
	}
	for(int i=0; i<image.cols ;i++){ //insere moldura
		image.at<uchar>(0,i) = 255;
		image.at<uchar>(image.rows-1,i) = 255;
	}	

  p.x=0;
  p.y=0;
	floodFill(image,p,0); // faz floodfill a partir de (0,0)

	old.x = 0; //inicializa posição do anterior
	old.y = 0;
	oldc = 254; // inicializa cor do anterior
  imwrite("sBordas.png", image);
	floodFill(image,p,100); // eleva fundo para tom 254 para diferenciar o fundo dos buracos
  imwrite("fundo.png", image);

  // busca objetos com buracos presentes

  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255 && oldc == 0){
		// achou um objeto
				p.x=j;
				p.y=i;
				floodFill(image,p,100);
				nobjectsCB++;
	  }
		old.x = i;
		old.y = j;
		oldc = image.at<uchar>(i,j);
	}
  }
	imshow("1",image);
	for(int i=0; i<height; i++)
    for(int j=0; j<width; j++)
      if(image.at<uchar>(i,j) == 255){
		// achou um objeto
				p.x=j;
				p.y=i;
				floodFill(image,p,100);
				nobjectsSB++;
		}
	printf("sem: %d, com: %d\n",nobjectsSB, nobjectsCB);
  waitKey();
  return 0;
}


#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

void usage(char* nome){
    printf("ERRO! - Uso correto eh:\n %s <imagem> <X1> <Y1> <X2> <Y2>\n",nome);
}

int main(int argc, char* argv[]){

  if(argc != 6){
      usage(argv[0]);
      exit(-1);
  }
  Mat image;
  image= imread(argv[1],CV_LOAD_IMAGE_COLOR);

  if(!image.data)
    cout << "nao abriu " << argv[1] << endl;

  namedWindow("janela",WINDOW_AUTOSIZE);
  
  for(int i=atoi(argv[2]);i<atoi(argv[4]);i++){
    for(int j=atoi(argv[3]);j<atoi(argv[5]);j++){
        image.at<Vec3b>(i,j)[0]= 255 - image.at<Vec3b>(i,j)[0];
        image.at<Vec3b>(i,j)[1]= 255 - image.at<Vec3b>(i,j)[1];
        image.at<Vec3b>(i,j)[2]= 255 - image.at<Vec3b>(i,j)[2];
    }
  }

  imshow("janela", image);  
	imwrite("exemplo1.png",image);
  waitKey();
  return 0;
}

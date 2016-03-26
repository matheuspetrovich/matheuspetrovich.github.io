#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

void usage(char* nome){
    printf("ERRO! - Uso correto eh:\n %s <imagem>\n",nome);
}

int main(int argc, char* argv[]){

  if(argc != 2){
      usage(argv[0]);
      exit(-1);
  }

  Mat image;
  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

  if(!image.data)
    cout << "nao abriu " << argv[1] << endl;

  namedWindow("janela",WINDOW_AUTOSIZE);

	int r = image.rows, c = image.cols;
	Mat out = image.clone();
	Mat tmp(image,Rect(0,c/2,r/2,c/2));
	Mat tmp1(image,Rect(r/2,c/2,r/2,c/2));
	Mat tmp2(image,Rect(c/2,0,r/2,c/2));
	Mat tmp3(image,Rect(0,0,r/2,c/2));


//inf esq
	tmp.copyTo(out(Rect(r/2,0,c/2,r/2)));
//sup esq
	tmp1.copyTo(out(Rect(0,0,c/2,r/2)));
//sup dir
	tmp2.copyTo(out(Rect(0,c/2,c/2,r/2)));
//inf dir
	tmp3.copyTo(out(Rect(r/2,c/2,c/2,r/2)));

imwrite("trocado.png",out);
 imshow("janela", out);
  waitKey();
  return 0;
}


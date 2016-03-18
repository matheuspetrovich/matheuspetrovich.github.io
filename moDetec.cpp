#include <iostream>
#include <opencv2/opencv.hpp>
#include  <time.h>  // time()
#include <math.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;
  int width, height;
  VideoCapture cap;
  vector<Mat> planes;
  Mat histR,histV;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

	int intervalo = 500; // intervalo de atualizacao da referencia
	clock_t time_1, time_2;
  int saida = -1;
	float thres = 40, dif = 0; // threshold escolhido com base em calibracao 
  double saida2;


	if(argc == 3){
		intervalo = atoi(argv[1]);
		thres = atoi(argv[2]);
	}

  cap.open(0);
  
  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
  }
  
  width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  int histw = nbins, histh = nbins/2;
  Mat histImgR(histh, histw, CV_8UC3, Scalar(0,0,0));

  time_1 = clock();
  histV.setTo(Scalar(0));

  while(1){
    cap >> image;
    split (image, planes);
    calcHist(&planes[0], 1, 0, Mat(), histR, 1,
             &nbins, &histrange,
             uniform, acummulate);

    normalize(histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
		if(saida == -1){
			histV = histR.clone(); // inicializa a referencia com o primeiro quadro usando saida como flag temporariamente
		}
    histImgR.setTo(Scalar(0));
    
    for(int i=0; i<nbins; i++){

			dif += abs(histV.at<float>(i)-histR.at<float>(i)); //acumula para calcular diferenca media

      line(histImgR, Point(i, histh),
           Point(i, cvRound(histR.at<float>(i))),
           Scalar(0, 0, 255), 1, 8, 0);
  }
		if(dif > thres) //se a diferenca for acima do limite permitido
			circle(image,Point(image.cols/2,image.rows/2),200, Scalar(0,0,255),-200);

		dif = 0; // reseta dif pro proximo frame

    histImgR.copyTo(image(Rect(0,0 ,nbins, histh)));
    imshow("image", image);
    if(waitKey(30) >= 0) break;

    saida = (int) clock() - (time_1);
    saida2 = (double) ((saida) / (double) CLOCKS_PER_SEC);
		saida2 *= 1000.0;
		if((int)saida2%intervalo<100){ //calcula o tempo para resetar a referencia
			histV = histR.clone();
		}
  }
  return 0;
}


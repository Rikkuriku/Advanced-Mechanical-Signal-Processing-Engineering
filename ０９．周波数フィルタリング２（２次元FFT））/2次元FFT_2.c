#include <stdio.h>
#include <math.h>
#include "pgmlib.h"
#include "fft.h" // data[],jdata[],num_of_dataを用います

void make_original_data(int n) //教科書p.73
{
  int i, j;
  
  if (width[n]!=height[n]) {
    printf("縦と横の画素数が異なっています。\n");
    exit(1);
  }
  printf("\n読み込んだ画像を変換元データに直します。");
  
  num_of_data = width[n];
  for (j=0; j<num_of_data; j++) {
    for (i=0; i<num_of_data; i++) {
      data[i][j]=(double)image[n][i][j];
      jdata[i][j]=0.0; // 虚部
    }
  }
}

void make_output_image(int n)
{
  int x, y;
  double val;
  
  printf("\n逆FFT変換後の画像を作成します。\n");
  width[n]=height[n]=num_of_data;
  double max=0;
  for (y=0; y<height[n]; y++) {
    for (x=0; x<width[n]; x++) {
      //val=sqrt(data[x][y]*data[x][y]+jdata[x][y]*jdata[x][y]);
      val=data[x][y];
      if (max<fabs(val)) max=val;
    }
  }
  printf("最大値：%f\n", max);
  for (y=0; y<height[n]; y++) {
    for (x=0; x<width[n]; x++) {
      val=(sqrt(data[x][y]*data[x][y]+jdata[x][y]*jdata[x][y]));
      if (val<0) val=0;
      if (val>MAX_BRIGHTNESS) val=MAX_BRIGHTNESS;
      image[n][x][y]=(unsigned char)val;
    }
  }
}

int main()
{
  //処理する元画像の読込み
  // load_image(0, "sinwave_N_64.pgm");
  load_image(0, "lena.pgm");

  make_original_data(0);
  FFT2(1); // ２次元空間画像を２次元FFT変換し周波数領域へ

  int K = 20;
  int i,j;
  for (j=K; j<num_of_data-K; j++) {
    for (i=0; i<num_of_data; i++) {
      data[i][j]=0.0;
      jdata[i][j]=0.0; // 虚部
    }
  }

  for (j=0; j<num_of_data; j++) {
    for (i=K; i<num_of_data-K; i++) {
      data[i][j]=0.0;
      jdata[i][j]=0.0; // 虚部
    }
  }
  FFT2(-1); 
  make_output_image(1); 

  //結果画像を保存
  // save_image(1, "fft_result.pgm");
  save_image(1, "lena_fft_result_K_20.pgm");
}

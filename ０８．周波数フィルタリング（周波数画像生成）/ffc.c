//fft_sample.c
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
  load_image(0, "lena.pgm");
  //load_image(0, "lena.pgm");

  make_original_data(0); //画像0を元に２次元FFTの前準備（data[],jdata[]に実数値保存、num_of_dataにサイズ指定）
  FFT2(1); // ２次元空間画像を２次元FFT変換し周波数領域へ

  // ☆ここでdata[],jdata[]に対して周波数領域の処理を掛ける☆

  FFT2(-1); //逆FFT変換して空間領域に戻す（ここをコメントアウトすると周波数領域での値（パワースペクトル）が画像保存されます）
  make_output_image(1); //画像1に逆FFTの結果を保存（実数のdata[],jdata[]からimage[n]へ）

  //結果画像を保存
  save_image(1, "lena_fft_result.pgm");
}

#include <stdio.h>
#include "pgmlib.h"

void process_image_and_save_histogram(int num1, int num2, int output_height, int output_width);
// 画像の輝度値をヒストグラムにして保存する。
void copyimage(int num1, int num2);
// 画像No.num1を画像No.num2にコピーする
void tonal_adjustment(int num1, int num2);
// 画像No.num1を画像No.num2に階調補正


int main(void) {
    process_image_and_save_histogram(0, 1, 256, 256);
    copyimage(0,1);
    tonal_adjustment(1,2);
    process_image_and_save_histogram(2, 3, 255, 255);
    return 0;
}

/*****************************************/
/* 　画像の輝度値をヒストグラムにして保存    */
/*****************************************/
void process_image_and_save_histogram(int num1, int num2, int output_height, int output_width) 
{ // 画像の輝度値をヒストグラムにして保存する。パラメータ：元画像番号、ヒストグラム画像番号、ヒストグラム縦幅、ヒストグラム横幅
    // 画像の読み込み
    char input_filename[20];
    sprintf(input_filename, "lena_%d.pgm", num1);
    load_image(num1, input_filename);

    // 全ての要素をゼロで初期化する
    int histogram[256] = {};

    // imageの値をカウント
    int color;
    int x, y;
    for (y = 0; y < height[num1]; y++) {
        for (x = 0; x < width[num1]; x++) {
            color = image[num1][x][y];
            histogram[color] += 1;
        }
    }

    // カウント最大値
    int count_max = 0;
    for (int i = 1; i < 256; i++) {
        // printf("輝度値%d個数: %d\n", i, histogram[i]);
        if (histogram[i] > count_max) {
            count_max = histogram[i];
        }
    }
    // printf("カウント最大値: %d\n", count_max);

    int max;
    height[num2] = output_height;
    width[num2] = output_width;
    init_image(num2, 255);

    // ヒストグラムの正規化
    for (int i = 0; i < height[num2]; i++) {
        int count = histogram[i] * height[num2] / (count_max);
        histogram[i] = count;
    }

    // ヒストグラムを表示
    for (x = 0; x < width[num2]; x++) {
        max = height[num2] - histogram[x];
        for (y = 0; y < height[num2]; y++) {
            if (y < max) {
                image[num2][x][y] = 255;
            } else {
                image[num2][x][y] = 0;
            }
        }
    }

    // 画像の保存
    char output_filename[20];
    sprintf(output_filename, "lena_hist_%d.pgm", num2);
    save_image(num2, output_filename);
}



/***************************/
/* 　　　画像をコピーする    */
/***************************/
void copyimage(int num1, int num2)
{ // 画像No.n1を画像No.n2にコピーする

    char input_filename[20];
    sprintf(input_filename, "lena_%d.pgm", num1);
    load_image(num1, input_filename);

    int x, y; // ループ変数
    // 横幅，縦幅の代入
    width[num2] = width[num1];
    height[num2] = height[num1];
    //階調データのコピー
    for(y=0;y<height[num1];y++)
        for(x=0;x<width[num1];x++)
            image[num2][x][y] = image[num1][x][y];

    // 画像の保存
    char output_filename[20];
    sprintf(output_filename, "lena_%d.pgm", num2);
    save_image(num2, output_filename);
}

/***************************/
/* 　　画像num1をnum2に    */
/* 　　　　階調補正　　　　　 */
/***************************/
void tonal_adjustment(int num1, int num2)
{
    // 画像読み込み
    char input_filename[20];
    sprintf(input_filename, "lena_%d.pgm", num1);
    load_image(num1, input_filename);

    /*最小階調値、最大階調値、ヒストグラム配列を作る*/ 
    // 全ての要素をゼロで初期化する
    int histogram[256] = {};

    // imageの値をカウント
    int color;
    int x, y;
    int fmin = histogram[0]; // 最小階調値
    int fmax = histogram[0]; // 最大階調値
    for (y = 0; y < height[num1]; y++) {
        for (x = 0; x < width[num1]; x++) {
            color = image[num1][x][y];
            histogram[color] += 1;
            if (color > fmax) {
                fmax = color;
            }
            if (color < fmin) {
                fmin = color;
            }
        }
    }
    // // 結果を出力
    // printf("最大値: %d\n", fmax);
    // printf("最小値: %d\n", fmin);

    
    // value_new = value*100/(fmax-fmin)+150
    int i, j; // ループ変数
    // 横幅，縦幅の代入
    width[num2] = width[num1];
    height[num2] = height[num1];
    // 階調補正
    for(j=0;j<height[num1];j++){
        for(i=0;i<width[num1];i++){
            int g = image[num1][i][j] *100 / (fmax - fmin) + 150;
            image[num2][i][j] = g;
        }
    }

    // // value_new = value*100/255+80
    // int i, j; // ループ変数
    // width[num2] = width[num1];
    // height[num2] = height[num1];
    // // 階調補正
    // for(j=0;j<height[num1];j++){
    //     for(i=0;i<width[num1];i++){
    //         int g = image[num1][i][j] *100 / 255 + 80;
    //         image[num2][i][j] = g;
    //     }
    // }

    // 画像保存
    char output_filename[50];
    sprintf(output_filename, "lena_%d.pgm", num2);
    save_image(num2, output_filename);
}

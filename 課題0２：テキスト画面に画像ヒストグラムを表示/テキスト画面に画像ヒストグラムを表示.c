#include <stdio.h>
#include"pgmlib.h" 

int main(void)
{
    load_image(0, "lena.pgm");
    // 二次元配列の定義
    int histogram[256][2];

    // 一列目の値を色の値0~255設定
    for (int i = 0; i < 256; i++) {
        histogram[i][0] = i;
    }

    // 二列目の値をすべて0に設定
    for (int i = 0; i < 256; i++) {
        histogram[i][1] = 0;
    }

    // imageの値をカウント
    int color;
    int x,y;
    for(y = 0; y <= height[0]-1; y++){
        for(x = 0; x <= width[0]-1;x++){
            color = image[0][x][y];
            histogram[color][1] += 1;
        }
    }

    // 度数を＊で表示
    for (int i = 0; i < 256; i++) {
        int star_mark_num =  histogram[i][1] *70/ 2500; // 星マークの個数
        printf("色%d\t",histogram[i][0]);
        for(int i = 0; i < star_mark_num; i++){
            printf("*");            
        }
        printf("\n");
    }
}

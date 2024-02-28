#include <stdio.h>
#include "pgmlib.h"

// 階調値がvalのピクセルの塗り方。
void paint_2_2(int n, int val, int x, int y){
    int dither;
    dither = val / 63;

    if(dither == 0){
        image[n][2*x][2*y] = 0;
        image[n][2*x+1][2*y] = 0;
        image[n][2*x][2*y+1] = 0;
        image[n][2*x+1][2*y+1] = 0;
    }
    else if(dither == 1){
        image[n][2*x][2*y] = 255;
        image[n][2*x+1][2*y] = 0;
        image[n][2*x][2*y+1] = 0;
        image[n][2*x+1][2*y+1] = 0;
    }
    else if(dither == 2){
        image[n][2*x][2*y] = 255;
        image[n][2*x+1][2*y] = 255;
        image[n][2*x][2*y+1] = 0;
        image[n][2*x+1][2*y+1] = 0;
    }
    else if(dither == 3){
        image[n][2*x][2*y] = 255;
        image[n][2*x+1][2*y] = 255;
        image[n][2*x][2*y+1] = 255;
        image[n][2*x+1][2*y+1] = 0;
    }
    else if(dither == 4){
        image[n][2*x][2*y] = 255;
        image[n][2*x+1][2*y] = 255;
        image[n][2*x][2*y+1] = 255;
        image[n][2*x+1][2*y+1] = 255;
    }
}

 
int main(void)
{
    load_image(0,"lena.pgm");

    // 疑似階調での二値化
    int x,y,val;
    width[3] = width[0] *2;
    height[3] = height[0] *2;
    for(y=0;y<height[0];y++){
        for(x=0;x<width[0];x++){
            val = image[0][x][y];
            paint_2_2(3,val,x,y);
        }
    }
    save_image(3,"lena_dither.pgm");
}

// 右側１ピクセルのみに誤差を分散した場合のプログラム
#include <stdio.h>
#include "pgmlib.h"

// 誤差を未処理４近傍側へ拡散
void error_diffusion(int num, int x, int y, int error)
{
    image[num][x+1][y] += error * 0.3;
}

int main(void)
{
    load_image(0, "lena.pgm");
    int x,y,val,error,thr;
    thr = 128;
    for (y = 0; y < height[0]; y++) {
        for (x = 0; x < width[0]; x++) {
            val = image[0][x][y];
            if(val <= thr)
                image[0][x][y] = 0;
            else if(val >thr)
                image[0][x][y] = 255;
            error = val - image[0][x][y];
            error_diffusion(0,x,y,error);
        }
    }
    save_image(0,"lena_error_diffusion_1.pgm");
}

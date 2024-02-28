// ８近傍中の未処理４近傍側（右側１ピクセルと下側３ピクセル）
#include <stdio.h>
#include "pgmlib.h"

// 誤差を未処理４近傍側へ拡散
void error_diffusion(int num, int x, int y, int error)
{
    image[num][x+1][y] += error * 0.3;
    image[num][x-1][y+1] += error * 0.2;
    image[num][x][y+1] += error * 0.3;
    image[num][x+1][y+1] += error * 0.2;}

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
    save_image(0,"lena_error_diffusion_4.pgm");
}

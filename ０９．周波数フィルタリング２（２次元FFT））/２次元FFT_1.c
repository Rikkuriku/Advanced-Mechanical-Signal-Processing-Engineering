//演習問題5-3
#include <stdio.h>
#include "pgmlib.h"
#include <math.h>
#define PI 3.141592657

int w = 255; //画像横幅
int N_x = 128;
int N_y = 256;
int theta_x = 0;
int theta_y = 0;
// int a_0 = 128;
int a_0 = 64;
int a = 127;
int main() {

    load_image(0, "lena.pgm");

    int sinwave;
    int val;					lena_sinwave_Nx_256_Ny_128.pgm
    for(int y=0;y<height[0];y++){
        for(int x=0;x<width[0];x++){
            sinwave = a_0 + a*(sin(20*PI*(x-theta_x)/N_x+20*PI*(y-theta_y)/N_y));
            // N_xとN_yは0になると、valの値は計算できず、nanになってしまう
            val = image[0][x][y] - sinwave;
            if(val>255) val = 255;
            else if(val<0) val = 0;
            image[0][x][y] = val;
        }
    }
    save_image(0,"lena_sinwave_Nx_256_Ny_128.pgm");
    return 0;
}

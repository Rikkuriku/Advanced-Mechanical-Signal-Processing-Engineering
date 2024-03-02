#include <stdio.h>
#include "pgmlib.h"
#include <math.h>
#define PI 3.141592657

int w = 255; //画像横幅
int N = 128;

int main() {
    height[0] = 255;
    width[0] = 255;
    int val;
    for(int y=0;y<256;y++){
        for(int x=0;x<256;x++){
            val = 127*(sin(2*PI*x/N)+1);
            image[0][x][y] = val;
        }
    }
    save_image(0,"sinwave_N_128.pgm");
    return 0;
}

#include <stdio.h>
#include "pgmlib.h"

// 階調削減
void tone_reduction(int index, int bit_depth){
    int x,y,val;
    for (y = 0; y < height[index]; y++) {
        for (x = 0; x < width[index]; x++) {
            val = image[index][x][y];
            int g = 255/bit_depth;
            val /= g;
            val *= g;
            image[index][x][y] = val;
        }
    }
}

int main(void)
{
    load_image(0,"lena.pgm");

    // bit_depth4で階調削減
    copy_image(0,1);
    tone_reduction(1,4);
    save_image(1,"lena_tone_reduced_4.pgm");

    // bit_depth8で階調削減
    copy_image(0,2);
    tone_reduction(2,8);
    save_image(2,"lena_tone_reduced_8.pgm");

    // bit_depth16で階調削減
    copy_image(0,3);
    tone_reduction(3,16);
    save_image(3,"lena_tone_reduced_16.pgm");

    // bit_depth32で階調削減
    copy_image(0,4);
    tone_reduction(4,32);
    save_image(4,"lena_tone_reduced_32.pgm");
}

#include <stdio.h>
#include "pgmlib.h"

// しきい値での二値化
void binarize_image(int index,int threshold) {
    int x, y, val;
    for (y = 0; y < height[index]; y++) {
        for (x = 0; x < width[index]; x++) {
            val = image[index][x][y];

            if (val < threshold) {
                image[index][x][y] = 0;
            } else {
                image[index][x][y] = 255;
            }
        }
    }
}

int main(void)
{
    load_image(0,"lena.pgm");

    // しきい値50での二値化
    copy_image(0,1);
    binarize_image(1, 50);
    save_image(1, "lena_binarization_50.pgm");

    // しきい値100での二値化
    copy_image(0,2);
    binarize_image(2, 100);
    save_image(2, "lena_binarization_100.pgm");

    // しきい値150での二値化
    copy_image(0,3);
    binarize_image(3, 150);
    save_image(3, "lena_binarization_150.pgm");

    // しきい値200での二値化
    copy_image(0,4);
    binarize_image(4, 200);
    save_image(4, "lena_binarization_200.pgm"); 
}

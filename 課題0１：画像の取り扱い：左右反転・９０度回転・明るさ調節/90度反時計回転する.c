#include <stdio.h>
#include"pgmlib.h" 

int main(void)
{
    load_image(0, "lena.pgm");

    /*90度反時計回転する*/
    copy_image(0,3); /*画像No.0からNo.3へコピーする*/
    copy_image(3,4); /*画像No.3からNo.4へコピーする*/
    int x,y;
    for(y=0;y<height[3];y++){
        for(x=0;x<width[3];x++){
            image[4][x][y] = image[3][height[3]-y-1][x];
            //image[4][y][width[4]-x-1] = image[3][x][y];
        }
    }
    copy_image(4,3);
    save_image(3,"3_rotation_lena.pgm");
}

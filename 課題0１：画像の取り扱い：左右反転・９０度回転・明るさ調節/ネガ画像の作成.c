#include <stdio.h>
#include"pgmlib.h" 

int main(void) 
{
    load_image(0, "lena.pgm");

    /*ネガ画像の作成*/
    copy_image(0,4);
    int x,y;
    for(y=0;y<height[4];y++){
        for(x=0;x<width[4];x++){
            image[4][x][y] = 255- image[4][x][y];
        }
    }
    save_image(4,"4_nega_lena.pgm");
}

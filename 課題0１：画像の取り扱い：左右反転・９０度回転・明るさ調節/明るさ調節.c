#include <stdio.h>
#include"pgmlib.h" 

int main(void)
{
    load_image(0, "lena.pgm");

    /*階調値100で明るくする*/
    copy_image(0,1);    /*画像No.0からNo.1へコピーする*/
    int x, y, value, brightness;
    for(int y=0;y<height[1];y++){
        for(int x=0;x<width[1];x++){
            value = image[1][x][y];
            brightness = value + 100;
            if(brightness>255){
                image[1][x][y] = 255;
            }
            else{
                image[1][x][y] = brightness;
            }
        }
    }
    save_image(1, "1_brighten_lena.pgm");
}

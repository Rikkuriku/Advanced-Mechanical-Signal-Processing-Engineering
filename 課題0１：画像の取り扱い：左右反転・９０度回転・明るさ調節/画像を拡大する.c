#include <stdio.h>
#include"pgmlib.h" 

int main(void)
{
    load_image(0, "lena.pgm");

    /*画像を2倍拡大する*/
    copy_image(0,5);
    int x,y;
    width[6] = 2 * width[5];
    height[6] = 2 * height[5];
    for(y=0;y<height[5];y++){	
        for(x=0;x<width[5];x++){
            image[6][2*x][2*y] = image[5][x][y];
            image[6][2*x+1][2*y] = image[5][x][y];
            image[6][2*x][2*y+1] = image[5][x][y];
            image[6][2*x+1][2*y+1] = image[5][x][y];
        }
    }
    copy_image(6,5);
    save_image(5,"5_enlarged_lena.pgm");
}

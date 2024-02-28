#include <stdio.h>
#include"pgmlib.h" 

int main(void)
{
    load_image(0, "lena.pgm");
	
    /*左右反転*/
    copy_image(0,2); /*画像No.0からNo.2へコピーする*/
    int x,y;
    for(y=0;y<height[2];y++){
       for(x=0;x<width[2];x++){	
         image[2][x][y] = image[0][width[2]-1-x][y];　        
        }
    }
    save_image(2,"2_lr_reversed_lena.pgm");
}

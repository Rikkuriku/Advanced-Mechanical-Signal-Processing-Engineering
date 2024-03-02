#include <stdio.h>
#include"pgmlib.h" 

int main(void)
{
    height[0] = 100;
    width[0] = 100;
    int x,y;
    int x1,y1; // remainder
    for(y = 0; y < height[0]; y++){
        y1 = (y/20) % 2;
        for(x = 0; x < width[0]; x++){
            x1 = (x/20) % 2;
            if(x1 == y1){
                image[0][x][y] = 255;
            }
            else{
                image[0][x][y] = 0;
            }
        printf("%d %d %d %d\n", x,y,x1,y1);
        }
    }
    save_image(0,"kuroshiro.pgm");
} 

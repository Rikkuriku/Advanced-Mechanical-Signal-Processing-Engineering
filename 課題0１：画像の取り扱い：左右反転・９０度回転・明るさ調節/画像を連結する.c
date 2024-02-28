#include <stdio.h>
#include"pgmlib.h" 

int main(void)
{
    load_image(0, "lena.pgm");

    /*画像1と画像3を連結する*/
    int x,y;
    width[6] = width[1]+width[3];
    if(width[1]==width[3]){
        height[6] = height[1];
    }
    else{
        printf("画像の高さは違うため、連結できません。");
    }
    // height[6] = max(width[1], width[3]);
    for(y=0;y<height[6];y++){
        for(x=0;x<width[1];x++){
            image[6][x][y]=image[1][x][y];
        }
        for(x=0;x<width[3];x++){
            image[6][x+width[1]][y]=image[3][x][y];
        }
    }
    save_image(6,"6_connect_lena.pgm");
}

//横方向
#include <stdio.h>
#include"pgmlib.h"

int main (void){
    load_image(0,"lena.pgm");//lena画像をロード

    height[1]=height[0];
    width[1]=width[0];
    int x,y,n,m;
    int val=0;

    //横方向
    int f_list[3][3]={{-1, 0, 1},
                      {-1, 0, 1},
                      {-1, 0, 1}};

    for(y=0;y<height[0];y++){
        for(x=0;x<width[0];x++){
            if(y==0||x==0||y==height[0]-1||x==width[0]-1)
            {//画面端を黒にする
                image[1][x][y]=0;
            }
            else{
                val=0;
                for(n=0;n<3;n++){
                    for(m=0;m<3;m++){
                        val+=f_list[n][m]*image[0][x-1+n][y-1+m];
                    }
                }
                if(val>255)
                    image[1][x][y]=255;
                else if(val<0)
                    image[1][x][y]=0;
                else
                    image[1][x][y]=val;
            }
        }
    }
    save_image(1,"lena_filter_yoko.pgm");
    return 0;
}

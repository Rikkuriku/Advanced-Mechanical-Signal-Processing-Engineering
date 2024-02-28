#include <stdio.h>
#include"pgmlib.h" 

int main(void)
{
    load_image(0, "lena.pgm");
    // １次元配列を作成
    int histogram[256];
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    // imageの値をカウント
    int color;
    int x,y;
    for(y = 0; y <= height[0]-1; y++){
        for(x = 0; x <= width[0]-1;x++){
            color = image[0][x][y];
            histogram[color] += 1;
        }
    }  

    // 
    for (int i = 0; i < 256; i++) {
        // histogram[i] =  histogram[i] *70/ 2500; 
        int count =  histogram[i] *255/(2600); 
        histogram[i] = count;
    }
    for(int i=0;i<256;i++){
        printf("%d\n",histogram[i]);
    }

    int max;
    height[1] = 256;
    width[1] = 256;
    init_image(1,255);
    for(x = 0;x <=256;x++){
        max = height[1] - histogram[x];
        for(y=0;y<=height[1]-1;y++){
            if(y<max){
                image[1][x][y] = 255;
            }
            else{
                image[1][x][y] = 0;
            }
            
        }
    }
    save_image(1,"histogram_image.pgm");
}

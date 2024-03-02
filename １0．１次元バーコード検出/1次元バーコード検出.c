#include <stdio.h>
#include "pgmlib.h"
#include <math.h>

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

// バーコード方向への黒（０）と白（２５５）の値の連続個数を数えて順に表示する
void countConsecutiveValues(int *inputArray, int length, int *output, int outputLength) {
    int count = 1;
    int currentValue = inputArray[0];
    int outputIndex = 0;

    for (int i = 1; i < length; i++) {
        if (inputArray[i] == currentValue) {
            count++;
        } else {
            // printf("連続する %d の数: %d\n", currentValue, count);
            int num;
            num = round(count / 8.5); //最初の連続した黒と白のピクセル数で適当に割る
            if (outputIndex < outputLength) {
                output[outputIndex] = num;
                outputIndex++;
            } else {
                printf("出力配列のサイズが足りません\n");
                return;
            }
            
            currentValue = inputArray[i];
            count = 1;
        }
    }
}

int main(void){
    

    // しきい値125での二値化
    load_image(0,"バーコード9784254122060.pgm");
    copy_image(0,1);
    binarize_image(1, 125);
    save_image(1, "バーコード9784254122060_125.pgm");
    
    // バーコードの50行目の階調値を配列Arrayに保存
    load_image(2,"バーコード9784254122060_125.pgm");
    int Array[width[2]];
    int val,x,y=50;
    for(x=0;x<width[2];x++){
        val = image[2][x][y];
        Array[x] = val;
    }

    // Array配列の内容を出力
    printf("\nArray配列の内容\n");
    for (int i = 0; i < sizeof(Array) / sizeof(Array[0]); i++) {
        printf("%d ", Array[i]);
    }
    printf("\n\n");

    // 配列の長さを計算
    int arrayLength = sizeof(Array) / sizeof(Array[0]);
    int output[61];
    countConsecutiveValues(Array, sizeof(Array) / sizeof(Array[0]), output, sizeof(output) / sizeof(output[0]));

    // output配列の内容を出力
    printf("output配列の内容");
    for (int i = 0; i < sizeof(output) / sizeof(output[0]); i++) {
        printf("%d ", output[i]);
    }
    printf("\n\n");

 
    // JANコード→バーコード　配列作る
    int JANcode_Barcode[10][3][4] = {
    {{3,2,1,1},{1,1,2,3},{3,2,1,1}},
    {{2,2,2,1},{1,2,2,2},{2,2,2,1}},
    {{2,1,2,2},{2,2,1,2},{2,1,2,2}},
    {{1,4,1,1},{1,1,4,1},{1,4,1,1}},
    {{1,1,3,2},{2,3,1,1},{1,1,3,2}},
    {{1,2,3,1},{1,3,2,1},{1,2,3,1}},
    {{1,1,1,4},{4,1,1,1},{1,1,1,4}},
    {{1,3,1,2},{2,1,3,1},{1,3,1,2}},
    {{1,2,1,3},{3,1,2,1},{1,2,1,3}},
    {{3,1,1,2},{2,1,1,3},{3,1,1,2}}
    };

    int array_[13]; // 1~12は識別してきたjanコードを保存、0は最後の国番号を保存
    int country[6]; // 識別してきた奇数0・偶数1を保存、奇数偶数の並びで国番号を識別する

    int count_array = 0; // 配列に記入するindex
    for(int n=4; n<27;n+=4){
        int target[4] = {output[n],output[n+1],output[n+2],output[n+3]}; // 識別したい4桁
        int found = 0;

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 3; ++j) {
                int match = 1;
                for (int k = 0; k < 4; ++k) {
                    if (JANcode_Barcode[i][j][k] != target[k]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    printf("[%d,%d,%d,%d]のJANコードは[%d]行[%d]列にあります\n", output[n],output[n+1],output[n+2],output[n+3],i,j);
                    array_[count_array+1] = i;
                    country[count_array] = j;
                    count_array+=1;


                    found = 1;
                    break;
                }
            }
            if (found) break;
        }

        if (!found) {
            printf("%d,%d,%d,%dは見つかりませんでした。\n",output[n],output[n+1],output[n+2],output[n+3]);
        }
    }

    for(int n=33; n<54;n+=4){
        int target[4] = {output[n],output[n+1],output[n+2],output[n+3]};
        int found = 0;

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 3; ++j) {
                int match = 1;
                for (int k = 0; k < 4; ++k) {
                    if (JANcode_Barcode[i][j][k] != target[k]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    printf("[%d,%d,%d,%d]のJANコードは[%d]行にあります\n", output[n],output[n+1],output[n+2],output[n+3],i);
                    array_[count_array+1] = i;
                    count_array+=1;

                    found = 1;
                    break;
                }
            }
            if (found) break;
        }

        if (!found) {
            printf("1,3,1,2は見つかりませんでした。\n");
        }
    }

    // 国番号配列の内容を出力
    printf("国番号配列の内容");
    for (int i = 0; i < 6; i++) {
        printf("%d ", country[i]);
    }
    printf("\n");

    // 国番号　配列作る
    int country_code[10][6] = {
    {0,0,0,0,0,0},
    {0,0,1,0,1,1},
    {0,0,1,1,0,1},
    {0,0,1,1,1,0},
    {0,1,0,0,1,1},
    {0,1,1,0,0,1},
    {0,1,1,1,0,0},
    {0,1,0,1,0,1},
    {0,1,0,1,1,0},
    {0,1,1,0,1,0}
    };

    int found = 0;
    for (int i = 0; i < 10; ++i) {
        int match = 1;
        for (int j = 0; j < 6; ++j) {
            if (country_code[i][j] != country[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            printf("国コードは[%d]番です。\n", i);
            array_[0] = i;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("国コードは見つかりませんでした。\n");
    }

    // print janコード
    printf("janコード");
    for (int i = 0; i < 13; i++) {
        printf("%d", array_[i]);
    }
    printf("\n");
}

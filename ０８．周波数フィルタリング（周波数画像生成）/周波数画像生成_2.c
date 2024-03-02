int N_x = 256;
int N_y = 128;
int theta_x = 0;
int theta_y = 0;
int a_0 = 128;
int a = 127;

int main() {
    height[0] = 256;
    width[0] = 256;
    int val;
    for(int y=0;y<256;y++){
        for(int x=0;x<256;x++){
            val = a_0 + a*(sin(2*PI*(x-theta_x)/N_x+2*PI*(y-theta_y)/N_y));
            // N_xとN_yは0になると、valの値は計算できず、nanになってしまう
            printf("%f",val);
            image[0][x][y] = val;
        }
    }
    save_image(0,"sinwave_Nx_256_Ny_128.pgm");
    return 0;
}

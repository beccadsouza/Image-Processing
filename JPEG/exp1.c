#include <stdio.h>
#include <stdlib.h> //to use system()
#include <string.h>
#include <stdint.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define CHANNEL_NUM 3
int main()
{

int width, height, bpp;

    uint8_t* rgb_image = stbi_load("reb_input_1.jpg", &width, &height, &bpp, 3); // reading  jpeg image
    stbi_image_free(rgb_image);
    printf("Width: %d\nHeight: %d\nBPP: %d\n",width,height,bpp);
    uint8_t* rgb_image1 =(uint8_t*)malloc(width*height*CHANNEL_NUM);
   
printf("Imagemagick  \n");
//sudo apt install imagemagick
printf("--------------------IMAGE METADATA-------------------------------------\n");  // writing image metadata
system("identify -verbose reb_input_1.jpg");
printf("-----------------------------------------------------------------------\n");
printf("Convert rgb to grayscale \n");
system("convert reb_input_1.jpg -set colorspace Gray -separate -average gray.jpeg");     // writing grayscale image
system("ls");
printf("-----------------------------------------------------------------------\n");
printf("Convert rgb to negetive \n");
system("convert  reb_input_1.jpg  -negate  test_negate.jpeg");                           // writing negetive image
system("ls");
printf("-----------------------------------------------------------------------\n");
printf("Convert rgb to black and white with threshold \n");
system("convert reb_input_1.jpg -threshold 50% black_white.jpeg");                      // writing black and white image
system("ls");

printf("-----------------------------------------------------------------------\n");
printf("Convert jpg to png \n");
system("convert reb_input_1.jpg index.png");                           // converting jpeg to  png image
system("ls");




return 0;
}
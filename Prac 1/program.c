#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
     unsigned char red,green,blue;
} PPMPixel;

typedef struct {
     int x, y;
     PPMPixel *data;
} PPMImage;

#define CREATOR "RPFELGUEIRAS"
#define RGB_COMPONENT_COLOR 255

static PPMImage *readPPM(const char *filename, bool display){
         char buff[16];
         PPMImage *img;
         FILE *fp;
         int c, rgb_comp_color;
         //open PPM file for reading
         fp = fopen(filename, "rb");
         if (!fp) {
              fprintf(stderr, "Unable to open file '%s'\n", filename);
              exit(1);
         }

         //read image format
         if (!fgets(buff, sizeof(buff), fp)) {
              perror(filename);
              exit(1);
         }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }
    else{
      if(display){
        fprintf(stderr, "Image format information : %c%c\n", buff[0], buff[1]);
        fprintf(stderr, "Type of Encoding : Binary\nEach pixel is of 3 bytes.\n");
      }
    }

    //alloc memory form image
    img = (PPMImage *)malloc(sizeof(PPMImage));
    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //check for comments
    c = getc(fp);
    while (c == '#') {
    while (getc(fp) != '\n') ;
         c = getc(fp);
    }

    ungetc(c, fp);
    //read image size information
    if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
         exit(1);
    }
    else{
      if(display)
        fprintf(stderr, "Image size information : %dx%d\n", img->x, img->y);
    }

    // calculating the size of image in bytes
    if (buff[0] == 'P' || buff[1] == '6')
    {
        int sizex = img->x;
        int sizey = img->y;
        int total = sizex*sizey;
        if(display)
        fprintf(stderr, "Size of image in Bytes: %d\n", total);
    }

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
         exit(1);
    }
    else{
      if(display)
        fprintf(stderr, "RGB component depth : %d\n", rgb_comp_color);
    }

    //check rgb component depth
    if (rgb_comp_color!= RGB_COMPONENT_COLOR) {
         fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));

    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //read pixel data from file
    if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }

    fclose(fp);
    return img;
}


void writePPM(const char *filename, PPMImage *img){
    FILE *fp;
    //open file for output
    fp = fopen(filename, "wb");
    if (!fp) {
         fprintf(stderr, "Unable to open file '%s'\n", filename);
         exit(1);
    }

    //write the header file
    //image format

    fprintf(fp, "P6\n");

    //comments
    fprintf(fp, "# Created by %s\n",CREATOR);

    //image size
    fprintf(fp, "%d %d\n",img->x,img->y);

    // rgb component depth
    fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);

    // pixel data
    fwrite(img->data, 3 * img->x, img->y, fp);
    fclose(fp);
}

void changeColorPPMBlackAndWhite(PPMImage *img){
    int i;
    if(img){

         for(i=0;i<img->x*img->y;i++){

              PPMPixel pixel = img->data[i];
              long pixel_value = (((int)pixel.red*1000 + (int)pixel.green)*1000 + (int)pixel.blue);

              // Threshold for B&W image set as 150150150
              if(pixel_value > 150150150){
                  img->data[i].red=RGB_COMPONENT_COLOR;
                  img->data[i].green=RGB_COMPONENT_COLOR;
                  img->data[i].blue=RGB_COMPONENT_COLOR;
              }
              else{
                   img->data[i].red=0;
                    img->data[i].green=0;
                    img->data[i].blue=0;
              }
    
         }
    }
}

void changeColorPPMNegative(PPMImage *img){
    int i;
    if(img){

         // Performing 255255255 - RGB color for every pixel
         for(i=0;i<img->x*img->y;i++){
              img->data[i].red=RGB_COMPONENT_COLOR-img->data[i].red;
              img->data[i].green=RGB_COMPONENT_COLOR-img->data[i].green;
              img->data[i].blue=RGB_COMPONENT_COLOR-img->data[i].blue;
         }
    }
}

void changeColorPPMGray(PPMImage *img){
    int i;
    if(img){

          // Taking average of RGB values in each pixel to create Gray color
         for(i=0;i<img->x*img->y;i++){

              PPMPixel pixel = img->data[i];
              long gray_pixel_value = ((double)((int)pixel.red + (int)pixel.green + (int)pixel.blue))/3;
              img->data[i].red=gray_pixel_value;
              img->data[i].green=gray_pixel_value;
              img->data[i].blue=gray_pixel_value;
    
         }
    }
}


int main(){
    PPMImage *image1, *image2, *image3;
    image1 = readPPM("ip_image.ppm", true);
    image2 = readPPM("ip_image.ppm", false);
    image3 = readPPM("ip_image.ppm", false);
    changeColorPPMBlackAndWhite(image1);
    writePPM("bw_op_image.ppm",image1);
    changeColorPPMNegative(image2);
    writePPM("neg_op_image.ppm",image2);
    changeColorPPMGray(image3);
    writePPM("gray_op_image.ppm",image3);
}

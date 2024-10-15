/*
 *      ppmdiff.c
 *      by Angela Huynh, Zach Everett
 *      Date: October 11, 2024
 *      Assignment: arith
 *
 *      Compares two ppm images to determine how similar/different 
 *      they are using the root mean square (RMS) difference.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pnm.h>
#include <uarray2b.h>
#include <uarray2.h>
#include "a2methods.h"
#include "a2blocked.h"
#include "a2plain.h"


int check_dimensions(Pnm_ppm image1, Pnm_ppm image2);
double compute_rms(Pnm_ppm image1, Pnm_ppm image2, int width, int height);
void close_files(FILE *file1, FILE *file2);

int main(int argc, char *argv[])
{
        if (argc != 3) {
                fprintf(stderr, "Usage: %s <image1.ppm> <image2.ppm>\n",
                        argv[0]);
                return 1;
        }

        FILE *file1 = strcmp(argv[1], "-") == 0 ? stdin : fopen(argv[1], "rb");
        FILE *file2 = strcmp(argv[2], "-") == 0 ? stdin : fopen(argv[2], "rb");

        if (!file1 || !file2) {
                fprintf(stderr, "Error: Could not open input files.\n");
                close_files(file1, file2);
                return 1;
        }

        A2Methods_T methods = uarray2_methods_plain; 
        Pnm_ppm image1 = Pnm_ppmread(file1, methods);
        Pnm_ppm image2 = Pnm_ppmread(file2, methods);
        close_files(file1, file2);

        if (!check_dimensions(image1, image2)) {
                Pnm_ppmfree(&image1);
                Pnm_ppmfree(&image2);
                return 1;
        }

        int width = image1->width < image2->width ? image1->width : 
                                                     image2->width;
        int height = image1->height < image2->height ? image1->height : 
                                                       image2->height;
        double rms_error = compute_rms(image1, image2, width, height);

        printf("%.4f\n", rms_error);

        Pnm_ppmfree(&image1);
        Pnm_ppmfree(&image2);
        return 0;
}

/*
 *      close_files
 *      
 */
void close_files(FILE *file1, FILE *file2)
{
        if (file1 && file1 != stdin) {
                fclose(file1);
        }
        if (file2 && file2 != stdin) {
                fclose(file2);
        }
}

/*
 *      check_dimensions
 *      
 */
int check_dimensions(Pnm_ppm image1, Pnm_ppm image2)
{
        int width1 = image1->width, height1 = image1->height;
        int width2 = image2->width, height2 = image2->height;

        if (abs(width1 - width2) > 1 || abs(height1 - height2) > 1) {
                fprintf(stderr, 
                        "Error: Image dimensions differ by more than 1.\n");
                return 0;
        }
        return 1;
}

/*
 *      compute_rms
 *      
 */
double compute_rms(Pnm_ppm image1, Pnm_ppm image2, int width, int height)
{
        double rms_error = 0.0;
        int denominator = image1->denominator;

        for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                        struct Pnm_rgb *pixel1 = UArray2_at(image1->pixels, 
                                                            i, j);
                        struct Pnm_rgb *pixel2 = UArray2_at(image2->pixels, 
                                                            i, j);
                        
                        // Convert RGB values to floating-point values
                        double red_diff = ((double)pixel1->red / denominator) - 
                                          ((double)pixel2->red / denominator);
                        double green_diff = ((double)pixel1->green / denominator) - 
                                            ((double)pixel2->green / denominator);
                        double blue_diff = ((double)pixel1->blue / denominator) - 
                                           ((double)pixel2->blue / denominator);
                        
                        rms_error += red_diff * red_diff + 
                                     green_diff * green_diff + 
                                     blue_diff * blue_diff;
                }
        }

        return sqrt(rms_error / (3 * width * height));
}

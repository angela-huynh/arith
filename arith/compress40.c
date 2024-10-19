/*
 *      compress40.c
 *      by Angela Huynh (ahuynh02), Zach Everett (zevere01)
 *      Date: October 11, 2024
 *      Assignment: arith
 *
 *      Implementation of compress40.h
 *      TO DO: finish writing description of files
 *     
 */
 
#include "pnm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assert.h"
#include <uarray2b.h>
#include <uarray2.h>
#include "a2methods.h"
#include "a2blocked.h"
#include "a2plain.h"

 
Pnm_ppm trim_dimensions(Pnm_pnm image);




extern void compress40  (FILE *input)
{
        assert(input != NULL)
        Pnm_ppm image = Pnm_ppmread(input, uarray2_methods_blocked); 

        trim_dimensions(image);
}


extern void decompress40(FILE *input)
{

}

Pnm_ppm trim_dimensions(Pnm_pnm image)
{
        if((image->height % 2) = 1) {
                Pnm_ppm new_image = malloc(sizeof(*new_image));
                assert(new_image != NULL);
                memset(new_image, 0, sizeof(*new_image));
                new_image->width = image->width;
                new_image->height = image->height - 1;
                new_image->denominator = image->denominator; 
                new_image->methods = image->methods;
                new_image->pixels = methods->new_with_blocksize(image->width, 
                image->height - 1, methods->size(image->pixels), 
                methods->blocksize(image->pixels));


        }
        
        if((image->width % 2) = 1) {
                Pnm_ppm new_image = malloc(sizeof(*new_image));
                assert(new_image != NULL);
                memset(new_image, 0, sizeof(*new_image));
                new_image->width = image->width;
                new_image->height = image->height - 1;
                new_image->denominator = image->denominator; 
                new_image->methods = image->methods;
        }


}







// Pnm_ppm readppm(FILE *input)
// {        
//         assert(input != NULL)
//         //int width, height;
//         Pnm_ppm image = Pnm_ppmread(input, uarray2_methods_blocked);

//         // width = image->height;
//         // height = image->width;

//         // Pnm_ppm new_image = malloc(sizeof(*new_image));
//         // assert(new_image != NULL);
//         // memset(new_image, 0, sizeof(*new_image));
//         // new_image->width = width;
//         // new_image->height = height;
//         // new_image->denominator = image->denominator; 
//         // new_image->methods = image->methods;
//         // new_image->pixels = methods->new_with_blocksize(width, height, 
//         // methods->size(image->pixels), methods->blocksize(image->pixels));

//         return new_image;
// }

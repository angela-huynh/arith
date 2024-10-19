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
#include "compress40.h"

//struct 
 
Pnm_ppm trim_dimensions(Pnm_ppm image);
static void apply_copy(int col, int row, A2Methods_UArray2 array2, void *elem,
void *cl);




extern void compress40  (FILE *input)
{
        assert(input != NULL);
        Pnm_ppm image = Pnm_ppmread(input, uarray2_methods_blocked); 

        image = trim_dimensions(image);
        printf("new width: %d \nnew height: %d \n", image->width, 
        image->height);
}


extern void decompress40(FILE *input)
{
        assert(input != NULL);
}

/*
* trim_dimensions
* Functionality: 
*       Takes user's original image and if width or height is odd,
*       it trims the final column and/or height to return a PPM 
*       with an even column and height
* Input: 
*       Pnm_pnm image: Instance of unmodified instance of image
* Output:
*       Pnm_ppm new_image: Instance of image with even width and height
* Notes:
*       Expect CRE if new image == NULL
*/
Pnm_ppm trim_dimensions(Pnm_ppm image)
{

    if (image->width % 2 == 0 && image->height % 2 == 0) {
        return image;
    }

    Pnm_ppm new_image = malloc(sizeof(*new_image));
    assert(new_image != NULL);
    memset(new_image, 0, sizeof(*new_image));

    new_image->denominator = image->denominator;
    new_image->methods = image->methods;

    new_image->width = image->width % 2 == 1 ? image->width - 1 : image->width;
    new_image->height = image->height % 2 == 1 ? image->height - 1 : image->height;

    new_image->pixels = new_image->methods->new_with_blocksize(
        new_image->width, new_image->height, sizeof(struct Pnm_rgb), 
        image->methods->blocksize(image->pixels));

    new_image->methods->map_block_major(image->pixels, apply_copy, new_image);

    return new_image;

}



/*
* apply_copy
* Functionality:
*       Copies orignal image into a new image 
* Input: 
*       int i: Index of current column 
*       int j: Index of current row
*       A2Methods_Object *pixel: Pointer to current pixel element
*       void *cl: new_image to be coppied to
* Output: 
*       void. But closure is updated via pointers to reflect new image 
* Notes:
*       Applies to a single instance of one pixel. Designed to be called 
*       from an apply function
*
*/
static void apply_copy(int col, int row, A2Methods_UArray2 array2, void *elem,
void *cl)
{
        (void)array2;
        Pnm_ppm new_image = cl;
        assert(new_image->pixels != NULL);
        if (col < (int)new_image->width && row < (int)new_image->height) {
            struct Pnm_rgb *orig_pixel = elem;
            struct Pnm_rgb *new_pixel = new_image->methods->at(
                new_image->pixels, col, row);
            *new_pixel = *orig_pixel;
        }
}

/*
        void apply_float(int i, int j, void *elem, void *cl)
        {
                assert(elem != NULL);
                
                float current = (float)elem->pixels->red;
                elem->pixels->red = new_float;

                current = (float)elem->pixels->green;
                elem->pixels->green = new_float;

                current = (float)elem->pixels->blue
                elem->pixels->blue = new_float;

                
        }
*/
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

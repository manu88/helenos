/*
 * Copyright (c) 2018 Manuel Deneu
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
//
//  AKImage.c
//  
//
//  Created by Manuel Deneu on 04/06/2018.
//
#include <assert.h>
#include <codec/tga.h>
#include <stdio.h>
#include <stdlib.h>
#include <surface.h>
#include <pixconv.h>
#include "AKImage.h"
#include "Utils.h"

#include "upng.h"



static bool AKImageInit( AKImage* image)
{
    image->surface = NULL;
    image->size    = AKSizeNull;
    return true;
}

bool AKImageInitWithTGAData(AKImage* image, void* data, size_t dataSize)
{
    if (AKImageInit(image) == false)
    {
        return false;
    }
    
    assert(image);
    assert(data);
    assert(dataSize > 0);
    
    surface_t *surface = decode_tga((void *) data, dataSize, 0);
    
    if(surface == NULL)
    {
        printf("Unable to decode TGA Data.\n");
        return false;
    }
    
    
    //free(image->data);
    image->surface = surface;
    
    return true;
}

bool AKImageInitWithTGAFile(AKImage* image, const char* tgaFilePath)
{
    assert(image);
    assert(tgaFilePath);
    
    
    size_t dataSize = 0;
    char* buffer =  getFileContent( tgaFilePath , &dataSize);
    
    if (buffer == NULL)
    {
        return false;
    }
    
    assert(dataSize > 0);
    
    const bool ret = AKImageInitWithTGAData( image, buffer, dataSize);
    
    free(buffer);
    
    return ret;
}


bool AKImageInitWithPNGData(AKImage* image, void* data, size_t dataSize)
{
    assert(image);
    assert(data);
    assert(dataSize > 0);
    
    if (AKImageInit(image) == false)
    {
        return false;
    }
    
    upng_t*  png = upng_new_from_bytes((const unsigned char*) data, dataSize);
    
    if( png == NULL )
    {
        printf("Unable to create PNG From Data\n");
        return false;
    }
    
    if (upng_get_error(png) == UPNG_EOK)
    {
        printf("error: %u %u\n", upng_get_error(png), upng_get_error_line(png));
        return false;
    }
    
    image->surface = NULL;
    
    return false;
}



bool AKImageInitWithPNGFile(AKImage* image, const char* pngFilePath)
{
    assert(image);
    assert(pngFilePath);
    
    if (AKImageInit(image) == false)
    {
        return false;
    }
    
    upng_t*  png = upng_new_from_file(pngFilePath);
    
    if( png == NULL )
    {
        printf("Unable to create PNG From File '%s'\n" , pngFilePath);
        return false;
    }
    
    printf("png from '%s' ok\n" , pngFilePath);
    
    unsigned width = upng_get_width(png);
    unsigned height = upng_get_height(png);
    unsigned depth = upng_get_bpp(png) / 8;
    
    printf("size:    %ux%ux%u (%u)\n", width, height, upng_get_bpp(png), upng_get_size(png));
    printf("format:    %u\n", upng_get_format(png));
    printf("depth:    %u\n", depth);
    
    
    //width  = 196;
    //height = 66;
    
    image->surface = surface_create(width, height, NULL, 0);
    
    for (sysarg_t y = 0; y < height; y++)
    {
        for (sysarg_t x = 0; x < width; x++)
        {
            size_t offset = (y * width + x ) * 3;
            
            pixel_t pixel =
            bgr_888_2pixel(((uint8_t *) upng_get_buffer(png) ) + offset);
            
            surface_put_pixel( image->surface, x, height - y - 1, pixel);
        }
    }
    
    return true;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

AKSize AKImageGetSize( const AKImage* image)
{
    assert(image);
    return image->size;
}




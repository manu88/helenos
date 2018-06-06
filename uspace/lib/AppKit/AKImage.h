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
//  AKImage.h
//  
//
//  Created by Manuel Deneu on 04/06/2018.
//

#ifndef AKImage_h
#define AKImage_h


#include <surface.h>
#include <AKGeometry.h>


/*
 A AKImage is a wrapper for image load/save.
 */
typedef struct _AKImage
{
    surface_t *surface;
    
    AKSize size;
    
} AKImage;

// TGA
bool AKImageInitWithTGAData(AKImage* image, void* data, size_t dataSize);
bool AKImageInitWithTGAFile(AKImage* image, const char* tgaFilePath);

// PNG
bool AKImageInitWithPNGData(AKImage* image, void* data, size_t dataSize);
bool AKImageInitWithPNGFile(AKImage* image, const char* pngFilePath);


/* Commons operations */
// returns AKSizeNull on invalid image
AKSize AKImageGetSize( const AKImage* image);

#endif /* AKImage_h */

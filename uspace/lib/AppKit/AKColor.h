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
//  AKColor.h
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#ifndef AKColor_h
#define AKColor_h

#include <io/pixel.h>
#include <stdbool.h>

typedef struct
{
    float r;
    float g;
    float b;
    float a;
    
} AKColor;


typedef pixel_t AKColor8Bit;




static inline AKColor AKColorMake( float r , float g , float b , float a)
{
    return (AKColor){ r ,g , b ,a};
}

static inline AKColor AKColorMakeWithPixel( AKColor8Bit color)
{
    return (AKColor){ RED(color)/255.f ,GREEN(color)/255.f , BLUE(color)/255.f ,ALPHA(color)/255.f};
}

static inline AKColor8Bit AKColorTo8bit( const AKColor* color )
{
    return PIXEL( (int) (color->a*255.f), (int) (color->r*255.f), (int) (color->g*255.f), (int) (color->b*255.f));
}

/*
 For now , it might no fully work with AKColor8Bit converted colors.
 TODO : do comparison with a delta, or get rid of pixel_t.
 */
bool AKColorEquals( const AKColor* color , const AKColor* otherColor );


/* Some color constants */

extern const AKColor AKColorRed;
extern const AKColor AKColorGreen;
extern const AKColor AKColorBlue;
extern const AKColor AKColorWhite;
extern const AKColor AKColorBlack;

extern const AKColor AKColorGray;
extern const AKColor AKColorLightGray;
extern const AKColor AKColorDarkGray;


#endif /* AKColor_h */

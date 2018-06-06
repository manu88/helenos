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
//  AKGeometry.h
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#ifndef AKGeometry_h
#define AKGeometry_h

typedef struct
{
    float x;
    float y;
    
} AKPoint;

typedef struct
{
    float width;
    float height;
    
} AKSize;

typedef struct
{
    AKPoint origin;
    AKSize  size;
    
} AKRect;


extern const AKSize  AKSizeNull;  // a zero width/height size
extern const AKPoint AKPointNull; // a zero x/y point
extern const AKRect  AKRectNull;  // a rect at 0:0 with a null size

static inline AKPoint AKPointMake( float x , float y)
{
    return (AKPoint){ x , y};
}

static inline AKSize AKSizeMake( float width , float height )
{
    return (AKSize){ width , height};
}

static inline AKRect AKRectMake( float x , float y , float width , float height)
{
    return (AKRect){ AKPointMake( x , y) , AKSizeMake(width , height) };
}


#endif /* AKGeometry_h */

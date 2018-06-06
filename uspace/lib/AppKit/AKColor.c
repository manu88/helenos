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
//  AKColor.c
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//
#include <assert.h>
#include "AKColor.h"


const AKColor AKColorRed    = { 1.f , 0.f , 0.f , 1.f};
const AKColor AKColorGreen  = { 0.f , 1.f , 0.f , 1.f};
const AKColor AKColorBlue   = { 0.f , 0.f , 1.f , 1.f};
const AKColor AKColorWhite  = { 1.f , 1.f , 1.f , 1.f};
const AKColor AKColorBlack  = { 0.f , 0.f , 0.f , 1.f};


const AKColor AKColorGray        = { 0.5f , 0.5f , 0.5f , 1.f};
const AKColor AKColorLightGray   = { 0.7f , 0.7f , 0.7f , 1.f};
const AKColor AKColorDarkGray    = { 0.3f , 0.3f , 0.3f , 1.f};


bool AKColorEquals( const AKColor* color , const AKColor* otherColor )
{
    assert(color && otherColor);
    
    return     color->r == otherColor->r
            && color->g == otherColor->g
            && color->b == otherColor->b
            && color->a == otherColor->a;
}

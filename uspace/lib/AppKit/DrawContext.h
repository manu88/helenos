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
//  DrawContext.h
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#ifndef DrawContext_h
#define DrawContext_h

#include <drawctx.h>
#include <surface.h>
#include <io/pixel.h>
#include <AKGeometry.h>
#include <AKFont.h>

typedef struct
{
    drawctx_t* ctx;
} DrawContext;


void DrawContextSetSource( DrawContext* context , source_t* source);
void DrawContextSetFont( DrawContext* context, font_t *font);

// Push and Restore context
void DrawContextSave( DrawContext* context );
void DrawContextRestore( DrawContext* context );

// Text operations
bool DrawContextGetTextSize(DrawContext* context ,font_t *font, const char* text , AKSize *size );


// Draw routines
void lineTo(DrawContext *context ,pixel_t color, int x0, int y0, int x1, int y1);
void lineTo2(DrawContext *context ,pixel_t color, int x0, int y0, int x1, int y1 , float width);
void DrawContextRect( DrawContext *context ,pixel_t color , const AKRect* rect);
void DrawContextAddText( DrawContext* context, const char* text , AKPoint position);


#endif /* DrawContext_h */

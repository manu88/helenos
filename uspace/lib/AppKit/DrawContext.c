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
//  DrawContext.c
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

/*
 Draw routines : Implementation taken from http://members.chello.at/~easyfilter/bresenham.html
 */

#include "DrawContext.h"
#include <sqrt.h>
#include <assert.h>
#include <errno.h>


void DrawContextSave( DrawContext* context )
{
    assert(context && context->ctx);
    drawctx_save(context->ctx);
}
void DrawContextRestore( DrawContext* context )
{
    assert(context && context->ctx);
    drawctx_restore(context->ctx);
}


void DrawContextSetSource( DrawContext* context , source_t* source)
{
    assert(context && source);
    
    drawctx_set_source( context->ctx, source);
}

void DrawContextSetFont( DrawContext* context, font_t *font)
{
    assert(context && font);
    
    drawctx_set_font(context->ctx, font);
}

void DrawContextAddText( DrawContext* context, const char* text , const AKPoint* position)
{
    assert(context && text && position);
    
    drawctx_print(context->ctx, text, (sysarg_t)position->x, (sysarg_t)position->y);
}
bool DrawContextGetTextSize(DrawContext* context ,font_t *font, const char* text , AKSize *size )
{
    assert(context && font && text && size);
    
    sysarg_t textWidth  = 0;
    sysarg_t textHeight = 0;
    errno_t ret =  font_get_box(font ,(char*) text, &textWidth, &textHeight);
    
    size->width  = textWidth;
    size->height = textHeight;
    return ret == EOK;
}
//extern errno_t font_get_box(font_t *, char *, sysarg_t *, sysarg_t *);

static inline int abs( int v)
{
    return v > 0 ? v : -v;
}

void lineTo(DrawContext *context ,pixel_t color, int x0, int y0, int x1, int y1)
{
    surface_t* surface = context->ctx->surface;
    
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;
    
    for(;;)
    {
        surface_put_pixel(surface, x0, y0, color);
        
        if (x0==x1 && y0==y1)
        {
            break;
        }
        e2 = err;
        if (e2 >-dx)
        {
            err -= dy; x0 += sx;
            
        }
        if (e2 < dy)
        {
            err += dx; y0 += sy;
            
        }
    }
}

void lineTo2(DrawContext *context ,pixel_t color, int x0, int y0, int x1, int y1 , float wd)
//void plotLineWidth(int x0, int y0, int x1, int y1, float wd)
{
    
    surface_t* surface = context->ctx->surface;
    
    int dx = abs(x1-x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0 < y1 ? 1 : -1;
    int err = dx-dy, e2, x2, y2;                          /* error value e_xy */
    
    float ed = dx+dy == 0 ? 1 : float32_sqrt((float)dx*dx+(float)dy*dy);
    
    for (wd = (wd+1)/2; ; )
    {
        surface_put_pixel(surface, x0, y0, color);
        //setPixelColor(x0,y0,max(0,255*(abs(err-dx+dy)/ed-wd+1)));
        e2 = err; x2 = x0;
        
        /* x step */
        if (2*e2 >= -dx)
        {
            for (e2 += dy, y2 = y0; e2 < ed*wd && (y1 != y2 || dx > dy); e2 += dx)
            {
                //setPixelColor(x0, y2 += sy, max(0,255*(abs(e2)/ed-wd+1)));
                surface_put_pixel(surface, x0, y0, color);
            }
            if (x0 == x1)
            {
                break;
            }
            
            e2 = err; err -= dy; x0 += sx;
        }
        /* y step */
        if (2*e2 <= dy)
        {
            for (e2 = dx-e2; e2 < ed*wd && (x1 != x2 || dx < dy); e2 += dy)
            {
                //setPixelColor(x2 += sx, y0, max(0,255*(abs(e2)/ed-wd+1)));
                surface_put_pixel(surface, x0, y0, color);
            }
            if (y0 == y1)
            {
                break;
            }
            err += dx; y0 += sy;
        }
    }
}



void DrawContextRect( DrawContext *context ,pixel_t color , const AKRect* rect)
{
    assert(context && rect);
    
    source_t source;
    source_init(&source);
    
    source_set_color(&source, color);
    drawctx_set_source(context->ctx, &source);
    drawctx_transfer(context->ctx, rect->origin.x, rect->origin.y , rect->size.width, rect->size.height);
    //drawctx_transfer(context->ctx, hpos, vpos + 1, 1, height - 2);
}

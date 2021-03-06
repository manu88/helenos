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
//  AKImageView.c
//  
//
//  Created by Manuel Deneu on 04/06/2018.
//

#include "AKCommonsPriv.h"
#include "AKImageView.h"
#include <drawctx.h>

#define LOGO_WIDTH   196
#define LOGO_HEIGHT  66

//static void canvas_destroy(widget_t *widget);

static void AKImageViewDraw(AKView * view , DrawContext* context);

static bool AKImageViewInit( AKImageView* imageView, widget_t * parent)
{
    return AKViewInit( &imageView->view , parent);
}



bool AKImageViewInitWithImage(AKImageView* imageView, widget_t * parent, AKImage* image)
{
    assert(imageView && image);
    
    if (AKImageViewInit(imageView , parent))
    {
        imageView->image = *image;
    }
    
    imageView->view.Draw = AKImageViewDraw;
    
    AKViewSetSize( &imageView->view , AKImageGetSize( image));
    /*
    if( init_canvas(&imageView->canvas,
                    parent,
                    NULL//data,
                     LOGO_WIDTH, LOGO_HEIGHT,
                    image->surface) == false)
    {
        return false;
    }
    
     */
    //imageView->canvas.widget.destroy = canvas_destroy;
    
    return true;
}

/*
static void canvas_destroy(widget_t *widget)
{
    canvas_t *canvas = (canvas_t *) widget;
    
    deinit_canvas(canvas);
//    free(canvas);
}
*/
static void AKImageViewDraw(AKView * view , DrawContext* context)
{
    AKImageView* self = (AKImageView*) view;
    
    
    transform_t transform;
    transform_identity(&transform);
    transform_translate(&transform, view->widget.hpos, view->widget.vpos);
    
    source_t source;
    source_init(&source);
    source_set_transform(&source, transform);
    source_set_texture(&source,
                       self->image.surface,
                       PIXELMAP_EXTEND_TRANSPARENT_BLACK);
    
    DrawContextSetSource(context, &source);
    DrawContexTransfer( context, AKViewGetBounds( view));
    
}




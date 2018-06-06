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
//  AKView.h
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#ifndef AKView_h
#define AKView_h

#include <source.h>
//#include <adt/list.h>

#include <widget.h>
#include <AKColor.h>
#include <DrawContext.h>
#include <AKGeometry.h>
#include <AKEvent.h>

typedef struct _AKView AKView;

typedef struct _AKView
{
    widget_t widget;
    
    // 'private' Properties
    source_t background;

    //bool isOpaque;  default to true
    
    // no default implementation
    void (*GeometryChanged)(AKView * view , int x , int y , int width , int height);
    
    void (*Draw)(AKView * view , DrawContext* context/*, int x , int y , int width , int height*/);
    
    void (*MouseEvent)(AKView* view , const AKMouseEvent* event);
    void (*KeyEvent)(AKView* view , const AKKeyEvent* event);
    
    
    // called when removed from parent
    void (*RemovedFromParentEvent)(AKView* view );
    
} AKView;

// Every callback will be set to NULL. You must set them after init

bool AKViewInit( AKView* view , widget_t* parent /*, AKSize size*/);
void AKViewDeInit( AKView* view);

void AKViewUpdateView( AKView* view);
void AKViewSetBackgroundColor( AKView* view , const AKColor* color);
AKColor AKViewGetBackgroundColor( const AKView* view);

AKRect AKViewGetBounds( const AKView* view);






#endif /* AKView_h */

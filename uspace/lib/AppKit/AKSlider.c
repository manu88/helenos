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
//  AKSlider.c
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#include "AKSlider.h"

static void AKSliderMouseEvent(AKView* view , const AKMouseEvent* event);
static void AKSliderDraw(AKView * view , DrawContext* context);


bool AKSliderInit( AKSlider* slider , widget_t* parent)
{
    
    if (AKControlInit( &slider->base , parent /*, sizeView*/))
    {
        slider->value = 0.5;
        
        slider->base.view.Draw = AKSliderDraw;
        slider->base.view.MouseEvent = AKSliderMouseEvent;
        
        slider->onValueChange = NULL;
        
        slider->value = 0.5;
        slider->handleColor = AKColorBlue;
        
        //slider->userData = NULL;
        return true;
    }
    
    return false;
}


double AKSliderGetValue( const AKSlider* slider )
{
    assert(slider);
    
    return slider->value;
}


void AKSliderSetHandleColor(AKSlider* slider, const AKColor *color)
{
    assert( slider && color);
    
    slider->handleColor = *color;
}


static void AKSliderDraw(AKView * view , DrawContext* context/*, int x , int y , int width , int height*/)
{
    AKSlider* self = (AKSlider*) view;
    
    
    assert(self);
    
    AKRect bounds = AKViewGetBounds(view);
    
    
    //lineTo2(context ,AKColorTo8bit(&AKColorGreen), bounds.origin.x, bounds.origin.y, 100, 50 , 10.);
    lineTo2(context ,AKColorTo8bit( &AKColorLightGray ),
            bounds.origin.x,
            bounds.origin.y+ bounds.size.height/2 ,
            bounds.origin.x+bounds.size.width,
            bounds.origin.y+ bounds.size.height/2 ,
            5.);
    
    
    /*
    AKRect handleRect = bounds;
    handleRect.origin.y += 5;
    handleRect.size.height -= 10;
    handleRect.size.width = 20;
    */
    
    
    
    self->handleRect.size.height = bounds.size.height - 10;
    self->handleRect.size.width  = 20;
    self->handleRect.origin = bounds.origin;
    
    self->handleRect.origin.y += 5;
    self->handleRect.origin.x = self->value* bounds.size.width;
    
    
    DrawContextRect( context ,AKColorTo8bit(&self->handleColor) ,&self->handleRect);
}

static void AKSliderMouseEvent(AKView* view , const AKMouseEvent* event)
{
    AKSlider* self = (AKSlider*) view;
    
    assert(self && event);
    
    if (AKControlIsActive(&self->base) ==false)
    {
        return ;
    }
    
    
    if (event->state == AKMouseState_Press)
    {
        AKRect bounds = AKViewGetBounds(view);
        self->value = event->pos.y/bounds.size.width;
        
        if (self->value > 1.)
        {
            self->value = 1.;
        }
        
        AKViewUpdateView( view);
        
        if (self->onValueChange)
        {
            self->onValueChange(self);
        }
    }
    
}



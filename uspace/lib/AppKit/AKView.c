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
//  AKView.c
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#include <stdio.h>
#include <assert.h>
#include <window.h>
#include <drawctx.h>
#include <path.h>
#include "AKView.h"
#include "AKColor.h"
#include "AKEvent.h"

static void AKView_handle_position_event(widget_t *widget, pos_event_t event);
static void AKView_handle_keyboard_event(widget_t *widget, kbd_event_t event);
static void AKView_repaint(widget_t *widget);
static void AKView_rearrange(widget_t *widget, sysarg_t hpos, sysarg_t vpos, sysarg_t width, sysarg_t height);
static void paint_internal(widget_t *widget);
static void AKView_destroy(widget_t *widget);
static void AKView_reconfigure(widget_t *widget);

bool AKViewInit( AKView* view , widget_t* parent , AKSize size)
{
    assert(view );
    
    widget_init(&view->widget, parent, /*data*/NULL);
    
    view->GeometryChanged = NULL;
    view->Draw = NULL;
    view->MouseEvent = NULL;
    view->KeyEvent = NULL;
    view->RemovedFromParentEvent = NULL;
    
    view->widget.destroy = AKView_destroy;
    view->widget.reconfigure = AKView_reconfigure;
    view->widget.rearrange = AKView_rearrange;
    view->widget.repaint = AKView_repaint;
    view->widget.handle_keyboard_event = AKView_handle_keyboard_event;
    view->widget.handle_position_event = AKView_handle_position_event;
    
    view->widget.width_min = size.width;
    view->widget.height_min = size.height;
    view->widget.width_ideal = view->widget.width_min;
    view->widget.height_ideal = view->widget.height_min;
    
    
    source_init(&view->background);
    source_set_color(&view->background, AKColorTo8bit( &AKColorWhite));
    return true;
}


void AKViewDeInit( AKView* view)
{
    assert(view );
    
    //widget_deinit
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

void AKViewSetBackgroundColor( AKView* view , const AKColor* color)
{
    assert(view && color);
    
    source_set_color(&view->background, AKColorTo8bit( color ));
    
}

AKColor AKViewGetBackgroundColor( const AKView* view)
{
    assert(view);
    return AKColorMakeWithPixel( source_get_color( &view->background ));
}

AKRect AKViewGetBounds( const AKView* view)
{
    assert(view);
    
    return AKRectMake( view->widget.hpos , view->widget.vpos , view->widget.width , view->widget.height );
}

void AKViewUpdateView( AKView* view)
{
    assert(view);
    
    paint_internal(&view->widget);
    window_damage(view->widget.window);
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

static void AKView_destroy(widget_t *widget)
{
    AKView *view = (AKView *) widget;
    assert(view);
    
    if(view->RemovedFromParentEvent)
    {
        view->RemovedFromParentEvent(view);
    }
    //printf("AKView_destroy called\n");
    widget_deinit( widget );
}

static void AKView_reconfigure(widget_t *widget)
{
    //printf("AKView_reconfigure\n");
    /* No-op */
}

static void paint_internal(widget_t *widget)
{
    AKView *view = (AKView *) widget;
    assert(view);
    surface_t *surface = window_claim(widget->window);
    if (!surface)
        window_yield(widget->window);
    
    drawctx_t drawctx;
    drawctx_init(&drawctx, surface);
    
    
    
    
    drawctx_set_source(&drawctx, &view->background);
    
    drawctx_transfer(&drawctx, widget->hpos, widget->vpos, widget->width,
                     widget->height);
    

    /* User defined draw*/
    

    if (view->Draw)
    {
        DrawContext ctx;
        ctx.ctx = &drawctx;
        
        view->Draw(view ,&ctx  );
    }
    
    /* End User defined draw*/
    
    window_yield(widget->window);
}

static void AKView_rearrange(widget_t *widget, sysarg_t hpos, sysarg_t vpos,
                           sysarg_t width, sysarg_t height)
{
    //printf("AKView_rearrange\n");
    
    widget_modify(widget, hpos, vpos, width, height);
    paint_internal(widget);
    
}

static void AKView_repaint(widget_t *widget)
{
    //printf("AKView_repaint\n");
    
   paint_internal(widget); 
   window_damage(widget->window);
}

static void AKView_handle_keyboard_event(widget_t *widget, kbd_event_t event)
{
    AKView *view = (AKView *) widget;
    assert(view);
    
    if (view->KeyEvent)
    {
        AKKeyEvent ev;
        
        if (event.type == KEY_PRESS)
        {
            ev.state =  AKKeyState_Press;
        }
        else if (event.type == KEY_RELEASE)
        {
            ev.state =  AKKeyState_Release;
        }
        else
        {
            assert(false);
        }
        ev.c = event.c;
        ev.key = event.key;
        ev.mods = event.mods;
        
        view->KeyEvent( view  , &ev);
    }
}

static void AKView_handle_position_event(widget_t *widget, pos_event_t event)
{
    
    AKView *view = (AKView *) widget;
    assert(view);
    
    widget->window->focus = widget;
    
    if (view->MouseEvent)
    {
        AKMouseEvent ev;
        ev.pos = AKPointMake( event.vpos , event.hpos);
        
        if(event.btn_num == 1)
        {
            ev.button = AKMouseButton_Left;
        }
        else if(event.btn_num == 2)
        {
            ev.button = AKMouseButton_Right;
        }
        
        
        switch (event.type)
        {
            case POS_RELEASE:
                ev.state = AKMouseState_Release;
                break;
                
            case POS_PRESS:
                ev.state = AKMouseState_Press;
                break;
                
            case POS_UPDATE:
                ev.state = AKMouseState_Move;
                break;
                
            default:
                assert(false);
                break;
        }
        
        view->MouseEvent( view , &ev);
    }
    /*
     event.btn_num = 1 : left, 2 : right
     */
    /*
    printf("AKView_handle_position_event (%li %li)(%li) : " , event.vpos , event.hpos , event.btn_num);
    
    if (event.type == POS_RELEASE)
    {
        printf("Release \n");
    }
    else if (event.type == POS_PRESS)
    {
        printf("Press \n");
    }
    else if (event.type == POS_UPDATE)
    {
        printf("Move \n");
    }
    */
    /*
    if (event.btn_num == 1)
    {
        
    }
     */
}


                

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
//  AKButton.c
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#include <str.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "WidgetImpl.h"
#include <font/embedded.h>
#include "AKButton.h"
#include "AKColor.h"
#include "window.h"
#include "common.h" // draw_bevel

//#include <drawctx.h>

static pixel_t color_highlight = PIXEL(255, 255, 255, 255);
static pixel_t color_shadow = PIXEL(255, 85, 85, 85);


static void button_repaint(widget_t *widget);
static void paint_internal(widget_t *widget);
static void button_handle_position_event(widget_t *widget, pos_event_t event);



static void AKButton_Draw(AKView * view , DrawContext* context);

static void AKButton_destroy(widget_t *widget)
{
    
    printf("AKButton removed\n");
    AKButton *self = (AKButton *) widget;
    assert(self );
    
    WidgetRemoveFromParent( widget);
    //AKGridViewDeInit( self);
    //deinit_button(&self->button);
}

bool AKButtonInit( AKButton * button ,widget_t* parent, const char* text , uint16_t textSize)
{
    assert(button);
    
    
    const AKSize sizeView = AKSizeMake( 200 , 50  );
    
    if (AKViewInit( &button->view , parent , sizeView))
    {
        
        
        source_init(&button->foregroundColor);
        source_set_color(&button->foregroundColor, AKColorTo8bit(&AKColorLightGray));
        
        source_init(&button->textColor);
        source_set_color(&button->textColor, AKColorTo8bit(&AKColorBlack) );
        
        
        if (text == NULL)
            button->text = NULL;
        else
            button->text = str_dup(text);
        
        errno_t rc = embedded_font_create(&button->font, textSize);
        if (rc != EOK)
        {
            free(button->text);
            button->text = NULL;
            return false;
        }
        
        /*
    if( init_button(&button->button, NULL , NULL, text, textSize,
                    AKColorTo8bit( &AKColorWhite) ,
                    AKColorTo8bit( &AKColorLightGray) ,
                    AKColorTo8bit( &AKColorBlack) )
       )
    {
        */
        
        button->view.widget.destroy = AKButton_destroy;
        button->onClick = NULL;
        button->userPtr = NULL;
        
        //button->view.widget.destroy = button_destroy;
        //button->view.widget.reconfigure = button_reconfigure; UNUSED
        //button->view.widget.rearrange = button_rearrange;
        button->view.widget.repaint = button_repaint;
        //button->view.widget.handle_keyboard_event = button_handle_keyboard_event;
        button->view.widget.handle_position_event = button_handle_position_event;
        
        
        button->view.Draw = AKButton_Draw;
        
        return true;
    }
    
    
    return false;
}

void AKButtonDeInit( AKButton* button)
{
    assert(button);
    //deinit_button(&button->button);
}

widget_t* AKButtonGetWidget( AKButton * button)
{
    assert(button);
    
    return &button->view.widget;
}

static void Internal_onClick(widget_t *widget, void *data)
{
    assert(widget);
    
    AKButton* self = (AKButton*) widget;//widget->data;
    assert(self);
    
    if (self->onClick)
    {
        self->onClick( self );
    }
}

void AKButtonSetClickedAction( AKButton* button , AKButtonClicked action)
{
    assert(button);
    
    button->onClick = action;
    sig_connect(
                &button->clicked,
                &button->view.widget,
                Internal_onClick);
}


static void AKButton_Draw(AKView * view , DrawContext* context)
{
    AKButton *btn = (AKButton *) view;
    widget_t *widget = &view->widget;
    
    
    source_t source;
    source_init(&source);
    
    if ((widget->width >= 8) && (widget->height >= 8))
    {
        drawctx_set_source(context->ctx, &source);
        
        draw_bevel(context->ctx, &source, widget->hpos + 3, widget->vpos + 3,
                   widget->width - 6, widget->height - 6, color_highlight,
                   color_shadow);
        
        drawctx_set_source(context->ctx,&btn->foregroundColor );
        
        drawctx_transfer(context->ctx, widget->hpos + 4, widget->vpos + 4,
                         widget->width - 8, widget->height - 8);
    }
    
    sysarg_t cpt_width;
    sysarg_t cpt_height;
    font_get_box(btn->font, btn->text, &cpt_width, &cpt_height);
    
    if ((widget->width >= cpt_width) && (widget->height >= cpt_height)) {
        sysarg_t x = ((widget->width - cpt_width) / 2) + widget->hpos;
        sysarg_t y = ((widget->height - cpt_height) / 2) + widget->vpos;
        
        drawctx_set_source(context->ctx, &btn->textColor);
        drawctx_set_font(context->ctx, btn->font);
        
        if (btn->text)
            drawctx_print(context->ctx, btn->text, x, y);
    }
    
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** */


static void button_handle_position_event(widget_t *widget, pos_event_t event)
{
    AKButton *btn = (AKButton *) widget;
    widget->window->focus = widget;
    
    // TODO make the click logic more robust (mouse grabbing, mouse moves)
    if (event.btn_num == 1)
    {
        if (event.type == POS_RELEASE)
        {
            sig_send(&btn->clicked, NULL);
        }
    }
}

static void button_repaint(widget_t *widget)
{
    paint_internal(widget);
    window_damage(widget->window);
}

static void paint_internal(widget_t *widget)
{
    AKButton *btn = (AKButton *) widget;
    
    surface_t *surface = window_claim(btn->view.widget.window);
    if (!surface)
        window_yield(btn->view.widget.window);
    
    source_t source;
    source_init(&source);
    
    drawctx_t drawctx;
    drawctx_init(&drawctx, surface);
    
    drawctx_set_source(&drawctx, &btn->view.background);
    drawctx_transfer(&drawctx, widget->hpos, widget->vpos,
                     widget->width, widget->height);
    
    if ((widget->width >= 8) && (widget->height >= 8)) {
        drawctx_set_source(&drawctx, &source);
        draw_bevel(&drawctx, &source, widget->hpos + 3, widget->vpos + 3,
                   widget->width - 6, widget->height - 6, color_highlight,
                   color_shadow);
        
        drawctx_set_source(&drawctx,&btn->foregroundColor );
        drawctx_transfer(&drawctx, widget->hpos + 4, widget->vpos + 4,
                         widget->width - 8, widget->height - 8);
    }
    
    sysarg_t cpt_width;
    sysarg_t cpt_height;
    font_get_box(btn->font, btn->text, &cpt_width, &cpt_height);
    
    if ((widget->width >= cpt_width) && (widget->height >= cpt_height)) {
        sysarg_t x = ((widget->width - cpt_width) / 2) + widget->hpos;
        sysarg_t y = ((widget->height - cpt_height) / 2) + widget->vpos;
        
        drawctx_set_source(&drawctx, &btn->textColor);
        drawctx_set_font(&drawctx, btn->font);
        
        if (btn->text)
            drawctx_print(&drawctx, btn->text, x, y);
    }
    
    window_yield(btn->view.widget.window);
}
    


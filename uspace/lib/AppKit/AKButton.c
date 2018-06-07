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
#include <stdlib.h>
#include "AKCommonsPriv.h"
#include "WidgetImpl.h"

#include "AKButton.h"
#include "AKColor.h"
#include "window.h"
#include "common.h" // draw_bevel



static pixel_t color_highlight = PIXEL(255, 255, 255, 255);
static pixel_t color_shadow = PIXEL(255, 85, 85, 85);

//static void button_handle_position_event(widget_t *widget, pos_event_t event);

static void AKButton_MouseEvent(AKView* view , const AKMouseEvent* event);
static void AKButton_Draw(AKView * view , DrawContext* context);

/*
static void AKButton_destroy(widget_t *widget)
{
    
    
    AKButton *self = (AKButton *) widget;
    assert(self );
    
    WidgetRemoveFromParent( widget);

}
 */

bool AKButtonInit( AKButton * button ,widget_t* parent, const char* text , uint16_t textSize)
{
    assert(button);
    
    
    //const AKSize sizeView = AKSizeMake( 200 , 50  );
    
    if (AKControlInit( &button->base , parent /*, sizeView*/))
    {
        
        source_init(&button->foregroundColor);
        source_set_color(&button->foregroundColor, AKColorTo8bit(&AKColorLightGray));
        
        source_init(&button->textColor);
        source_set_color(&button->textColor, AKColorTo8bit(&AKColorBlack) );
        
        source_init(&button->inactiveTextColor);
        source_set_color(&button->inactiveTextColor, AKColorTo8bit(&AKColorGray) );
        
        
        
        
        if (text == NULL)
            button->text = NULL;
        else
            button->text = str_dup(text);
        
        
        button->font = AKFontGet( EmbeddedFontName , textSize );
        
        if ( button->font.handle == NULL)
        {
            free(button->text);
            button->text = NULL;
            return false;
        }
        /*
        errno_t rc = embedded_font_create(&button->font, textSize);
        if (rc != EOK)
        {
            free(button->text);
            button->text = NULL;
            return false;
        }
         */
        
        //button->base.view.widget.destroy = AKButton_destroy;
        
        
        button->onClick = NULL;
        //button->userPtr = NULL;

        button->base.view.Draw = AKButton_Draw;
        button->base.view.MouseEvent = AKButton_MouseEvent;
        return true;
    }
    
    
    return false;
}

void AKButtonDeInit( AKButton* button)
{
    assert(button);
    
    free(button->text);
    
    AKFontRelease( &button->font);
    AKViewDeInit(&button->base.view);
}

void AKButtonSetText( AKButton* button , const char*text)
{
    assert(button);
    assert(text);
    
    if(button->text)
    {
        free(button->text);
    }
    
    button->text = str_dup(text);
    
    AKViewUpdateView( (AKView* ) button);
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
                &button->base.view.widget,
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
    font_get_box(btn->font.handle, btn->text, &cpt_width, &cpt_height);
    
    if ((widget->width >= cpt_width) && (widget->height >= cpt_height)) {
        sysarg_t x = ((widget->width - cpt_width) / 2) + widget->hpos;
        sysarg_t y = ((widget->height - cpt_height) / 2) + widget->vpos;
        
        drawctx_set_source(context->ctx, AKControlIsActive(&btn->base)? &btn->textColor : &btn->inactiveTextColor );
        
        drawctx_set_font(context->ctx, btn->font.handle);
        
        if (btn->text)
        {
            DrawContextAddText(context, btn->text, AKPointMake( x, y) );
            //drawctx_print(context->ctx, btn->text, x, y);
        }
    }
    
}

static void AKButton_MouseEvent(AKView* view , const AKMouseEvent* event)
{
    
    AKButton *btn = (AKButton *) view;
    
    if (AKControlIsActive(&btn->base) ==false)
    {
        return ;
    }
    
    if (event->state == AKMouseState_Release)
    {
        sig_send(&btn->clicked, NULL);
    }

}

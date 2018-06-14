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
//  AKLabel.c
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#include <str.h>
#include <drawctx.h>
#include <stdlib.h>
#include "AKCommonsPriv.h"
#include "AKLabel.h"
#include "WidgetImpl.h"
#include "AKColor.h"
#include <source.h>
#include <window.h>


/*
 static void deinit_my_label(AKLabel *lbl)
 {
     printf("AKLabel removed\n");
     //deinit_label(&lbl->label);
     
     
     
 }
 */

static void AKLabelDraw(AKView * view , DrawContext* context);


/*
static void my_label_destroy(widget_t *widget)
{
 //    AKLabel *lbl = (AKLabel *) widget;
 
     WidgetRemoveFromParent( widget);
 
     //free(lbl);
 }
 */
 

bool AKLabelInit(AKLabel *lbl, widget_t *parent, const char *caption, uint16_t points/*, const AKColor* background, const AKColor* textColor*/ )
{
    assert(lbl );
    
    if (AKViewInit( &lbl->view , parent) )
    {
        
        //lbl->view.widget.destroy = label_destroy;
        //lbl->view.widget.reconfigure = label_reconfigure;
        //lbl->view.widget.rearrange = label_rearrange;
        //lbl->view.widget.repaint = label_repaint;
        //lbl->view.widget.handle_keyboard_event = label_handle_keyboard_event;
        //lbl->view.widget.handle_position_event = label_handle_position_event;
        
        //lbl->view.widget.destroy = my_label_destroy;

        source_init(&lbl->text);
        source_set_color(&lbl->text, AKColorTo8bit( &AKColorBlue));
        
        if (caption == NULL)
            lbl->caption = NULL;
        else
            lbl->caption = str_dup(caption);
        
        
        lbl->font = AKFontGet( EmbeddedFontName , points );
        
        if ( lbl->font.handle == NULL)
        {
            free(lbl->caption);
            lbl->caption = NULL;
            return false;
        }
        
        
        sysarg_t cpt_width;
        sysarg_t cpt_height;
        font_get_box(lbl->font.handle, lbl->caption, &cpt_width, &cpt_height);
        
        lbl->view.widget.width_min = cpt_width + 4;
        lbl->view.widget.height_min = cpt_height + 4;
        lbl->view.widget.width_ideal = lbl->view.widget.width_min;
        lbl->view.widget.height_ideal = lbl->view.widget.height_min;
        
        
        lbl->view.Draw = AKLabelDraw;
        return true;
    }

    return false;
}

void AKLabelDeInit(AKLabel *label)
{
    assert(label );
    
    AKFontRelease(&label->font);
}

void AKLabelSetTextColor( AKLabel* label , const AKColor* color)
{
    assert(label );
    
    source_set_color(&label->text, AKColorTo8bit(color) );
    
    window_refresh(label->view.widget.window);
    
}

void AKLabelSetText( AKLabel* label , const char* text)
{
    assert(label );
    
    if (text)
    {
        free( label->caption);
        label->caption = str_dup(text);
        
        sysarg_t cpt_width;
        sysarg_t cpt_height;
        font_get_box(label->font.handle, label->caption, &cpt_width, &cpt_height);
        
        label->view.widget.width_min = cpt_width + 4;
        label->view.widget.height_min = cpt_height + 4;
        label->view.widget.width_ideal = label->view.widget.width_min;
        label->view.widget.height_ideal = label->view.widget.height_min;
        
        window_refresh(label->view.widget.window);
    }    
}


static void AKLabelDraw(AKView * view , DrawContext* context)
{
    AKLabel* label = (AKLabel*) view;
    
    sysarg_t cpt_width;
    sysarg_t cpt_height;
    font_get_box(label->font.handle, label->caption, &cpt_width, &cpt_height);
    
    if (
        (label->view.widget.width >= cpt_width) &&
        (label->view.widget.height >= cpt_height))
    {
        sysarg_t x = ((label->view.widget.width - cpt_width) / 2)   + label->view.widget.hpos;
        sysarg_t y = ((label->view.widget.height - cpt_height) / 2) + label->view.widget.vpos;
        
        drawctx_set_source(context->ctx, &label->text);
        drawctx_set_font(context->ctx, label->font.handle);
        
        if (label->caption)
        {
            //DrawContextAddText(context, btn->text, AKPointMake( x, y) );
            DrawContextAddText(context , label->caption, AKPointMake( x, y) );
            //drawctx_print( context->ctx, label->caption, x, y);
        }
    }
}

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
//  AKTextView.c
//  
//
//  Created by Manuel Deneu on 07/06/2018.
//

#include <str.h>
#include <stdlib.h>
#include "AKCommonsPriv.h"
#include <AKTextView.h>




static void AKTextView_Draw(AKView * view , DrawContext* context);


 
bool AKTextViewInit( AKTextView* textView, widget_t* parent)
{
    assert(textView);
    
    
    if (AKControlInit( &textView->base , parent ) )
    {
        source_init(&textView->textColor);
        source_set_color(&textView->textColor, AKColorTo8bit( &AKColorBlack));
        
        
        textView->text = str_dup("");
        
        
        textView->font = AKFontGet( EmbeddedFontName , FontDefaultSize );
        
        if ( textView->font.handle == NULL)
        {
            return false;
        }
        
        textView->base.view.Draw = AKTextView_Draw;
        
        return true;
    }
    
    return false;
}

void AKTextViewDeInit( AKTextView* textView)
{
    assert(textView);
}



void AKTextViewSetText( AKTextView* textView, const char* text)
{
    
    assert(textView);
    assert(text);
    
    assert(textView->text);
    
    char* last = textView->text;
    
    textView->text = str_dup(text);
    free(last);
    
    //AKViewUpdateView( (AKView*) textView);
}

void AKTextViewSetTextColor( AKTextView* textView , const AKColor* color)
{
    assert(textView);
    
    source_set_color(&textView->textColor, AKColorTo8bit(color) );
}

static char *substr(char const *input, size_t start, size_t len)
{
    char *ret = malloc(len+1);
    memcpy(ret, input+start, len);
    ret[len]  = '\0';
    return ret;
}

static void AKTextView_Draw(AKView * view , DrawContext* context)
{
    
    AK_DEBUG_LOG("AKTextView_Draw\n");
    AKTextView* self = (AKTextView*) view;
    
    DrawContextSetSource( context , &self->textColor);
    DrawContextSetFont( context, self->font.handle);
    /*
    drawctx_set_source(context->ctx, &self->textColor);
    drawctx_set_font(context->ctx, self->font.handle);
    */
    char* next = NULL;
    char* strLine = NULL;
    
    char* text = str_dup( self->text );
    char* textToFree = text;
    assert(text);
    
    //printf("Original '%s'\n" ,self->text );
    
    AKPoint pos = AKViewGetBounds( (const AKView*) self).origin;// AKPointMake(10 , 50);
    
    pos.x +=10;
    pos.y +=10;
    
    // Why coef 2 ??
    const size_t maxCharPerLine  = 2.f * (AKViewGetBounds( (const AKView*) self).size.width - 20.f) /  AKFontGetSize( &self->font);
    
    //printf(" num chars for size %lu %f\n",maxCharPerLine ,AKViewGetBounds( (const AKView*) self).size.width );
    
    while( (strLine = str_tok( text, "\n", &next)) != NULL)
    {
        
        //printf("Line: '%s' at %f %f \n",  strLine , pos.x , pos.y );
        size_t lineStrLen = str_width(strLine);
        
        size_t textOffset = 0;
        while (lineStrLen)
        {
            
            const size_t size = maxCharPerLine < lineStrLen? maxCharPerLine : lineStrLen ;
            char* l = substr(strLine, textOffset, size);
            //printf("Substr at %lu size %lu \n", textOffset , size);
            
            sysarg_t cpt_width;
            sysarg_t cpt_height;
            font_get_box(self->font.handle, l, &cpt_width, &cpt_height);
            
            DrawContextAddText(context , l, pos );
            
            pos.y += cpt_height;
            
            textOffset+=size;
            lineStrLen -= size;
            
            free(l);
            
            
        }
        // Draw
        
        
        // End Draw
        if (next == NULL)
        {
            break;
        }
        
        text = next;
    }

    free(textToFree);
    
}

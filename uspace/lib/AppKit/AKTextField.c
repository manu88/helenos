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
//  AKTextField.c
//  
//
//  Created by Manuel Deneu on 01/06/2018.
//

#include <str.h>
#include <assert.h>
#include <stdio.h>
#include <window.h>
#include <font/embedded.h>
#include <stdlib.h>
#include "AKTextField.h"
#include "AKColor.h"


static void AKTextFieldDraw(AKView * view , DrawContext* context);
static void AKTextFieldKeyEvent(AKView* view , const AKKeyEvent* event);


bool AKTextFieldInit( AKTextField* textField , widget_t* parent)
{
    assert(textField);
    
    //const AKSize sizeView = AKSizeMake( 200 , 50  );
    
    if (AKViewInit( &textField->view , parent /*, sizeView*/))
    {
        // debug
        AKViewSetBackgroundColor(&textField->view , &AKColorGreen);
        
        textField->text = str_dup("Label");
        textField->view.Draw = AKTextFieldDraw;
        
        textField->view.KeyEvent =AKTextFieldKeyEvent;
        textField->fontSizeInPoints = 16;
        
        
        source_init(&textField->textColor);
        source_set_color(&textField->textColor, AKColorTo8bit( &AKColorRed));
        
        errno_t rc = embedded_font_create(&textField->font, textField->fontSizeInPoints);
        if (rc != EOK)
        {
            printf("AKTextFieldInit : unable to create font\n");
            
            return false;
        }
        
        
        textField->textDidChange = NULL;
        
        return true;
    }
    
    return false;
    
}

static void AKTextFieldKeyEvent(AKView* view , const AKKeyEvent* event)
{
    AKTextField* self = (AKTextField*) view;
    assert(self);
    
    bool textChanged = false;
    
    if (event->state == AKKeyState_Press && event->c)
    {
        if (event->key == KC_BACKSPACE)
        {
            //printf("Got BACKSPACE\n");
            
            size_t len = str_size(self->text);
            
            self->text[len-1] = 0;
            
            AKViewUpdateView( view);
            
            textChanged = true;
            
        }
        else if (event->key == KC_ENTER)
        {
            printf("Got KC_ENTER\n");
        }
        else if (event->c)
        {
            size_t newLen = str_size(self->text) + 1;
            
            char* newStr = realloc(self->text , newLen);// malloc(newLen);
            //char* oldStr = self->text;
            str_cpy(newStr, newLen, self->text);
            newStr[newLen-1] =  event->c;
            
            //free(oldStr);
            self->text = newStr;
            
            //printf("append char : '%c' -> string '%s'\n" , event->c , self->text);
            
            textChanged = true;
            AKViewUpdateView( view);
        }
        
    }
    
    if (textChanged && self->textDidChange)
    {
        self->textDidChange(self);
    }
}

static void AKTextFieldDraw(AKView * view , DrawContext* context)
{

    AKTextField* self = (AKTextField*) view;
    assert(self && self->text);
    
    
    DrawContextSetSource( context , &self->textColor);
    DrawContextSetFont(context , self->font);

    
    AKSize textSize;
    
    if (DrawContextGetTextSize( context , self->font, self->text, &textSize) == false)
    {
        assert(false);
    }
    

    
//    printf("Text size %f %f \n", textSize.width , textSize.height);
    

    AKPoint textPos = AKPointMake( 50 , 50);
    DrawContextAddText(context, self->text, &textPos);
    //drawctx_print( context->ctx, self->text, x, y);

}



void AKTextFieldSetTextColor( AKTextField* textField , const AKColor* color)
{
    assert(textField);
    
    source_set_color(&textField->textColor, AKColorTo8bit(color) );
    
    window_refresh(textField->view.widget.window);
    
}

const char* AKTextFieldGetText( const AKTextField* textField)
{
    assert(textField);
    
    return textField->text;
}
void AKTextFieldSetText(AKTextField* textField, const char* text )
{
    assert(textField);
    assert(text);
    
    free(textField->text);
    textField->text = str_dup(text);
}






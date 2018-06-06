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

#include <stdio.h>
#include <assert.h>
#include "WidgetImpl.h"
#include "AKButton.h"
#include "AKColor.h"

static void AKWidgetInitBase( AKButton * button)
{
    
    widget_t* self = (widget_t*) &button->button;
    assert(self);
    self->data = self;
    
    
}

static void AKButton_destroy(widget_t *widget)
{
    
    printf("AKButton removed\n");
    AKButton *self = (AKButton *) widget;
    assert(self );
    
    WidgetRemoveFromParent( widget);
    //AKGridViewDeInit( self);
    //deinit_button(&self->button);
}

bool AKButtonInit( AKButton * button , const char* text , uint16_t textSize)
{
    assert(button);
    
    if( init_button(&button->button, NULL /*Parent*/, NULL/* data */, text, textSize,
                    AKColorTo8bit( &AKColorWhite) /* backgroundColor*/,
                    AKColorTo8bit( &AKColorLightGray) /*foregroundColor*/,
                    AKColorTo8bit( &AKColorDarkGray) /* textColor*/)
       )
    {
        
        button->button.widget.destroy = AKButton_destroy;
        button->onClick = NULL;
        button->userPtr = NULL;
        
        AKWidgetInitBase(button);
        return true;
    }
    
    
    return false;
}

void AKButtonDeInit( AKButton* button)
{
    assert(button);
    deinit_button(&button->button);
}

widget_t* AKButtonGetWidget( AKButton * button)
{
    assert(button);
    
    return &button->button.widget;
}

static void Internal_onClick(widget_t *widget, void *data)
{
    assert(widget);
    
    AKButton* self = (AKButton*) widget->data;
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
                &button->button.clicked,
                &button->button.widget,
                Internal_onClick);
}



    


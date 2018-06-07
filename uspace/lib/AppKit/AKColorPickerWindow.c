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
//  AKColorPickerWindow.c
//  
//
//  Created by Manuel Deneu on 01/06/2018.
//

#include <stdio.h> // snprintf
#include <stdlib.h> // malloc
#include "AKCommonsPriv.h"
#include "AKColorPickerWindow.h"


static void sliderColorChanged(AKSlider * slider);
static void updateColor( AKColorPickerWindow* colorPicker);


bool AKColorPickerWindowInitWithTitle(AKColorPickerWindow* colorPicker , const char* title)
{
    assert(colorPicker && title);
    
    if (AKWindowInitWithName( &colorPicker->win,   WINDOW_DECORATED , title ) )
    {
        
        
        colorPicker->freeOnClose = false;
        if ( AKGridViewInit(&colorPicker->grid, window_root(AKWindowGetNativeHandle(&colorPicker->win)) , 2/*cols*/, 5/*rows*/ ) == false)
        {
            // TODO: Fix mem leak here
            return false;
        }
        
        if (AKLabelInit(&colorPicker->colorLabel, NULL, "R:0.5 G:0.5 B:0.5", 20  ) == false)
        {
            // TODO: Fix mem leak here
            return false;
        }
        
        AKSliderInit( &colorPicker->sliderR , NULL);
        AKSliderSetHandleColor(&colorPicker->sliderR , &AKColorRed);
        
        colorPicker->sliderR.base.view.userData = colorPicker;
        colorPicker->sliderR.onValueChange = sliderColorChanged;
        
        AKSliderInit( &colorPicker->sliderG , NULL);
        AKSliderSetHandleColor(&colorPicker->sliderG , &AKColorGreen);
        
        colorPicker->sliderG.base.view.userData = colorPicker;
        colorPicker->sliderG.onValueChange = sliderColorChanged;
        
        AKSliderInit( &colorPicker->sliderB , NULL);
        AKSliderSetHandleColor(&colorPicker->sliderB , &AKColorBlue);
        
        colorPicker->sliderB.base.view.userData = colorPicker;
        colorPicker->sliderB.onValueChange = sliderColorChanged;
        
        AKGridViewAdd(&colorPicker->grid , (AKView *)&colorPicker->colorLabel ,0, 0, 2, 1);
        
        if (AKGridViewAdd(&colorPicker->grid , (AKView*) &colorPicker->sliderR ,0, 2, 2, 1) == false)
        {
            assert(false);
        }
        
        if (AKGridViewAdd(&colorPicker->grid , (AKView*) &colorPicker->sliderG ,0, 3, 2, 1) == false)
        {
            assert(false);
        }
        
        if (AKGridViewAdd(&colorPicker->grid , (AKView*) &colorPicker->sliderB ,0, 4, 2, 1) == false)
        {
            assert(false);
        }
        
        AKWindowResize( &colorPicker->win , 0, 0, 430, 240, WINDOW_PLACEMENT_CENTER | WINDOW_PLACEMENT_TOP);
        
        colorPicker->onColorChange = NULL;
        return true;
    }
    
    return false;
}
bool AKColorPickerWindowInit(AKColorPickerWindow* colorPicker)
{
    return AKColorPickerWindowInitWithTitle(colorPicker ,"Color Picker" );
}


AKColorPickerWindow* AKColorPickerWindowCreate(const char* title , const AKColor* color ,AKColorPickerWindowColorChanged onColorChange)
{
    AKColorPickerWindow* colPicker = (AKColorPickerWindow*) malloc(sizeof(AKColorPickerWindow)) ;
    
    if (colPicker && AKColorPickerWindowInitWithTitle( colPicker , title))
    {
        colPicker->freeOnClose = false;
        colPicker->onColorChange = onColorChange;
        return colPicker;
    }
    
    return NULL;
}

void AKColorPickerWindowDeInit(AKColorPickerWindow* colorPicker)
{
    assert(colorPicker);
    
    AKLabelDeInit( &colorPicker->colorLabel);
}

AKColor AKColorPickerWindowGetColor( const AKColorPickerWindow* colorPicker )
{
    assert(colorPicker);
    
    return AKColorMake( AKSliderGetValue(&colorPicker->sliderR),
                        AKSliderGetValue(&colorPicker->sliderG),
                        AKSliderGetValue(&colorPicker->sliderB),
                        1.0
                       );
}

static void updateColor( AKColorPickerWindow* colorPicker)
{
    assert(colorPicker);
    
    const AKColor color = AKColorPickerWindowGetColor( colorPicker);
    
    char b[32];
    snprintf(b , 32 , "R:%0.2f G:%0.2f B:%0.2f" , color.r,color.g , color.b);
    
    AKLabelSetText( &colorPicker->colorLabel , b);
    AKLabelSetTextColor( &colorPicker->colorLabel , &color);
}

static void sliderColorChanged(AKSlider * slider)
{
    AKColorPickerWindow* self = (AKColorPickerWindow*) slider->base.view.userData;
    assert(self);
    
    assert( slider == &self->sliderR || slider == &self->sliderG || slider == &self->sliderB);
    
    
    updateColor( self);
    if (self->onColorChange)
    {
        self->onColorChange(self);
    }
}

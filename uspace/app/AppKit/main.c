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

/*
    AppKit library demo
 */

#include <assert.h>
#include <ApplicationKit.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <task.h>

#include <window.h>

static void colorPickerWindowColorChanged(AKColorPickerWindow * colorPicker);

AKGridView gridView;
AKTextField textField;
AKWindow win;
AKButton btn_confirm;
AKButton btn_cancel;
AKColorPickerWindow* colorPicker = NULL;
AKImageView imageView;

static int loadImage()
{
    AKImage image;
    
    
    const char* fileP = "data/images/helenos.tga";
    //const char* fileP = "data/images/helenos.png";
    
    if ( AKImageInitWithTGAFile(&image ,fileP ) == false)
    //if ( AKImageInitWithPNGFile(&image ,fileP ) == false)
    {
        return 0;
    }
    
    if( AKImageViewInitWithImage(&imageView ,NULL, &image) == false)
    {
        printf("Error : unable to create AKImageView\n" );
        return 0;
    }
    
    
    //free(buffer);
    
    return 1;
}

static void onColorPickerWindowEvent(AKWindow * window, AKWindowEvent event   )
{
    assert( colorPicker != NULL);
    assert( window == (AKWindow *) colorPicker);
    printf("Received ColorPickerWindowEvent :  %i\n" , event);
    
    //AKWindowClose( (AKWindow*) colorPicker);
    
    AKColorPickerWindowDeInit(colorPicker);
    //free(colorPicker);
    colorPicker = NULL;
}

static void on_confirm(AKButton * button)
{
    assert(button == &btn_confirm);
    
    
    if(colorPicker == NULL)
    {
        colorPicker = AKColorPickerWindowCreate("Color picker", NULL ,colorPickerWindowColorChanged);
        
        ((AKWindow*)colorPicker)->OnEvent = onColorPickerWindowEvent;
        AKWindowRun( (AKWindow*) colorPicker);
    }
}

static void on_cancel(AKButton *button)
{
    assert(button == &btn_cancel);
    
    bool state = AKControlIsActive( (AKControl*) &btn_confirm);
    
    AKControlSetActive((AKControl*) &btn_confirm , !state);
    
    AKButtonSetText( &btn_cancel , state? "Enable" : "Disable");
    
/*
    if (colorPicker)
    {
        AKWindowClose( (AKWindow*) colorPicker);

        //free(colorPicker);
        colorPicker = NULL;
    }
 */
}

static void colorPickerWindowColorChanged(AKColorPickerWindow * colorPicker)
{
    const AKColor color = AKColorPickerWindowGetColor(colorPicker);
    AKTextFieldSetTextColor(&textField, &color);
}



int main(int argc, char *argv[])
{
    
    assert(AKApplicationInstance == NULL);
    
    if (AKApplicationInit() == false)
    {
        printf("Unable to create AKApplicationInstance\n");
        return 1;
    }
	
    assert(AKApplicationInstance != NULL);
    
    if (loadImage())
    {
        printf("Init imageView ok \n");
    }
    
    
    if (AKWindowInit( &win,  WINDOW_MAIN | WINDOW_DECORATED | WINDOW_RESIZEABLE) == 0)
    {
        return 2;
    }
    
    if (AKTextFieldInit(&textField , NULL)== false)
    {
        return 5;
    }
    

    if (AKButtonInit( &btn_confirm , NULL/* parent*/ , "Show colors" , 16) == false)
    {
        return 5;
    }

    if (AKButtonInit( &btn_cancel , NULL/* parent*/ ,"Disable" , 16) == false)
    {
        return 6;
    }
    
    AKButtonSetClickedAction( &btn_confirm , on_confirm);
    AKButtonSetClickedAction( &btn_cancel , on_cancel);

    
    if (AKGridViewInit(&gridView ,window_root(AKWindowGetNativeHandle(&win)) ,  2/*cols*/, 3/*rows*/) == false)
    {
        return 7;
    }
    
    AKGridViewAdd(&gridView, (AKView*) &textField , 0, 0, 2, 1);
    AKGridViewAdd(&gridView, (AKView*) &btn_confirm, 0, 1, 1, 1);
    AKGridViewAdd(&gridView, (AKView*) &btn_cancel,  1, 1, 1, 1);
    AKGridViewAdd(&gridView, (AKView*) &imageView,  0, 2, 1, 1);
    
    /* Some tests*/
    widget_t* gridW = (widget_t*) &gridView.grid;
    
    widget_t* b1W = (widget_t*) &btn_confirm;
    widget_t* b2W = (widget_t*) &btn_cancel;
    //assert(gridW == labW->parent);
    assert(gridW == b1W->parent);
    assert(gridW == b2W->parent);
    /* END TESTS */
    
    AKAlertWindow popup;
    
    if ( AKAlertWindowInit(&popup , "Hello" , "This is a text") == false)
    {
        return 8;
    }
    
    AKWindowRun((AKWindow*) &popup);
    
    AKWindowResize( &win , 0, 0, 430, 240, WINDOW_PLACEMENT_CENTER);
    
    
    AKWindowSetFocusedView( &win , (AKView*) &textField);
    AKWindowRun( &win);
    
    
    
    
    
    
    
    
    //task_retval(0);
    async_manager();
    
    
    AKAlertWindowDeInit(&popup);
    
    return 0;
	
}

/** @}
 */

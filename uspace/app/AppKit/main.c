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

#include <Utils.h>
#include <assert.h>
#include <ApplicationKit.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <task.h>

#include <window.h>

//AKWindow win;
AKTextView textView;
AKColorPickerWindow colorPicker;

static void colorPickerWindowColorChanged(AKColorPickerWindow * colorPicker)
{
    const AKColor color = AKColorPickerWindowGetColor(colorPicker);
    
    AKTextViewSetTextColor( &textView , &color);
    
    AKViewUpdateView((AKView*)  &textView);
}


int main(int argc, char *argv[])
{
    
    AKScreenManager man;
    
    if (AKScreenManagerInit(&man , NULL) == false)
    {
        return 1;
    }
    if (argc < 2)
    {
        printf("pass a text file as argument! \n");
        
        return 1;
    }
    
    const char* fileName = argv[1];
    size_t fileDataSize = 0;
    char* fileContent = getFileContentText( fileName , &fileDataSize);
    
    
    if( fileContent == NULL)
    {
        return 4;
    }
    
    
    assert(AKApplicationInstance == NULL);
    
    if (AKApplicationInit() == false)
    {
        printf("Unable to create AKApplicationInstance\n");
        return 1;
    }
	
    assert(AKApplicationInstance != NULL);
    
    if ( AKTextViewInit(&textView , window_root(AKWindowGetNativeHandle(&AKApplicationInstance->rootWindow) )) == false )
    {
        return 3;
    }

    AKWindowResize( &AKApplicationInstance->rootWindow , 0, 0, 200, 100, WINDOW_PLACEMENT_CENTER);
    
    
    
    AKColorPickerWindowInitWithTitle(&colorPicker , "Text Color");
    
    //colorPicker = AKColorPickerWindowCreate("Color picker", NULL ,colorPickerWindowColorChanged);
    
    colorPicker.onColorChange = colorPickerWindowColorChanged;
    AKWindowRun( (AKWindow*) &colorPicker);
    
    
    
    AKWindowSetTitle( &AKApplicationInstance->rootWindow , fileName);
    AKWindowRun( &AKApplicationInstance->rootWindow);
    
    
    
    AKTextViewSetText( &textView, fileContent);
    
    
    AKApplicationMain( argc , argv);
    //task_retval(0);
    
    
    

    free(fileContent);
    return 0;
	
}

/** @}
 */

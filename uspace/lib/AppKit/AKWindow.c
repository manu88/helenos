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
//  AKWindow.c
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#include "AKCommonsPriv.h"
#include "AKWindow.h"
#include "AKView.h"

#define DEFAULT_COMPOSITOR (const char*)"comp:0/winreg"

static void AKWindowRoot_destroy(widget_t *widget);




bool AKWindowInitWithName( AKWindow *win , window_flags_t flags , const char* name)
{
    assert(win && name);
    
    
    win->win = window_open(DEFAULT_COMPOSITOR, NULL, flags, name);
    
    win->win->root.destroy = AKWindowRoot_destroy;
    
    win->win->root.data = win;
    
    win->OnEvent = NULL;
    //win->isOpen = false;
    return win->win != NULL;
}

bool AKWindowInit( AKWindow *win , window_flags_t flags)
{
    /*
    assert(win);
    win->win = window_open(DEFAULT_COMPOSITOR, NULL, flags, "");

    return win->win != NULL;
     */
    
    return AKWindowInitWithName(win , flags , "");
    
}
void AKWindowDeInit( AKWindow *win)
{
    assert(win);
    
}

bool AKWindowSetTitle(  AKWindow *win , const char* title)
{
    assert(win && title);
    
    return window_set_caption(win->win , title) == EOK;
}
const char* AKWindowGetTitle( const AKWindow *win)
{
    assert(win);
    
    return win->win->caption;
}

void AKWindowResize( AKWindow* win , int x , int y , int width , int height, window_placement_flags_t placement_flags)
{
    assert(win);
    
    window_resize(win->win, x, y, width, height, placement_flags);
}

window_t * AKWindowGetNativeHandle( const AKWindow* win)
{
    assert(win);
    return win->win;
}

bool AKWindowIsMain( const AKWindow* win )
{
    assert(win && win->win);
    
    return win->win->is_main;
}

void AKWindowRun( AKWindow* win)
{
    assert(win && win->win);
    
    /*
    if (win->win->surface == NULL)
    {
        
        sysarg_t w = win->win->root.width == 0? 300 : win->win->root.width;
        sysarg_t h = win->win->root.height == 0? 200 : win->win->root.height;
        AK_DEBUG_LOG("Root size %lu %lu\n",w , h);
        
        
        AKWindowResize( win , 0, 0, w,h, WINDOW_PLACEMENT_CENTER);
        
    }
     */
    
    window_exec(win->win);

}

void AKWindowClose( AKWindow* win)
{
    assert(win && win->win);
    
    /*
    if (win->isOpen == true)
    {
        win->isOpen = false;
     */
        window_close(win->win);
    //}
}

void AKWindowSetFocusedView( AKWindow* win, AKView* view)
{
    assert(win && win->win);
 
    
    win->win->focus = &view->widget;
}

bool AKWindowHasFocus( const AKWindow* win)
{
    assert(win && win->win);
    
    return win->win->is_focused;
}

static void AKWindowRoot_destroy(widget_t *widget)
{
    AKWindow* win = (AKWindow*) widget->data;
    
    assert(win);
    
    if(win->OnEvent)
    {
        win->OnEvent(win , AKWindowEvent_Closed);
    }
    widget_deinit(widget);
}



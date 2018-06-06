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
//  AKWindow.h
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#ifndef AKWindow_h
#define AKWindow_h


#include <window.h>

typedef enum
{
  AKWindowEvent_Closed
} AKWindowEvent;

typedef struct _AKView AKView;

typedef struct _AKWindow AKWindow;
typedef struct _AKWindow
{
    window_t *win;
    
    bool isOpen; // Temp hack TODO: find a better system
    
    
    void (*OnEvent)(AKWindow * window, AKWindowEvent event   );
} AKWindow;

/*
 window_flags_t defined in io/window.h
 */
bool AKWindowInit( AKWindow *win , window_flags_t flags);
bool AKWindowInitWithName( AKWindow *win , window_flags_t flags , const char* name);
void AKWindowDeInit( AKWindow *win);

bool AKWindowSetTitle(  AKWindow *win , const char* title);
const char* AKWindowGetTitle( const AKWindow *win);

/*
 window_placement_flags_t defined in io/window.h
 */
void AKWindowResize( AKWindow* win , int x , int y , int width , int height , window_placement_flags_t placement_flags);



window_t * AKWindowGetNativeHandle( const AKWindow* win);

void AKWindowRun( AKWindow* win);
void AKWindowClose( AKWindow* win);

bool AKWindowIsMain( const AKWindow* win );

// safe to pass NULL (?)
void AKWindowSetFocusedView(AKWindow* win, AKView* view);

bool AKWindowHasFocus( const AKWindow* win);

#endif /* AKWindow_h */

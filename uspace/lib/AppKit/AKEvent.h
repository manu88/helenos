//
//  AKEvent.h
//  
//
//  Created by Manuel Deneu on 01/06/2018.
//
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

#ifndef AKEvent_h
#define AKEvent_h

#include <io/keycode.h>
#include "AKGeometry.h"
#include <wchar.h>

typedef enum
{
    AKMouseButton_Left  = 1,
    AKMouseButton_Right = 2
    
} AKMouseButton;

typedef enum
{
    AKMouseState_Move,
    AKMouseState_Press,
    AKMouseState_Release
    
} AKMouseState;

typedef struct
{
    AKMouseButton button;
    AKMouseState  state;
    AKPoint       pos;
    
} AKMouseEvent;

/* **** **** **** **** **** **** **** **** **** */

typedef enum
{
    AKKeyState_Press,
    AKKeyState_Release
    
} AKKeyState;

typedef struct
{
    AKKeyState state;
    keycode_t key;
    keymod_t mods;
    wchar_t c; // The character that was generated or '\0' for none.
    
} AKKeyEvent;

#endif /* AKEvent_h */

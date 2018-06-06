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
//  AKButton.h
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#ifndef AKButton_h
#define AKButton_h

#include <AKControl.h>
#include <connection.h> // signal_t

typedef struct _AKButton AKButton;

typedef void (*AKButtonClicked)(AKButton * button);


typedef struct _AKButton
{
    AKControl base; // needs to stay first!
    
    source_t foregroundColor;
    source_t textColor;
    source_t inactiveTextColor;
    
    font_t *font;
    
    char *text;
    signal_t clicked;
    
    void* userPtr;
    
    AKButtonClicked onClick;
    
} AKButton;




/*
 Will reset fields like userPtr, onClick, etc !
 */
bool AKButtonInit( AKButton * button ,widget_t* parent, const char* text , uint16_t textSize);

void AKButtonDeInit( AKButton* button);

widget_t* AKButtonGetWidget( AKButton * button);

void AKButtonSetClickedAction( AKButton* button , AKButtonClicked action);

void AKButtonSetText( AKButton* button , const char*text);

#endif /* AKButton_h */

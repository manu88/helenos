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
//  AKTextField.h
//  
//
//  Created by Manuel Deneu on 01/06/2018.
//

#ifndef AKTextField_h
#define AKTextField_h


#include <AKControl.h>
#include <AKFont.h>

typedef struct _AKTextField AKTextField;


typedef void (*AKTextFieldTextChanged)(AKTextField * button);

typedef struct _AKTextField
{
    AKControl base;
    void* userData;
    
    AKFont font;
    source_t textColor;
    uint16_t fontSizeInPoints; // default to 16
    
    char* text;
    
    
    
    AKTextFieldTextChanged textDidChange;
} AKTextField;

bool AKTextFieldInit( AKTextField* textField , widget_t* parent);

void AKTextFieldSetTextColor( AKTextField* textField , const AKColor* color);


const char* AKTextFieldGetText( const AKTextField* textField);
void AKTextFieldSetText(AKTextField* textField, const char* text );

#endif /* AKTextField_h */

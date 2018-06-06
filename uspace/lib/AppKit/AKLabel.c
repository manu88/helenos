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
//  AKLabel.c
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#include <assert.h>
#include <stdio.h>
#include "AKLabel.h"
#include "WidgetImpl.h"
#include "AKColor.h"
#include <source.h>
#include <window.h>


/*
 static void deinit_my_label(AKLabel *lbl)
 {
     printf("AKLabel removed\n");
     //deinit_label(&lbl->label);
     
     
     
 }
 */
 
 static void my_label_destroy(widget_t *widget)
 {
 //    AKLabel *lbl = (AKLabel *) widget;
 
     WidgetRemoveFromParent( widget);
 
     //free(lbl);
 }
 

bool AKLabelInit(AKLabel *lbl, widget_t *parent, const char *caption, uint16_t points/*, const AKColor* background, const AKColor* textColor*/ )
{
    assert(lbl );
    
    bool initialized = init_label(&lbl->label,
                                  parent,
                                  NULL,
                                  caption,
                                  points,
                                  AKColorTo8bit( &AKColorWhite),
                                  AKColorTo8bit( &AKColorBlue)
                                  );
    
    lbl->label.widget.destroy = my_label_destroy;
    return initialized;
}

void AKLabelSetTextColor( AKLabel* label , const AKColor* color)
{
    assert(label );
    
    source_set_color(&label->label.text, AKColorTo8bit(color) );
    
    window_refresh(label->label.widget.window);
    
}
void AKLabelSetText( AKLabel* label , const char* text)
{
    assert(label );
    
    label->label.rewrite(&label->label.widget, (void *) text);
}

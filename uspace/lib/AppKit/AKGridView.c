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
//  AKGridView.c
//  
//
//  Created by Manuel Deneu on 04/06/2018.
//


#include "AKCommonsPriv.h"
#include "AKGridView.h"
#include "WidgetImpl.h"
#include "AKColor.h"





static void AKGridView_destroy(widget_t *widget)
{
    AKGridView *self = (AKGridView *) widget;
    assert(self );
    
    WidgetRemoveFromParent(widget);
    //AKGridViewDeInit( self);
}


bool AKGridViewInit(AKGridView *gridView, widget_t * parent, size_t cols , size_t rows)
{
    assert(gridView );
    
    
    if (init_grid( &gridView->grid, parent , NULL/*Data*/ , cols , rows ,AKColorTo8bit( &AKColorWhite) /* backgroundColor*/))
    {
        
        gridView->grid.widget.destroy = AKGridView_destroy;
        return true;
    }
    return false;
}

void AKGridViewDeInit( AKGridView *gridView)
{
    assert(gridView );
    
    widget_deinit(&gridView->grid.widget);
    //deinit_grid(&gridView->grid);
}


bool AKGridViewAdd(AKGridView *gridView ,AKView* view ,size_t col , size_t row , size_t sizeCols , size_t sizeRows   )
{
    assert(gridView && view);
    
    return gridView->grid.add(&gridView->grid ,(widget_t*) view , col , row , sizeCols , sizeRows);
}

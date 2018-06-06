//
//  WidgetImpl.c
//  
//
//  Created by Manuel Deneu on 04/06/2018.
//

#include <assert.h>
#include <adt/list.h>
#include "WidgetImpl.h"


void WidgetRemoveFromParent( widget_t* widget)
{
    assert(widget);
    
    if (widget->parent)
    {
        list_remove(&widget->link);
        
        widget->parent = NULL;
    }
}

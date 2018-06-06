//
//  AKControl.c
//  
//
//  Created by Manuel Deneu on 06/06/2018.
//

#include <assert.h>
#include "AKControl.h"


bool AKControlInit( AKControl* control , widget_t* parent)
{
    assert(control);
    
    if ( AKViewInit( &control->view , parent))
    {
        control->isActive = true;
        return true;
    }
    
    return false;
}

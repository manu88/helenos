//
//  AKControl.c
//  
//
//  Created by Manuel Deneu on 06/06/2018.
//

#include "AKCommonsPriv.h"
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


void AKControlSetActive( AKControl* control , bool active)
{
    assert(control);
    
    
    const bool changed = control->isActive != active;
    control->isActive = active;
    
    if (changed)
    {
        AKViewUpdateView(&control->view);
    }
}

bool AKControlIsActive( const AKControl* control)
{
    assert(control);
    
    return control->isActive;
}

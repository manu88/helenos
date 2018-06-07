//
//  AKAlertWindow.c
//  
//
//  Created by Manuel Deneu on 06/06/2018.
//
#include <assert.h>
#include "AKAlertWindow.h"


bool AKAlertWindowInit(AKAlertWindow* alert , const char* title)
{
    assert(alert);
    assert(title);
    
    if (AKWindowInitWithName( &alert->win,   WINDOW_DECORATED , title ) )
    {
        
        if ( AKGridViewInit(&alert->grid, window_root(AKWindowGetNativeHandle(&alert->win)) , 2/*cols*/, 2/*rows*/ ) == false)
        {
            // TODO: Fix mem leak here
            return false;
        }
        
        AKLabelInit( &alert->text , NULL, "Some text here" , 16);
        
        AKButtonInit( &alert->okButton ,NULL, "Ok" , 16);
        AKButtonInit( &alert->cancelButton ,NULL, "Cancel" , 16);
        
        
        if (AKGridViewAdd(&alert->grid , (AKView*) &alert->text ,0, 0, 2, 1) == false)
        {
            return false;
        }
        
        if (AKGridViewAdd(&alert->grid , (AKView*) &alert->okButton ,0, 1, 1, 1) == false)
        {
            return false;
        }
        if (AKGridViewAdd(&alert->grid , (AKView*) &alert->cancelButton ,1, 1, 1, 1) == false)
        {
            return false;
        }
        
        AKWindowResize( &alert->win , 0, 0, 220, 90, WINDOW_PLACEMENT_CENTER | WINDOW_PLACEMENT_TOP);
        
        return true;
    }
    
    return false;
}

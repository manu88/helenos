//
//  AKAlertWindow.c
//  
//
//  Created by Manuel Deneu on 06/06/2018.
//
#include "AKCommonsPriv.h"
#include "AKAlertWindow.h"

static void onButton(AKButton * button);


bool AKAlertWindowInit(AKAlertWindow* alert , const char* title , const char* text )
{
    assert(alert);
    assert(title);
    
    if (AKWindowInitWithName( &alert->win,  0/* WINDOW_DECORATED*/ , title ) )
    {
        
        if ( AKGridViewInit(&alert->grid, window_root(AKWindowGetNativeHandle(&alert->win)) , 2/*cols*/, 2/*rows*/ ) == false)
        {
            // TODO: Fix mem leak here
            return false;
        }
        
        AKLabelInit( &alert->text , NULL, text , FontDefaultSize);
        
        AKButtonInit( &alert->okButton ,NULL, "Ok" , FontDefaultSize);
        AKButtonSetClickedAction(&alert->okButton , onButton);
        alert->okButton.base.view.userData = alert;
        
        AKButtonInit( &alert->cancelButton ,NULL, "Cancel" , FontDefaultSize);
        AKButtonSetClickedAction(&alert->cancelButton , onButton);
        alert->cancelButton.base.view.userData = alert;
        
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

void AKAlertWindowDeInit(AKAlertWindow* alert)
{
    assert(alert);
    
    AKLabelDeInit( &alert->text);
}

static void onButton(AKButton * button)
{
    AKAlertWindow* alert = (AKAlertWindow*) button->base.view.userData;
    
    assert(alert);
    
    AKWindowClose( (AKWindow*) alert  );
}



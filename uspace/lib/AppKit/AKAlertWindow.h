//
//  AKAlertWindow.h
//  
//
//  Created by Manuel Deneu on 06/06/2018.
//

#ifndef AKAlertWindow_h
#define AKAlertWindow_h

#include <AKWindow.h>
#include <AKGridView.h>
#include <AKButton.h>
#include <AKLabel.h>

typedef struct _AKAlertWindow
{
    AKWindow win;
    AKGridView grid;
    
    AKLabel text;
    AKButton okButton;
    AKButton cancelButton;
    
} AKAlertWindow ;

bool AKAlertWindowInit(AKAlertWindow* alert , const char* title , const char* text );

#endif /* AKAlertWindow_h */

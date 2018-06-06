//
//  AKControl.h
//  
//
//  Created by Manuel Deneu on 06/06/2018.
//

#ifndef AKControl_h
#define AKControl_h

#include <AKView.h>


typedef struct _AKControl
{
    AKView view;
    
    bool isActive; // defaut : true
    
} AKControl;


bool AKControlInit( AKControl* control , widget_t* parent);



#endif /* AKControl_h */

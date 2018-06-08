//
//  AKTextView.h
//  
//
//  Created by Manuel Deneu on 07/06/2018.
//

#ifndef AKTextView_h
#define AKTextView_h

#include <AKControl.h>


typedef struct _AKTextView
{
    AKControl base;
    
    AKFont font;
    source_t textColor;
    
    char* text;
    
} AKTextView;

bool AKTextViewInit( AKTextView* textView, widget_t* parent);
void AKTextViewDeInit( AKTextView* textView);

void AKTextViewSetText( AKTextView* textView, const char* text);
void AKTextViewSetTextColor( AKTextView* textView , const AKColor* color);
#endif /* AKTextView_h */

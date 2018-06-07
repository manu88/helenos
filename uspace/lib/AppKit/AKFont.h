//
//  AKFont.h
//  
//
//  Created by Manuel Deneu on 07/06/2018.
//

#ifndef AKFont_h
#define AKFont_h

#include <font.h>


extern const char EmbeddedFontName[];

extern const uint16_t FontDefaultSize;

typedef struct
{
    font_t *handle;
    
} AKFont;


AKFont AKFontGet( const char* name , uint16_t points );


void AKFontRelease( AKFont* font);


#endif /* AKFont_h */

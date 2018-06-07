//
//  AKTextView.c
//  
//
//  Created by Manuel Deneu on 07/06/2018.
//

#include <str.h>
#include <stdlib.h>
#include "AKCommonsPriv.h"
#include <AKTextView.h>




static void AKTextView_Draw(AKView * view , DrawContext* context);

bool AKTextViewInit( AKTextView* textView, widget_t* parent)
{
    assert(textView);
    
    
    if (AKControlInit( &textView->base , parent ) )
    {
        source_init(&textView->textColor);
        source_set_color(&textView->textColor, AKColorTo8bit( &AKColorRed));
        
        
        textView->text = str_dup("");
        
        textView->font = AKFontGet( EmbeddedFontName , FontDefaultSize );
        
        if ( textView->font.handle == NULL)
        {
            return false;
        }
        
        textView->base.view.Draw = AKTextView_Draw;
        
        return true;
    }
    
    return false;
}

void AKTextViewDeInit( AKTextView* textView)
{
    assert(textView);
}



void AKTextViewSetText( AKTextView* textView, const char* text)
{
    
    assert(textView);
    assert(text);
    
    assert(textView->text);
    
    char* last = textView->text;
    
    textView->text = str_dup(text);
    free(last);
    
    //AKViewUpdateView( (AKView*) textView);
}

static char *substr(char const *input, size_t start, size_t len)
{
    char *ret = malloc(len+1);
    memcpy(ret, input+start, len);
    ret[len]  = '\0';
    return ret;
}

static void AKTextView_Draw(AKView * view , DrawContext* context)
{
    AKTextView* self = (AKTextView*) view;
    
    
    drawctx_set_source(context->ctx, &self->textColor);
    drawctx_set_font(context->ctx, self->font.handle);
    
    char* next = NULL;
    char* strLine = NULL;
    
    char* text = str_dup( self->text );
    char* textToFree = text;
    assert(text);
    
    //printf("Original '%s'\n" ,self->text );
    
    
    AKPoint pos = AKViewGetBounds( (const AKView*) self).origin;// AKPointMake(10 , 50);
    
    pos.x +=10;
    pos.y +=10;
    // Why coef 2 ??
    const size_t maxCharPerLine  = 2.f * (AKViewGetBounds( (const AKView*) self).size.width - 20.f) /  AKFontGetSize( &self->font);
    
    //printf(" num chars for size %lu %f\n",maxCharPerLine ,AKViewGetBounds( (const AKView*) self).size.width );
    
    while( (strLine = str_tok( text, "\n", &next)) != NULL)
    {
        
        //printf("Line: '%s' at %f %f \n",  strLine , pos.x , pos.y );
        size_t lineStrLen = str_width(strLine);
        
        size_t textOffset = 0;
        while (lineStrLen)
        {
            
            const size_t size = maxCharPerLine < lineStrLen? maxCharPerLine : lineStrLen ;
            char* l = substr(strLine, textOffset, size);
            //printf("Substr at %lu size %lu \n", textOffset , size);
            
            sysarg_t cpt_width;
            sysarg_t cpt_height;
            font_get_box(self->font.handle, l, &cpt_width, &cpt_height);
            
            DrawContextAddText(context , l, pos );
            
            pos.y += cpt_height;
            
            textOffset+=size;
            lineStrLen -= size;
            
            free(l);
            
            
        }
        // Draw
        
        
        // End Draw
        if (next == NULL)
        {
            break;
        }
        
        text = next;
    }

    free(textToFree);
    
}

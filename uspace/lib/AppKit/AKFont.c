//
//  AKFont.c
//  
//
//  Created by Manuel Deneu on 07/06/2018.
//

#include "AKFont.h"
#include <str.h>
#include <font/embedded.h>
#include <adt/list.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

const char EmbeddedFontName[] = "embedded";
const uint16_t FontDefaultSize = 16;

typedef struct _AKFontPriv
{
    font_t *font;
    uint16_t sizePoints;
    char* name;
    
    link_t link;
    
    size_t refCount;
    
} AKFontPriv;


typedef struct
{
    list_t fontStash;
    
} AKFontManager;


static AKFontManager _manager =
    {
        .fontStash = LIST_INITIALIZER(_manager.fontStash)
    };




AKFont AKFontGet( const char* name , uint16_t points )
{
    
    assert(name);
    printf("Search font '%s' , size %u \n" ,name , points );
    
    AKFontPriv* priv = NULL;
    list_foreach_safe(_manager.fontStash, cur_link, next_link)
    {
        AKFontPriv *cur_item = list_get_instance(cur_link, AKFontPriv, link);
        assert(cur_item);
        
        
        if ( str_cmp(name , cur_item->name) == 0 && points == cur_item->sizePoints )
        {
            priv = cur_item;
        }
        
        /*
        printf("%d\n", cur_item->value);
        list_remove(cur_link);
         */
    }
    
    if (priv == NULL)
    {
        printf("Font not found in stash \n");
        
        
        font_t* f = NULL;
        errno_t rc = embedded_font_create( &f, points);
        if (rc != EOK)
        {
            return (AKFont) { NULL};
        }
        
        
        priv = (AKFontPriv*) malloc(sizeof(AKFontPriv));
        assert(priv);
        priv->name = str_dup(name);
        priv->font = f;
        priv->sizePoints = points;
        priv->refCount = 1;
    
        list_append(&priv->link, &_manager.fontStash);
    
    
        return (AKFont) { priv->font};
    }
    
    
    printf("Font FOUND in stash \n");
    
    priv->refCount += 1;
    return (AKFont) { priv->font };
}


void AKFontRelease( AKFont* font)
{
    printf("AKFontRelease \n");
    
    list_foreach_safe(_manager.fontStash, cur_link, next_link)
    {
        AKFontPriv *item = list_get_instance(cur_link, AKFontPriv, link);
        
        assert(item);
        
        
        
        item->refCount--;
        printf("New ref count for font '%s' , size %u : %lu \n" ,item->name , item->sizePoints  , item->refCount);
        
        if ( item->refCount <=0)
        {
            printf("Time to release\n");
            // time to release font
            font_release(item->font);
            list_remove(&item->link);
            
            free(item);
        }
        
        //
        
    }
    //font_release(font->handle);
}

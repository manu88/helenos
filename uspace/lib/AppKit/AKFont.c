/*
 * Copyright (c) 2018 Manuel Deneu
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
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
#include "AKCommonsPriv.h"
#include <stdlib.h>
#include <errno.h>


const char EmbeddedFontName[] = "embedded";
const uint16_t FontDefaultSize = 16;

typedef struct _AKFontPriv
{
    AKFont font;
    
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




static AKFont AKFontMakeInvalid()
{
    return (AKFont){.handle = NULL , .sizePoints=0, .name = NULL };
}

AKFont AKFontGet( const char* name , uint16_t points )
{
    
    assert(name);
    AK_DEBUG_LOG("Search font '%s' , size %u \n" ,name , points );
    
    AKFontPriv* priv = NULL;
    list_foreach_safe(_manager.fontStash, cur_link, next_link)
    {
        AKFontPriv *cur_item = list_get_instance(cur_link, AKFontPriv, link);
        assert(cur_item);
        
        if ( str_cmp(name , cur_item->font.name) == 0 && points == cur_item->font.sizePoints )
        {
            priv = cur_item;
            break;
        }
        
    }
    
    if (priv == NULL)
    {
        AK_DEBUG_LOG("Font not found in stash \n");
        
        
        font_t* f = NULL;
        errno_t rc = embedded_font_create( &f, points);
        if (rc != EOK)
        {
            return AKFontMakeInvalid();
        }
        
        
        priv = (AKFontPriv*) malloc(sizeof(AKFontPriv));
        assert(priv);
        priv->font.name = str_dup(name);
        priv->font.handle = f;
        priv->font.sizePoints = points;
        priv->refCount = 1;
    
        list_append(&priv->link, &_manager.fontStash);
    
    
        return priv->font;
    }
    
    
    AK_DEBUG_LOG("Font FOUND in stash \n");
    
    priv->refCount += 1;
    return priv->font;
}


void AKFontRelease( AKFont* font)
{
    assert(font && font->name);
    AK_DEBUG_LOG("AKFontRelease \n");
    
    list_foreach_safe(_manager.fontStash, cur_link, next_link)
    {
        AKFontPriv *item = list_get_instance(cur_link, AKFontPriv, link);
        
        assert(item);
        
        
        if ( str_cmp(font->name , item->font.name) == 0 && font->sizePoints == item->font.sizePoints )
        {
            item->refCount--;
            AK_DEBUG_LOG("New ref count for font '%s' , size %u : %lu \n" ,item->font.name , item->font.sizePoints  , item->refCount);
            
            if ( item->refCount <=0)
            {
                AK_DEBUG_LOG("Time to release\n");
                // time to release font
                font_release(item->font.handle);
                
                free(item->font.name);
                list_remove(&item->link);
                
                free(item);
            }
            
            break;
        }
        
        //
        
    }
    //font_release(font->handle);
}

const char* AKFontGetName( const  AKFont* font)
{
    assert(font);
    
    return font->name;
}

uint16_t AKFontGetSize( const  AKFont* font)
{
    assert(font);
    
    return font->sizePoints;
}

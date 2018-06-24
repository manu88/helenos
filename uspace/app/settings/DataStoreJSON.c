//
//  DataStoreJSON.c
//  
//
//  Created by Manuel Deneu on 19/06/2018.
//

#include "DataStoreJSON.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cJSON.h>

bool DataStoreInitFromJSON(DataStore* dataStore , const char*buffer)
{
    assert(dataStore);
    assert(buffer);
    
    if (DataStoreInit(dataStore) == false)
    {
        return false;
    }
    
    cJSON *json= cJSON_Parse(buffer);
    
    if( json == NULL)
    {
        return false;
    }
    
    if(cJSON_IsObject(json) == false)
    {
        return false;
    }
    
    const cJSON *element = NULL;
    cJSON_ArrayForEach(element, json)
    {
        
        DataStoreAddValue(dataStore,element->valuestring , element->string );
        printf("add Key '%s' Value '%s'\n",element->string,element->valuestring);
        
    }
    
    
    cJSON_Delete(json);
    
    return true;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

typedef struct
{
    cJSON *root;
} JSONSerializationContext;

static bool TraverseDB(DataStore* dataStore,DBItem *item, void *context_)
{
    assert(context_);
    assert(dataStore);
    
    JSONSerializationContext* context = (JSONSerializationContext*) context_;
    assert(context->root);
    
    
    printf("Key '%s' Value '%s'\n" , item->key , item->value);
    
    cJSON *itemJSON = cJSON_CreateStringReference(item->value);
    
    if (itemJSON)
    {
       cJSON_AddItemToObjectCS(context->root, item->key, itemJSON);
    }
    //cJSON_CreateStringReference(const char *string);
    //cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item);
    return true;
}

char* DataStoreGetJSONBuffer(const DataStore* store)
{
    assert(store);
    
    JSONSerializationContext context;
    context.root = cJSON_CreateObject();
    
    DataStoreIterate(( DataStore*) store , TraverseDB , &context); // Cast from CONST!
    
    
    char* buffer = cJSON_Print(context.root);
    
    
    return buffer;
    
}

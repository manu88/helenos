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

char* DataStoreGetJSONBuffer(const DataStore* store)
{
    assert(dataStore);
    
    return NULL;
    
}

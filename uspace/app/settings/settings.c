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

#include <stdio.h>
#include <stdlib.h>
#include <cJSON.h>
#include <SettingsClient.h>
#include <DataStore.h>
#include <DataStoreJSON.h>

int main()
{
    
    
    DataStore ds;
    
    //cJSON *json= cJSON_Parse("{\"Key1\" : \"Value1\",\"Key2\" : \"Value2\"}");
    
    if( DataStoreInitFromJSON(&ds , "{\"Key1\" : \"Value1\",\"Key2\" : \"Value2\"}") == false)
    {
        return 1;
    }
    
    printf("+DS Size %lu\n" , DataStoreGetSize(&ds));
    
    printf("Value for key Key1 : '%s'\n" , DataStoreGetValueForKey(&ds , "Key1"));
    printf("Value for key Key2 : '%s'\n" , DataStoreGetValueForKey(&ds , "Key2"));
    printf("Value for key Key3 : '%s'\n" , DataStoreGetValueForKey(&ds , "Key3"));
    
    /*
    if( DataStoreInit(&ds) == false)
    {
        return 1;
    }
    
    //test();
    
    printf("+DS Size %lu\n" , DataStoreGetSize(&ds));
    DataStoreAddValue(&ds , "Key1" , "value1");
    printf("+DS Size %lu\n" , DataStoreGetSize(&ds));
    
    DataStoreAddValue(&ds , "Key2" , "value2");
    printf("+DS Size %lu\n" , DataStoreGetSize(&ds));
    
    DataStoreAddValue(&ds , "Key3" , "value3");
    printf("+DS Size %lu\n" , DataStoreGetSize(&ds));
    
    
    
    if(DataStoreAddValue(&ds , "Key1" , "value1") == false)
    {
        printf("+error adding again Key1\n");
    }
    
    printf("+DS Size %lu\n" , DataStoreGetSize(&ds));
    
    printf("Value for key Key1 : '%s'\n" , DataStoreGetValueForKey(&ds , "Key1"));
    printf("Value for key Key2 : '%s'\n" , DataStoreGetValueForKey(&ds , "Key2"));
    printf("Value for key Key3 : '%s'\n" , DataStoreGetValueForKey(&ds , "Key3"));
    printf("Value for key Key4 : '%s'\n" , DataStoreGetValueForKey(&ds , "Key4"));
    
    
    if(DataStoreRemoveKey(&ds , "Key2") == false)
    {
        printf("+error removing Key2\n");
    }
    
    printf("+DS Size %lu\n" , DataStoreGetSize(&ds));
    
    DataStoreDeInit(&ds);
    
    
    
    cJSON *json= cJSON_Parse("{\"Key1\" : \"Value1\",\"Key2\" : \"Value2\"}");
    
    if( json == NULL)
    {
        printf("JSON parsing error \n");
        return 2;
    }
    
    if(cJSON_IsObject(json))
    {
        printf("Is object\n");
    }
    
    const cJSON *element = NULL;
    cJSON_ArrayForEach(element, json)
    {
        printf("Key '%s' Value '%s'\n",element->string,element->valuestring);
        
    }
    
    cJSON_Delete(json);
     */
     
    
    return 0;
}

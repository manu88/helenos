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

#include <str.h>
#include <str_error.h>
#include <stdio.h>
#include <stdlib.h>
#include <cJSON.h>
#include <SettingsClient.h>
#include <DataStore.h>
#include <DataStoreJSON.h>


#include <loc.h> //loc_service_get_id

#include <IPCCommons.h>

#define NAME  "settings"

static bool TraverseDB(DataStore* dataStore,DBItem *item, void *context)
{
    printf("Key '%s' Value '%s'\n" , item->key , item->value);
    return true;
}

int main( int argc , char* argv[])
{
    
    service_id_t reg_dsid;
    errno_t rc = loc_service_get_id(NAME, &reg_dsid, 0);
    if (rc != EOK)
    {
        printf("%s: unable to find server: %s.\n",
               NAME, str_error(rc));
        return 10;
    }
    
    printf("loc_service_get_id OK \n");
    
    async_sess_t *reg_sess = loc_service_connect(reg_dsid, INTERFACE_COMPOSITOR, 0);
    if (reg_sess == NULL)
    {
        //free(win);
        return 11;
    }
    
    printf("loc_service_connect OK \n");
    
    
    async_exch_t *exch = async_exchange_begin(reg_sess);
    
    sysarg_t retVal = 0;
    errno_t ret = async_req_0_1(exch, SettingsIPC_Messages_Test ,&retVal/*, x, y, width, height*/);
    async_exchange_end(exch);
    
    if (ret != EOK)
    {
        printf("Err async_req_1_0 %i\n" , ret);
        
    }
    
    
    
    if (argc <2)
    {
        printf("Usage ... \n");
        return 1;
    }
    SettingsClient client;
    
    if ( SettingsClientInit(&client) == false)
    {
        printf("Unable to initialize SettingsClient\n");
        return 2;
    }
    
    if( DataStoreInitFromJSON(&client.ds , "{\"Key1\" : \"Value1\",\"Key2\" : \"Value2\"}") == false)
    {
        return 2;
    }
    
    printf("+DS Size %lu\n" , DataStoreGetSize(&client.ds));
    
    printf("Value for key Key1 : '%s'\n" , DataStoreGetValueForKey(&client.ds , "Key1"));
    printf("Value for key Key2 : '%s'\n" , DataStoreGetValueForKey(&client.ds , "Key2"));
    printf("Value for key Key3 : '%s'\n" , DataStoreGetValueForKey(&client.ds , "Key3"));
    
    
    printf("--- Iterate ----- \n");
    
    DataStoreIterate( &client.ds , TraverseDB , NULL);
    
    printf("--- Save to JSON ----- \n");
    
    char* outBuf =  DataStoreGetJSONBuffer(&client.ds);
    
    if (outBuf)
    {
        printf("'%s'\n" , outBuf);
    }
    
    free(outBuf);
    
    
    return 0;
    
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
     
    
    
}

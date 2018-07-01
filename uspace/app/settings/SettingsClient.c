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

#include <SettingsClient.h>
#include <stddef.h>
#include <stdlib.h>
#include <str.h>
#include <assert.h>

bool SettingsClientInit(SettingsClient* client, const char* clientID)
{
    assert(client);
    assert(clientID);
    
    
    client->clientID = str_dup(clientID);
    
    return true;
    
}

void SettingsClientDeInit(SettingsClient* client)
{
    assert(client);
    
    free( client->clientID);
}


bool SettingsClientAddValue(SettingsClient* client,const char* value , const char* key )
{
    assert(client);
    
    return false;
}

bool SettingsClientRemoveKey(SettingsClient* client,const char* key )
{
    assert(client);
    
    return false;
}

bool SettingsClientContainsKey(const SettingsClient* client , const char* key)
{
    assert(client);
    
    return false;
}

const char* SettingsClientGetValueForKey(const SettingsClient* client , const char* key)
{
    assert(client);
    
    return DataStoreGetValueForKey( &client->ds, key);
}

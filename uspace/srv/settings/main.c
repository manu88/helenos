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
#include <async.h>
#include <ipc/services.h>
#include <task.h>
#include <ipc/corecfg.h>
#include <loc.h>
#include <macros.h>
#include <errno.h>
#include <str_error.h>

#define NAME  "settings"

#include "IPCCommons.h"

static void onClient(cap_call_handle_t icall_handle, ipc_call_t *icall, void *arg)
{
    printf("Got a new client \n");
    /* Accept the connection */
    async_answer_0(icall_handle, EOK);
    
    
    while (true)
    {
        ipc_call_t call;
        cap_call_handle_t chandle = async_get_call(&call);
        sysarg_t method = IPC_GET_IMETHOD(call);
        
        if (!method)
        {
            /* The other side has hung up */
            printf("Client has hung up \n");
            async_answer_0(chandle, EOK);
            return;
        }
        else if (method == SettingsIPC_Messages_Test)
        {
            printf("Got SettingsIPC_Messages_Test \n");
        }
        else
        {
            printf("Got a message \n");
        }
    } // while (true)
    
    
}

int main(int argc, char *argv[])
{
	printf("%s: Settings DB Service\n", NAME);

    
    async_set_fallback_port_handler(onClient, NULL);
    
    errno_t rc = loc_server_register(NAME);
    if (rc != EOK)
    {
        printf("%s: Failed registering server: %s.\n",
               NAME, str_error(rc));
        return -1;
    }
    
    service_id_t sid;
    rc = loc_service_register(NAME, &sid);
    if (rc != EOK)
    {
        printf("%s: Failed registering service: %s.\n",
               NAME, str_error(rc));
        return -1;
    }


	//task_retval(0);
	async_manager();

	return 0;
}

/** @}
 */

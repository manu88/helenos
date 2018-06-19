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


static void onClient(cap_call_handle_t icall_handle, ipc_call_t *icall, void *arg)
{
    printf("Got a new client \n");
    /* Accept the connection */
    async_answer_0(icall_handle, EOK);
    
    
}

int main(int argc, char *argv[])
{
	printf("%s: Task Monitoring Service\n", NAME);

    
    async_set_fallback_port_handler(onClient, NULL);
    
    errno_t rc = loc_server_register(NAME);
    if (rc != EOK)
    {
        printf("%s: Failed registering server: %s.\n",
               NAME, str_error(rc));
        return -1;
    }
    
    service_id_t sid;
    rc = loc_service_register(SERVICE_NAME_CORECFG, &sid);
    if (rc != EOK)
    {
        printf("%s: Failed registering service: %s.\n",
               NAME, str_error(rc));
        return -1;
    }


	task_retval(0);
	async_manager();

	return 0;
}

/** @}
 */

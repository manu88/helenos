

#include <stdio.h>
#include <async.h>
#include <ipc/services.h>
#include <task.h>
#include <ipc/corecfg.h>
#include <loc.h>
#include <macros.h>
#include <errno.h>
#include <str_error.h>

#define NAME  "taskmon"

static bool write_core_files;

static void corecfg_client_conn(cap_call_handle_t, ipc_call_t *, void *);

static void fault_event(ipc_call_t *call, void *arg)
{
	const char *fname;
	char *s_taskid;
	char *dump_fname;
	errno_t rc;

	task_id_t taskid;
	uintptr_t thread;

	taskid = MERGE_LOUP32(IPC_GET_ARG1(*call), IPC_GET_ARG2(*call));
	thread = IPC_GET_ARG3(*call);

	if (asprintf(&s_taskid, "%" PRIu64, taskid) < 0) {
		printf("Memory allocation failed.\n");
		return;
	}

	printf(NAME ": Task %" PRIu64 " fault in thread %p.\n", taskid,
	    (void *) thread);

	fname = "/app/taskdump";

	if (write_core_files) {
		if (asprintf(&dump_fname, "/data/core%" PRIu64, taskid) < 0) {
			printf("Memory allocation failed.\n");
			return;
		}

		printf(NAME ": Executing %s -c %s -t %s\n", fname, dump_fname, s_taskid);
		rc = task_spawnl(NULL, NULL, fname, fname, "-c", dump_fname, "-t", s_taskid,
		    NULL);
	} else {
		printf(NAME ": Executing %s -t %s\n", fname, s_taskid);
		rc = task_spawnl(NULL, NULL, fname, fname, "-t", s_taskid, NULL);
	}

	if (rc != EOK) {
		printf("%s: Error spawning %s (%s).\n", NAME, fname,
		    str_error(rc));
	}
}

static void corecfg_get_enable_srv(cap_call_handle_t icall_handle, ipc_call_t *icall)
{
	async_answer_1(icall_handle, EOK, write_core_files);
}

static void corecfg_set_enable_srv(cap_call_handle_t icall_handle, ipc_call_t *icall)
{
	write_core_files = IPC_GET_ARG1(*icall);
	async_answer_0(icall_handle, EOK);
}

static void corecfg_client_conn(cap_call_handle_t icall_handle, ipc_call_t *icall, void *arg)
{
	/* Accept the connection */
	async_answer_0(icall_handle, EOK);

	while (true) {
		ipc_call_t call;
		cap_call_handle_t chandle = async_get_call(&call);
		sysarg_t method = IPC_GET_IMETHOD(call);

		if (!method) {
			/* The other side has hung up */
			async_answer_0(chandle, EOK);
			return;
		}

		switch (method) {
		case CORECFG_GET_ENABLE:
			corecfg_get_enable_srv(chandle, &call);
			break;
		case CORECFG_SET_ENABLE:
			corecfg_set_enable_srv(chandle, &call);
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	printf("%s: Task Monitoring Service\n", NAME);

#ifdef CONFIG_WRITE_CORE_FILES
	write_core_files = true;
#else
	write_core_files = false;
#endif
	if (async_event_subscribe(EVENT_FAULT, fault_event, NULL) != EOK) {
		printf("%s: Error registering fault notifications.\n", NAME);
		return -1;
	}

	async_set_fallback_port_handler(corecfg_client_conn, NULL);

	errno_t rc = loc_server_register(NAME);
	if (rc != EOK) {
		printf("%s: Failed registering server: %s.\n",
		    NAME, str_error(rc));
		return -1;
	}

	service_id_t sid;
	rc = loc_service_register(SERVICE_NAME_CORECFG, &sid);
	if (rc != EOK) {
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

/*
 * Copyright (c) 2006 Ondrej Palkovsky
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

/** @addtogroup libc
 * @{
 */
/** @file
 */

#ifndef LIBC_PRIVATE_ASYNC_H_
#define LIBC_PRIVATE_ASYNC_H_

#include <async.h>
#include <adt/list.h>
#include <fibril.h>
#include <fibril_synch.h>
#include <sys/time.h>
#include <stdbool.h>

/** Structures of this type are used to track the timeout events. */
typedef struct {
	/** If true, this struct is in the timeout list. */
	bool inlist;

	/** Timeout list link. */
	link_t link;

	/** If true, we have timed out. */
	bool occurred;

	/** Expiration time. */
	struct timeval expires;
} to_event_t;

/** Structures of this type are used to track the wakeup events. */
typedef struct {
	/** If true, this struct is in a synchronization object wait queue. */
	bool inlist;

	/** Wait queue linkage. */
	link_t link;
} wu_event_t;

/** Structures of this type represent a waiting fibril. */
typedef struct {
	/** Identification of and link to the waiting fibril. */
	fid_t fid;

	/** If true, this fibril is currently active. */
	bool active;

	/** Timeout wait data. */
	to_event_t to_event;
	/** Wakeup wait data. */
	wu_event_t wu_event;
} awaiter_t;

/** Session data */
struct async_sess {
	/** List of inactive exchanges */
	list_t exch_list;

	/** Session interface */
	iface_t iface;

	/** Exchange management style */
	exch_mgmt_t mgmt;

	/** Session identification */
	cap_phone_handle_t phone;

	/** First clone connection argument */
	sysarg_t arg1;

	/** Second clone connection argument */
	sysarg_t arg2;

	/** Third clone connection argument */
	sysarg_t arg3;

	/** Exchange mutex */
	fibril_mutex_t mutex;

	/** Number of opened exchanges */
	atomic_t refcnt;

	/** Mutex for stateful connections */
	fibril_mutex_t remote_state_mtx;

	/** Data for stateful connections */
	void *remote_state_data;
};

/** Exchange data */
struct async_exch {
	/** Link into list of inactive exchanges */
	link_t sess_link;

	/** Link into global list of inactive exchanges */
	link_t global_link;

	/** Session pointer */
	async_sess_t *sess;

	/** Exchange identification */
	cap_phone_handle_t phone;
};

extern void awaiter_initialize(awaiter_t *);

extern void __async_server_init(void);
extern void __async_client_init(void);
extern void __async_ports_init(void);
extern void async_insert_timeout(awaiter_t *);

extern errno_t async_create_port_internal(iface_t, async_port_handler_t,
    void *, port_id_t *);
extern async_port_handler_t async_get_port_handler(iface_t, port_id_t, void **);

#endif

/** @}
 */

/*
 * Copyright (c) 2006 Jakub Jermar
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

/** @addtogroup genarchmm
 * @{
 */
/** @file
 */

/*
 * This is the generic 4-level page table interface.
 * Architectures that use hierarchical page tables
 * are supposed to implement *_ARCH macros.
 */

#ifdef CONFIG_PAGE_PT

#ifndef KERN_PAGE_PT_H_
#define KERN_PAGE_PT_H_

#include <arch/types.h>
#include <mm/as.h>
#include <mm/page.h>

/*
 * Number of entries in each level.
 */
#define PTL0_ENTRIES			PTL0_ENTRIES_ARCH
#define PTL1_ENTRIES			PTL1_ENTRIES_ARCH
#define PTL2_ENTRIES			PTL2_ENTRIES_ARCH
#define PTL3_ENTRIES			PTL3_ENTRIES_ARCH

/* Table sizes in each level */
#define PTL0_SIZE			PTL0_SIZE_ARCH
#define PTL1_SIZE			PTL1_SIZE_ARCH
#define PTL2_SIZE			PTL2_SIZE_ARCH
#define PTL3_SIZE			PTL3_SIZE_ARCH

/*
 * These macros process vaddr and extract those portions
 * of it that function as indices to respective page tables.
 */
#define PTL0_INDEX(vaddr)		PTL0_INDEX_ARCH(vaddr)
#define PTL1_INDEX(vaddr)		PTL1_INDEX_ARCH(vaddr)
#define PTL2_INDEX(vaddr)		PTL2_INDEX_ARCH(vaddr)
#define PTL3_INDEX(vaddr)		PTL3_INDEX_ARCH(vaddr)

#define SET_PTL0_ADDRESS(ptl0)		SET_PTL0_ADDRESS_ARCH(ptl0)

/*
 * These macros traverse the 4-level tree of page tables,
 * each descending by one level.
 */
#define GET_PTL1_ADDRESS(ptl0, i)	GET_PTL1_ADDRESS_ARCH(ptl0, i)
#define GET_PTL2_ADDRESS(ptl1, i)	GET_PTL2_ADDRESS_ARCH(ptl1, i)
#define GET_PTL3_ADDRESS(ptl2, i)	GET_PTL3_ADDRESS_ARCH(ptl2, i)
#define GET_FRAME_ADDRESS(ptl3, i)	GET_FRAME_ADDRESS_ARCH(ptl3, i)

/*
 * These macros are provided to change the shape of the 4-level tree of page
 * tables on respective level.
 */
#define SET_PTL1_ADDRESS(ptl0, i, a)	SET_PTL1_ADDRESS_ARCH(ptl0, i, a)
#define SET_PTL2_ADDRESS(ptl1, i, a)	SET_PTL2_ADDRESS_ARCH(ptl1, i, a)
#define SET_PTL3_ADDRESS(ptl2, i, a)	SET_PTL3_ADDRESS_ARCH(ptl2, i, a)
#define SET_FRAME_ADDRESS(ptl3, i, a)	SET_FRAME_ADDRESS_ARCH(ptl3, i, a)

/*
 * These macros are provided to query various flags within the page tables.
 */
#define GET_PTL1_FLAGS(ptl0, i)		GET_PTL1_FLAGS_ARCH(ptl0, i)
#define GET_PTL2_FLAGS(ptl1, i)		GET_PTL2_FLAGS_ARCH(ptl1, i)
#define GET_PTL3_FLAGS(ptl2, i)		GET_PTL3_FLAGS_ARCH(ptl2, i)
#define GET_FRAME_FLAGS(ptl3, i)	GET_FRAME_FLAGS_ARCH(ptl3, i)

/*
 * These macros are provided to set/clear various flags within the page tables.
 */
#define SET_PTL1_FLAGS(ptl0, i, x)	SET_PTL1_FLAGS_ARCH(ptl0, i, x)
#define SET_PTL2_FLAGS(ptl1, i, x)	SET_PTL2_FLAGS_ARCH(ptl1, i, x)
#define SET_PTL3_FLAGS(ptl2, i, x)	SET_PTL3_FLAGS_ARCH(ptl2, i, x)
#define SET_FRAME_FLAGS(ptl3, i, x)	SET_FRAME_FLAGS_ARCH(ptl3, i, x)

/*
 * Macros for querying the last-level PTEs.
 */
#define PTE_VALID(p)		PTE_VALID_ARCH((p))
#define PTE_PRESENT(p)		PTE_PRESENT_ARCH((p))
#define PTE_GET_FRAME(p)	PTE_GET_FRAME_ARCH((p))
#define PTE_READABLE(p)		1
#define PTE_WRITABLE(p)		PTE_WRITABLE_ARCH((p))
#define PTE_EXECUTABLE(p)	PTE_EXECUTABLE_ARCH((p))

extern as_operations_t as_pt_operations;
extern page_mapping_operations_t pt_mapping_operations;

extern void page_mapping_insert_pt(as_t *as, uintptr_t page, uintptr_t frame,
    int flags);
extern pte_t *page_mapping_find_pt(as_t *as, uintptr_t page);

#endif

#endif

/** @}
 */

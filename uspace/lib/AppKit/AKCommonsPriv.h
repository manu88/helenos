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
//
//  AKCommonsPriv.h
//  
//
//  Created by Manuel Deneu on 07/06/2018.
//

#ifndef AKCommonsPriv_h
#define AKCommonsPriv_h

#ifndef AK_DEBUG
#define AK_DEBUG
#endif

#include <assert.h>
#ifdef AK_DEBUG
#include <stdio.h>
#endif


#ifdef AK_DEBUG
#define AK_DEBUG_LOG( ...) printf( __VA_ARGS__)
#else
#define AK_DEBUG_LOG( ...) // no-op
#endif /* #ifdef AK_DEBUG */


/* Do not put any vital code into DEBUG_ASSERT since it will turn into a no-op on release build. */
#ifdef AK_DEBUG
#define AK_DEBUG_ASSERT(x) assert(x)
#else
#define AK_DEBUG_ASSERT(x)
#endif /* #ifdef AK_DEBUG */


#endif /* AKCommonsPriv_h */

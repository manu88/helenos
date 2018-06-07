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

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

#include <AKCommonsPriv.h>
#include "AKScreen.h"
#include <ipc/window.h>


static const char* defaultComp = "comp:0/disp";

bool AKScreenManagerInit(AKScreenManager* manager, const char* optionalCompositorName)
{
    assert(manager);
    
    service_id_t reg_dsid;
    
    errno_t rc = loc_service_get_id( optionalCompositorName? optionalCompositorName : defaultComp, &reg_dsid, 0);
    if (rc != EOK)
    {
        return false;
    }
    
    manager->reg_sess = loc_service_connect(reg_dsid, INTERFACE_COMPOSITOR, 0);
    if (manager->reg_sess == NULL)
    {
        
        return false;
    }
    
    return true;
}

void AKScreenManagerDeInit(AKScreenManager* manager)
{
    assert(manager);
    async_hangup(manager->reg_sess);
}


/*
bool DisplaySuspend(AKScreenManager* manager,  size_t displayIndex)
{
    assert(manager);
    sysarg_t retVal = 0;
    
    async_exch_t *exch = async_exchange_begin(manager->reg_sess);
    
    errno_t ret = async_req_1_1(exch, WINDOW_SUSPEND,displayIndex ,&retVal);
    async_exchange_end(exch);
    
    return ret == EOK;
}
*/


bool AKScreenManagerGetModForDisplay(AKScreenManager* manager,AKScreenConfiguration* config, size_t displayIndex , size_t modIndex)
{
    assert(manager);
    assert(config);
    
    sysarg_t w = 0;
    sysarg_t h = 0;
    
    async_exch_t *exch = async_exchange_begin(manager->reg_sess);
    if(exch == NULL)
    {
        return false;
    }
    errno_t ret = async_req_1_2(exch, WINDOW_DISPLAY_MODS,displayIndex ,&w , &h);
    async_exchange_end(exch);
    
    if (ret != EOK)
    {
        AK_DEBUG_LOG("Err async_req_1_0 %i\n" , ret);
        
        return false;
        
    }
    
    config->size = AKSizeMake( w , h);
    
    
    return true;
}


size_t AKScreenManagerGetModCountForDisplay(AKScreenManager* manager , size_t displayIndex)
{
    assert(manager);
    sysarg_t retVal = 0;
    
    async_exch_t *exch = async_exchange_begin(manager->reg_sess);
    if(exch == NULL)
    {
        return 0;
    }
    errno_t ret = async_req_1_1(exch, WINDOW_DISPLAY_MODS_COUNT,displayIndex ,&retVal);
    async_exchange_end(exch);
    
    if (ret != EOK)
    {
        AK_DEBUG_LOG("Err async_req_1_0 %i\n" , ret);
    }
    
    return (size_t) retVal;
}

size_t AKScreenManagerGetNumDisplays(AKScreenManager* manager)
{
    assert(manager);
    sysarg_t retVal = 0;
    
    async_exch_t *exch = async_exchange_begin(manager->reg_sess);
    if(exch == NULL)
    {
        return 0;
    }
    errno_t ret = async_req_0_1(exch, WINDOW_DISPLAY_COUNT ,&retVal/*, x, y, width, height*/);
    async_exchange_end(exch);
    
    if (ret != EOK)
    {
        AK_DEBUG_LOG("Err async_req_1_0 %i\n" , ret);
        
    }
    
    
    
    
    return (size_t) retVal;
}

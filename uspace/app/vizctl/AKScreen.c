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

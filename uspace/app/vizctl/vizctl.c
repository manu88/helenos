#include <stdio.h>
#include "AKScreen.h"


int main()
{
    
    AKScreenManager screenManager;

    if (AKScreenManagerInit(&screenManager , NULL) == false)
    {
        return 1;
    }
    
    // 1 get num of displays
    const size_t numDisps = AKScreenManagerGetNumDisplays(&screenManager);
    printf("Num displays = %lu \n" , numDisps);
    
    
    // 2 for each display, list mods
    
    for(size_t  displayIndex = 0; displayIndex <  numDisps; ++displayIndex )
    {
        const size_t numMods = AKScreenManagerGetModCountForDisplay(&screenManager , displayIndex);
        printf("Num mods for displays %lu = %lu \n" , displayIndex, numMods );
        
        
        AKScreenConfiguration config;
        
        for(size_t  modIndex = 0; modIndex <  numMods; ++modIndex )
        {
            if (AKScreenManagerGetModForDisplay(&screenManager,&config,displayIndex , modIndex) )
            {
                printf("Display %li / Mod %li : W=%f  =%f\n"  ,displayIndex,modIndex, config.size.width , config.size.height);
            }
        }
    }
    
    AKScreenManagerDeInit(&screenManager);
    
    //async_manager();
    
    return 0;
}

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

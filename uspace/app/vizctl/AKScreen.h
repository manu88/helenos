#ifndef AKSCREEN_H
#define AKSCREEN_H

#include <loc.h>
#include <AKGeometry.h>


typedef struct
{
    AKSize size;
    
} AKScreenConfiguration;

typedef struct
{
    async_sess_t *reg_sess;
    
} AKScreenManager;



bool AKScreenManagerInit(AKScreenManager* manager, const char* optionalCompositorName);
void AKScreenManagerDeInit(AKScreenManager* manager);





size_t AKScreenManagerGetNumDisplays( AKScreenManager* manager );
size_t AKScreenManagerGetModCountForDisplay(AKScreenManager* manager , size_t displayIndex);

bool AKScreenManagerGetModForDisplay(AKScreenManager* manager,AKScreenConfiguration* config, size_t displayIndex , size_t modIndex);
//bool DisplaySuspend(AKScreenManager* manager,  size_t displayIndex);












#endif /* AKSCREEN_H*/

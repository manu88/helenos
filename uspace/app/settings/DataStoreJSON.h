//
//  DataStoreJSON.h
//  
//
//  Created by Manuel Deneu on 19/06/2018.
//

#ifndef DataStoreJSON_h
#define DataStoreJSON_h

#include <DataStore.h>

bool DataStoreInitFromJSON(DataStore* dataStore , const char*buffer);

char* DataStoreGetJSONBuffer(const DataStore* store);

#endif /* DataStoreJSON_h */

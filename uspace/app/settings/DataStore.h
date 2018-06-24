//
//  DataStore.h
//  
//
//  Created by Manuel Deneu on 19/06/2018.
//

#ifndef DataStore_h
#define DataStore_h

#include <adt/hash_table.h> // just for ht_link_t


typedef char DBValue;

typedef struct
{
    ht_link_t link;
    char* key;
    DBValue* value;
    
} DBItem;


typedef struct _DataStore
{
    hash_table_t hashTable;
}DataStore;


bool DataStoreInit(DataStore* dataStore);
void DataStoreDeInit(DataStore* dataStore);

bool DataStoreAddValue(DataStore* dataStore,const DBValue* value , const char* key );
bool DataStoreRemoveKey(DataStore* dataStore,const char* key );
bool DataStoreContainsKey(const DataStore* dataStore , const char* key);

const DBValue* DataStoreGetValueForKey(const DataStore* dataStore , const char* key);


typedef bool (*TraverseDataStore)( DataStore* dataStore ,DBItem *item, void *context);

void DataStoreIterate( DataStore* dataStore , TraverseDataStore method , void* context);


size_t DataStoreGetSize(const DataStore* dataStore);



#endif /* DataStore_h */

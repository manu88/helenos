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
    const char* key;
    DBValue* value;
    
} DBItem;


typedef struct
{
    hash_table_t hashTable;
}DataStore;

void test(void);

#endif /* DataStore_h */

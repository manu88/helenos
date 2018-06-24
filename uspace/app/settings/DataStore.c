//
//  DataStore.c
//  
//
//  Created by Manuel Deneu on 19/06/2018.
//

#include <assert.h>
#include <DataStore.h>
#include <stdlib.h>
#include <stdio.h>
#include <adt/hash.h>
#include <str.h>

static size_t item_hash(const ht_link_t *item);
static size_t key_hash(void *key);
static bool item_equal(const ht_link_t *item1, const ht_link_t *item2);
static bool key_equal(void *key, const ht_link_t *item);
static void remove_item(ht_link_t *item);

static hash_table_ops_t hashTableOps =
{
    .hash = item_hash,
    .key_hash = key_hash,
    .equal = item_equal,
    .key_equal = key_equal,
    .remove_callback = remove_item
};

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

static size_t hashString(const char *str)
{
    
    size_t hash = 0;

    int c;
    
    while ((c = *str++))
    {
        hash = hash_combine(hash, c);
    }
    
    return hash;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

/** Returns the hash of the key stored in the item (ie its lookup key). */
static size_t item_hash(const ht_link_t *item_)
{
    const DBItem* item = (const DBItem*)item_;
    //printf("item_hash key '%s' value '%s'\n" , item->key , item->value);
    return hashString(item->key);
}

/** Returns the hash of the key. */
static size_t key_hash(void *key)
{
    //printf("key_hash key '%s' \n" , (const char*)key );
    return hashString(key);
}

/** True if the items are equal (have the same lookup keys). */
static bool item_equal(const ht_link_t *item1_, const ht_link_t *item2_)
{
    const DBItem* item1 = (const DBItem*)item1_;
    const DBItem* item2 = (const DBItem*)item2_;
    //printf("item_equal 1:'%s' '%s 2:'%s' '%s'\n" , item1->key, item1->value,item2->key, item2->value );
    return str_cmp(item1->key , item2->key) == 0;
}

/** Returns true if the key is equal to the item's lookup key. */
static bool key_equal(void *key, const ht_link_t *item_)
{
    const DBItem* item = (const DBItem*)item_;
    //printf("key_equal\n");
    return str_cmp(key , item->key) == 0;
}

/** Hash table item removal callback.
 *
 * Must not invoke any mutating functions of the hash table.
 *
 * @param item Item that was removed from the hash table.
 */
static void remove_item(ht_link_t *item_)
{
    DBItem* item = (DBItem*)item_;
    
    free(item->key);
    free(item->value);
    free(item);
    //printf("remove_item\n");
}


/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */

bool DataStoreInit(DataStore* dataStore)
{
    assert(dataStore);
    size_t init_size = 0;// default
    size_t max_load  = 0;// default
    
    if(hash_table_create(&dataStore->hashTable, init_size, max_load, &hashTableOps) == false)
    {
        //printf("Error creating hashtable\n");
        return false;
    }
    
    return true;
}
void DataStoreDeInit(DataStore* dataStore)
{
    assert(dataStore);
    hash_table_destroy(&dataStore->hashTable);
}

bool DataStoreAddValue(DataStore* dataStore,const DBValue* value , const char* key )
{
    assert(dataStore);
    assert(value);
    assert(key);
    
    DBItem* item = (DBItem*) malloc( sizeof(DBItem));
    item->key = str_dup(key);
    item->value = str_dup(value);
    
    return hash_table_insert_unique(&dataStore->hashTable, &item->link);
    
}

bool DataStoreRemoveKey(DataStore* dataStore,const char* key )
{
    assert(dataStore);
    assert(key);
    
    return hash_table_remove(&dataStore->hashTable,(void*) key) == 1; // CAST TO CONST!
}

bool DataStoreContainsKey(const DataStore* dataStore , const char* key)
{
    return DataStoreGetValueForKey(dataStore , key) != NULL;
}

const DBValue* DataStoreGetValueForKey(const DataStore* dataStore , const char* key)
{
    assert(dataStore);
    assert(key);
    
    ht_link_t * link = hash_table_find(&dataStore->hashTable, (void *)key); // CAST TO CONST!
    
    if (!link)
    {
        return NULL;
    }
    
    const DBItem* item = (const DBItem*)link;
    
    return item->value;
}

size_t DataStoreGetSize(const DataStore* dataStore)
{
    assert(dataStore);
    
    return hash_table_size( (hash_table_t*) &dataStore->hashTable); // CAST TO CONST!
}

/* **** **** **** **** **** **** **** **** **** **** **** **** */

typedef struct
{
    DataStore* dataStore;
    TraverseDataStore method;
    void *ctx;
    
}ContextIterator;

static bool IterateDataStore(ht_link_t *item_, void *context)
{
    assert(context);
    DBItem* item = (DBItem*)item_;
    
    ContextIterator* internalContext = (ContextIterator*) context;
    
    return internalContext->method( internalContext->dataStore , item ,internalContext->ctx);
}

void DataStoreIterate( DataStore* dataStore , TraverseDataStore method , void* context)
{
    assert(dataStore);
    
    ContextIterator internalContext;
    internalContext.dataStore = dataStore;
    internalContext.ctx    = context;
    internalContext.method = method;
    
    hash_table_apply( &dataStore->hashTable,IterateDataStore/* method*/, &internalContext);

}


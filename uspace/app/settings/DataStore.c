//
//  DataStore.c
//  
//
//  Created by Manuel Deneu on 19/06/2018.
//

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


/** Returns the hash of the key stored in the item (ie its lookup key). */
static size_t item_hash(const ht_link_t *item_)
{
    const DBItem* item = (const DBItem*)item_;
    printf("item_hash key '%s' value '%s'\n" , item->key , item->value);
    return hashString(item->key);
}

/** Returns the hash of the key. */
static size_t key_hash(void *key)
{
    
    printf("key_hash key '%s' \n" , (const char*)key );
    return hashString(key);
}

/** True if the items are equal (have the same lookup keys). */
static bool item_equal(const ht_link_t *item1_, const ht_link_t *item2_)
{
    const DBItem* item1 = (const DBItem*)item1_;
    const DBItem* item2 = (const DBItem*)item2_;
    printf("item_equal 1:'%s' '%s 2:'%s' '%s'\n" , item1->key, item1->value,item2->key, item2->value );
    return str_cmp(item1->key , item2->key) == 0;
}

/** Returns true if the key is equal to the item's lookup key. */
static bool key_equal(void *key, const ht_link_t *item)
{
    printf("key_equal\n");
    return false;
}

/** Hash table item removal callback.
 *
 * Must not invoke any mutating functions of the hash table.
 *
 * @param item Item that was removed from the hash table.
 */
static void remove_item(ht_link_t *item)
{
    printf("remove_item\n");
}

void test()
{
    
    
    hash_table_t hashTable;
    
    size_t init_size = 0;// default
    size_t max_load  = 0;// default
    
    if(hash_table_create(&hashTable, init_size, max_load, &hashTableOps) == false)
    {
        printf("Error creating hashtable\n");
        return;
    }
    
    printf("hashtable OK\n");
    
    printf("hashtable Size %lu\n" , hash_table_size(&hashTable));
    
    DBItem* item = (DBItem*) malloc( sizeof(DBItem));
    item->key = str_dup("Key1");
    item->value = str_dup("Value1");
    
    if(hash_table_insert_unique(&hashTable, &item->link) == false)
    {
        printf("Error adding item1\n");
    }
    
    printf("hashtable Size %lu\n" , hash_table_size(&hashTable));
    
    DBItem* item2 = (DBItem*) malloc( sizeof(DBItem));
    item2->key = str_dup("Key1");
    item2->value = str_dup("Value2");
    
    if(hash_table_insert_unique(&hashTable, &item2->link) == false)
    {
        printf("Error adding item2\n");
    }
    
    printf("hashtable Size %lu\n" , hash_table_size(&hashTable));
    
}

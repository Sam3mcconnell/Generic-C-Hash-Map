/**
    @file map.h
    @author Samuel McConnell (semcconn)
    Header for the map component, a hash map.
*/

#ifndef MAP_H
#define MAP_H

#include "value.h"
#include <stdbool.h>

/** Incomplete type for the Map representation. */
typedef struct MapStruct Map;

/** Make an empty map.
    @param len Initial length of the hash table.
    @return pointer to a new map.
*/
Map *makeMap(int len);

/** Get the size of the given map.
    @param m Pointer to the map.
    @return Number of key/value pairs in the map. */
int mapSize(Map *m);

/** Add a new key / value pair to the map, or replace the value
    associeted with the given key.  The map will take ownership of the
    given key and value objects.
    @param m Map to add a key/value pair to.
    @param k Key to add to map.
    @param v Value to associate with the key.
*/
void mapSet(Map *m, Value *key, Value *val);

/** Return the value associated with the given key. The returned Value
    is still owned by the map.
    @param m Map to query.
    @param k Key to look for in the map.
    @return Value associated with the given key, or NULL if the key
    isn't in the map.
*/
Value *mapGet(Map *m, Value *key);

/** Remove a key / value pair from the given map.
    @param m Map to remove a key from
    @param k Key to look for and remove in the map.
    @return true if the key was successfully removed (i.e., it was in
    the map)
*/
bool mapRemove(Map *m, Value *key);

/** Free all the memory used to store a map, including all the
    memory in its key/value pairs.
    @param m The map to free.
*/
void freeMap(Map *m);

#endif

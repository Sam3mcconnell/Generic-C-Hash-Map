// Simple test program for the text component.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "value.h"
#include "map.h"

int main()
{
  // Make a few values we use below.
  Value v5, v10, v15, v20;
  parseInteger(&v5, "5");
  parseInteger(&v10, "10");
  parseInteger(&v15, "15");
  parseInteger(&v20, "20");

  // Make a map with 3 slots in its hash table.
  Map *map = makeMap(3);
  assert(mapSize(map) == 0);

  // Put a the entry 5 -> 10 in the map.
  Value key, val;
  parseInteger(&key, "5");
  parseInteger(&val, "10");
  mapSet(map, &key, &val);
  assert(mapSize(map) == 1);

  Value *v = mapGet(map, &v5);
  assert(v10.equals(&v10, v));

  // Put a second entry, 10 -> 15 in the map.
  parseInteger(&key, "10");
  parseInteger(&val, "15");
  mapSet(map, &key, &val);
  assert(mapSize(map) == 2);

  v = mapGet(map, &v10);
  assert(v15.equals(&v15, v));

  // Check the key / value that was previously there.
  v = mapGet(map, &v5);
  assert(v10.equals(&v10, v));

  // Change the value for key 5. to 5 -> 20
  parseInteger(&key, "5");
  parseInteger(&val, "20");
  mapSet(map, &key, &val);
  assert(mapSize(map) == 2);

  v = mapGet(map, &v5);
  assert(v20.equals(&v20, v));

  // Remove the value for key 10.
  assert(mapRemove(map, &v10));
  assert(mapSize(map) == 1);

  // Make sure that value is gone.
  v = mapGet(map, &v10);
  assert(v == NULL);

  // Try to remove a value that's not there.
  assert(mapRemove(map, &v10) == false);
  assert(mapSize(map) == 1);

  // Free our maps.
  freeMap(map);

  // Free our temporary values.
  v5.empty(&v5);
  v10.empty(&v10);
  v15.empty(&v15);
  v20.empty(&v20);

  return EXIT_SUCCESS;
}

/**
    @file map.c
    @author
    Implementation for the map component, a hash map.
  */

#include "map.h"
#include <stdlib.h>
#include <stdio.h>

#include "value.h"

typedef struct MapPairStruct MapPair;

/** Key/Value pair to put in a hash map. */
struct MapPairStruct
{
  /** Key part of this node, stored right in the node to improve locality. */
  Value key;

  /** Value part of this node, stored right in the node to improve locality. */
  Value val;

  /** Pointer to the next node at the same element of this table. */
  MapPair *next;
};

/** Representation of a hash table implementation of a map. */
struct MapStruct
{
  /** Table of key / value pairs. */
  MapPair **table;

  /** Length of the table. */
  int tlen;

  /** Number of key / value pairs in the map. */
  int size;
};

Map *makeMap(int len)
{
  Map *newMap = (Map *)malloc(sizeof(Map));
  newMap->table = (MapPair **)calloc(len, sizeof(MapPair *));
  newMap->tlen = len;
  newMap->size = 0;

  for (int i = 0; i < len; i++)
  {
    newMap->table[i] = NULL;
  }
  return newMap;
}

int mapSize(Map *m)
{
  return m->size;
}

void mapSet(Map *m, Value *key, Value *val)
{
  unsigned int index = key->hash(key) % m->tlen;
  MapPair *current = m->table[index];

  if (current != NULL)
  {
    while (current != NULL)
    {
      if (key->equals(&current->key, key))
      {
        key->empty(key);
        current->val.empty(&current->val);
        current->val = *val;
        return;
      }
      current = current->next;
    }
  }

  MapPair *newPair = malloc(sizeof(MapPair));
  Value *destKey = malloc(sizeof(Value));

  key->move(key, destKey);
  free(destKey);
  newPair->key = *key;
  newPair->val = *val;
  newPair->next = m->table[index];
  m->table[index] = newPair;
  m->size++;
}

Value *mapGet(Map *m, Value *key)
{
  unsigned int index = key->hash(key) % m->tlen;
  MapPair *current = m->table[index];
  while (current != NULL)
  {
    if (key->equals(&current->key, key))
    {
      return &(current->val);
    }
    current = current->next;
  }
  return NULL;
}

bool mapRemove(Map *m, Value *key)
{
  unsigned int index = key->hash(key) % m->tlen;
  MapPair *current = m->table[index];
  MapPair *prev = NULL;
  while (current != NULL)
  {
    if (key->equals(&current->key, key))
    {
      if (prev != NULL)
      {
        prev->next = current->next;
      }
      else
      {
        m->table[index] = current->next;
      }
      current->key.empty(&current->key);
      current->val.empty(&current->val);
      free(current);
      m->size--;
      return true;
    }
    prev = current;
    current = current->next;
  }
  return false;
}

void freeMap(Map *m)
{
  for (int i = 0; i < m->tlen; ++i)
  {
    MapPair *current = m->table[i];
    while (current != NULL)
    {
      MapPair *next = current->next;
      current->key.empty(&current->key);
      current->val.empty(&current->val);
      free(current);

      current = next;
    }
  }
  free(m->table);
  free(m);
}
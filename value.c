/**
    @file value.c
    @author Samuel McConnell (semcconn)
    Implementation for the value component, with support for integer
    and string values.
  */

#include "value.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/** These are the numbers used when hashing the string */
#define HASING_NUMBERS \
  {                    \
    10, 6, 3, 11, 15   \
  }

//////////////////////////////////////////////////////////
// Integer implementation.

// print method for Integer.
static void printInteger(Value const *v)
{
  // Print the integer inside this value.
  printf("%d", v->ival);
}

// move method for Integer.
static void moveInteger(Value const *src, Value *dest)
{
  // We just need to copy the value.
  dest->ival = src->ival;

  dest->print = src->print;
  dest->move = src->move;
  dest->equals = src->equals;
  dest->hash = src->hash;
  dest->empty = src->empty;
}

// equals method for Integer.
static bool equalsInteger(Value const *v, Value const *other)
{
  return v->ival == other->ival;
}

// hash method for Integer.
static unsigned int hashInteger(Value const *v)
{
  // This will overflow negative values to large positive ones.
  return v->ival;
}

// Free memory used inside this integer Value.
static void emptyInteger(Value *v)
{
  // An int vaue doesn't need any additional memory.
}

// Parsing method for integer
int parseInteger(Value *v, char const *str)
{
  // Try to parse an integer from str.
  int val, len;
  if (sscanf(str, "%d%n", &val, &len) != 1)
    return 0;

  // Fill in all the fields of v for an integer type of value.
  v->print = printInteger;
  v->move = moveInteger;
  v->equals = equalsInteger;
  v->hash = hashInteger;
  v->empty = emptyInteger;
  v->ival = val;

  // Return how much of str we parsed.
  return len;
}

// Print method for String.
static void printString(Value const *v)
{
  printf("\"%s\"", (char *)v->vptr);
}

// move method for Strings.
static void moveString(Value const *src, Value *dest)
{

  dest->vptr = src->vptr;
  dest->print = src->print;
  dest->move = src->move;
  dest->equals = src->equals;
  dest->hash = src->hash;
  dest->empty = src->empty;
}

// equals method for String.
static bool equalsString(Value const *v, Value const *other)
{
  return strcmp((char *)v->vptr, (char *)other->vptr) == 0;
}

static unsigned int hashString(Value const *v)
{
  unsigned int hash = 0;
  char const *str = (char *)v->vptr;
  int hasingNumbers[] = HASING_NUMBERS;
  while (*str != '\0')
  {
    hash += *str;
    hash += (hash << hasingNumbers[0]);
    hash ^= (hash >> hasingNumbers[1]);
    str++;
  }
  hash += (hash << hasingNumbers[2]);
  hash ^= (hash >> hasingNumbers[3]);
  hash += (hash << hasingNumbers[4]);
  return hash;
}

// Free memory used inside this String Value.
static void emptyString(Value *v)
{
  free(v->vptr);
}

// Parsing method for String.
int parseString(Value *v, char const *str)
{
  int totalEaten = 0;

  if (*str != '\"')
  {
    return 0;
  }

  str++;
  totalEaten++;
  char *buffer = malloc(strlen(str) + 1);
  char *writePtr = buffer;

  while (*str)
  {
    if (*str == '\"')
    {
      str++;
      totalEaten++;
      break;
    }
    else if (*str == '\\' && *(str + 1))
    {
      str++;
      totalEaten++;
      switch (*str)
      {
      case 'n':
        *writePtr++ = '\n';
        break;
      case 't':
        *writePtr++ = '\t';
        break;
      case '\"':
        *writePtr++ = '\"';
        break;
      case '\\':
        *writePtr++ = '\\';
        break;
      default:
        *writePtr++ = *str;
      }
    }
    else
    {
      *writePtr++ = *str;
    }
    str++;
    totalEaten++;
  }

  *writePtr = '\0';

  v->print = printString;
  v->move = moveString;
  v->equals = equalsString;
  v->hash = hashString;
  v->empty = emptyString;
  v->vptr = buffer;

  return totalEaten;
}
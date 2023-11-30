/**
    @file driver.c
    @author Samuel McConnell (semcconn)
    Implementation for the map component, a hash map.
  */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "value.h"
#include "map.h"
#include "input.h"

/** The inital size of the map */
#define INITIAL_MAP_SIZE 10
/** The max size of a given line to store values */
#define MAX_LINE_LENGTH 256
/** An array of the possible number of parameters */
#define PARAM_NUMBERS \
  {                   \
    1, 2, 3           \
  }

/**
 * This is a helper method to check if the string or integer is able to be parsed.
 * @param value as a pointer to the value that is being checked for parse ability.
 * @return true if the string is able to be parsed, false otherwise
 */
static bool checkParse(char *value)
{
  Value val;
  char *quote = strchr(value, '\"');
  if (quote != NULL)
  {
    if (parseString(&val, value) == 0)
    {
      return false;
    };
  }
  else
  {
    if (parseInteger(&val, value) == 0)
    {
      return false;
    };
  }
  val.empty(&val);
  return true;
}

/**
 * This is a helper method to parse a string into a string or integer.
 * @param value as a pointer to the value that is being parsed
 * @return the parsed string as a Value
 */
static Value parseValue(char *value)
{
  Value val;
  char *quote = strchr(value, '\"');
  if (quote != NULL)
  {
    parseString(&val, value);
  }
  else
  {
    parseInteger(&val, value);
  }
  return val;
}

/**
 * The main function of the program. Calls all the needed functions to make
 * the program function approprietly.
 * @return EXIT_SUCCESS if the program was ran correctly.
 */
int main()
{
  int paramNumbers[] = PARAM_NUMBERS;
  Map *map = makeMap(INITIAL_MAP_SIZE);
  char *input;
  while (1)
  {
    printf("cmd> ");
    input = readLine(stdin);
    if (input == NULL)
    {
      break;
    }
    printf("%s\n", input);
    char cmd[MAX_LINE_LENGTH];
    char param1[MAX_LINE_LENGTH];
    char param2[MAX_LINE_LENGTH];
    char extra[MAX_LINE_LENGTH];
    int result = sscanf(input, "%s \"%[^\"]\" \"%[^\"]\" \"%[^\"]\"", cmd, param1, param2, extra);

    if ((strcmp(cmd, "remove") == 0 || strcmp(cmd, "get") == 0) && result == paramNumbers[1])
    {
      char *newParam1 = (char *)malloc(strlen(param1) + paramNumbers[2]);
      newParam1[0] = '"';
      for (size_t i = 0; i < strlen(param1); i++)
      {
        newParam1[i + 1] = param1[i];
      }
      newParam1[strlen(param1) + paramNumbers[0]] = '"';
      newParam1[strlen(param1) + paramNumbers[1]] = '\0';
      strcpy(param1, newParam1);
      free(newParam1);
    }
    else if (result != 3)
    {
      result = sscanf(input, "%s %s %s %s", cmd, param1, param2, extra);
    }
    else
    {
      char *newParam1 = (char *)malloc(strlen(param1) + paramNumbers[2]);
      newParam1[0] = '"';
      for (size_t i = 0; i < strlen(param1); i++)
      {
        newParam1[i + 1] = param1[i];
      }
      newParam1[strlen(param1) + paramNumbers[0]] = '"';
      newParam1[strlen(param1) + paramNumbers[1]] = '\0';
      strcpy(param1, newParam1);

      char *newParam2 = (char *)malloc(strlen(param2) + paramNumbers[2]);
      newParam2[0] = '"';
      for (size_t i = 0; i < strlen(param2); i++)
      {
        newParam2[i + 1] = param2[i];
      }
      newParam2[strlen(param2) + paramNumbers[0]] = '"';
      newParam2[strlen(param2) + paramNumbers[1]] = '\0';
      strcpy(param2, newParam2);
      free(newParam1);
      free(newParam2);
    }
    free(input);
    if (strcmp(cmd, "quit") == 0 && result == paramNumbers[0])
    {
      break;
    }
    else if (strcmp(cmd, "size") == 0 && result == paramNumbers[0])
    {
      printf("%d\n", mapSize(map));
    }
    else if (strcmp(cmd, "set") == 0 && result == paramNumbers[2])
    {
      if (checkParse(param1) && checkParse(param2))
      {
        Value key = parseValue(param1);
        Value value = parseValue(param2);
        mapSet(map, &key, &value);
      }
      else
      {
        printf("Invalid command\n");
      }
    }
    else if (strcmp(cmd, "get") == 0 && result == paramNumbers[1])
    {
      if (checkParse(param1))
      {
        Value key = parseValue(param1);
        Value *val = mapGet(map, &key);
        key.empty(&key);
        if (!val)
        {
          printf("Undefined\n");
        }
        else
        {
          val->print(val);
          printf("\n");
        }
      }
      else
      {
        printf("Invalid command\n");
      }
    }
    else if (strcmp(cmd, "remove") == 0 && result == paramNumbers[1])
    {
      if (checkParse(param1))
      {
        Value key = parseValue(param1);
        if (!mapRemove(map, &key))
        {
          printf("Not in map\n");
        }
        key.empty(&key);
      }
      else
      {
        printf("Invalid command\n");
      }
    }
    else
    {
      printf("Invalid command\n");
    }

    printf("\n");
  }
  freeMap(map);
  return EXIT_SUCCESS;
}
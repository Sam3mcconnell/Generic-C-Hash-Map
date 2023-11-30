/**
    @file value.h
    @author Samuel McConnell (semcconn)
    Header for the value component, representing either an integer or
    string value.
 */

#ifndef VALUE_H
#define VALUE_H

#include <stdbool.h>

/** Map struct ValueStruct to the shorter name, Value. */
typedef struct ValueStruct Value;

/** Abstract type used to represent an arbitrary value. All Values
    support four basic operations. */
struct ValueStruct
{
    /** Pointer to a function that prints this value to the terminal.
        @param v Pointer to the value object to print. */
    void (*print)(Value const *v);

    /** Pointer to a function that moves the representation of a value
        from v to dest.  The dest value must be empty before this is called
        and the v value will be empty afterward.
        @param v pointer to the value being moved (the source).
        @param dest pointer to the empty value it's moving into. */
    void (*move)(Value const *src, Value *dest);

    /** Compare the two given Value values, returning true
        if they are equivalent.
        @param a Pointer to the left-hand value to compare (the one
        containing this function)
        @param b Poitner to the right-hand value to compare.
        @return True if the values are equal. */
    bool (*equals)(Value const *v, Value const *other);

    /** Compute a hash function for this value.
        @param v Pointer to the inststance this funciton is called for.
        @return Hash value for this instance */
    unsigned int (*hash)(Value const *v);

    /** Free any memory allocated for this Value instance.  This only frees
        the memory allocated by this instance, no the memory for the Value
        object itself.  The owner is responsible for freeing that, since it may
        be part of a larger struct.
        @param v Pointer to the value to be emptied. */
    void (*empty)(Value *v);

    /** Anonymous union representation of the value stored inside this
        value, stored either as an int or as a pointer. */
    union
    {
        /** If this value is an int, we can store it right in the struct. */
        int ival;

        /** If this value is larger, we store it elsewhere in memory and just
            store a generic pointer to it here. */
        void *vptr;
    };
};

/** Parse in integer value from the given string.  If successful, initialize the given
    Value to contain the integer.
    @param v Pointer to a value instance that will hold the parsed integer.
    @param str String from which to parse the integer value.
    @return Number of characters consumed while parsing the integer, or zero if unsuccessful.
*/
int parseInteger(Value *v, char const *str);

/** Parse in string value from the given string.  If successful, initialize the given
    Value to contain the string.
    @param v Pointer to a value instance that will hold the parsed string.
    @param str String from which to parse the string value.
    @return Number of characters consumed while parsing the string, or zero if unsuccessful.
*/
int parseString(Value *v, char const *str);

#endif

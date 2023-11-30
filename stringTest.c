// Simple test program for values containing a string.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "value.h"

int main()
{
  // Try out the parse function for a few string values.
  int n;

  Value s1, s2, s3, s4, s5, s6;
  n = parseString( &s1, "\"abc\"" );
  // Should have read five characters.
  assert( n == 5 );

  n = parseString( &s2, "\"abc\" " );
  // Should have read five characters.
  assert( n == 5 );

  n = parseString( &s3, "  \"xyz\"  " );
  // Should have read seven characters.
  assert( n == 7 );
  
  // The first two string values should be equal.
  assert( s1.equals( &s1, &s2 ) );
  
  // Should also work the other way around.
  assert( s2.equals( &s2, &s1 ) );
  
  // The third object should be different.
  assert( ! s1.equals( &s1, &s3 ) );
  assert( ! s2.equals( &s2, &s3 ) );
  
  // Try a longer string.
  n = parseString( &s4, "\"ABCDEFGHIJKLMNOPQRSTUVWXYZ\"" );
  assert( n == 28 );

  // Some examples from the wikipedia page for the Jenkins hash function.
  n = parseString( &s5, "\"a\"" );
  assert( n == 3 );

  n = parseString( &s6, "\"The quick brown fox jumps over the lazy dog\"" );
  assert( n == 45 );

  // Check the hash values for these objects.
  assert( s1.hash( &s1 ) == 0xED131F5B );
  assert( s2.hash( &s2 ) == 0xED131F5B );
  assert( s3.hash( &s3 ) == 0x418B8F9E );
  assert( s4.hash( &s4 ) == 0x17D780E5 );
  
  // Check against the expected hashes from the wikipedia page.
  assert( s5.hash( &s5 ) == 0xCA2E9442 );
  assert( s6.hash( &s6 ) == 0x519E91F5 );

  // Get all the string objects to print themselves (we can't test this
  // with assert)
  s1.print( &s1 );
  printf( "\n" );
  s2.print( &s2 );
  printf( "\n" );
  s3.print( &s3 );
  printf( "\n" );
  s4.print( &s4 );
  printf( "\n" );
  s5.print( &s5 );
  printf( "\n" );
  s6.print( &s6 );
  printf( "\n" );
  
  // Free memory in all he string values.
  s1.empty( &s1 );
  s2.empty( &s2 );
  s3.empty( &s3 );
  s4.empty( &s4 );
  s5.empty( &s5 );
  s6.empty( &s6 );

  return EXIT_SUCCESS;
}

#include <stdio.h>

int main( int argc, char* argv[] ) { 
  int rows = 0;
  printf("Enter number of rows: ");
  scanf("%d", &rows);
  
  for( int i = 0; i < rows*3; i ++ ) {
    // Top or bottom rows
    if ( i == 0 || i == (rows*3)-1 ) {
      printf("   ");
      for( int j = 0; j < rows; j++ ) {
        printf(" ");
      }
      for( int k = 0; k < rows; k++ ) {
        printf("* ");
      }
      printf("\n");
      // Long sides
    } else if ( i >= rows && i < 2*rows) {
      printf("*   ");
      for( int k = 0; k < rows*2; k++ ) {
        printf("  ");
      }
      printf("*");
      printf("\n");
      //top slanted sides
    } else if ( i > 0 && i < rows ) {
      for ( int j = 1; j < rows-i; j++ ) {
        printf("  ");
      }
      printf("* ");
      for( int j = 0; j < (rows + 2 * (i-1)); j++ ){
        printf("  ");
      }
      printf("*\n");
      // bottom slanted sides
    } else {
      for ( int j = 0; j < ( rows * ( 2 ) + 2 ) - i; j++ ) {
        printf("  ");
      } 
      printf("* ");
    }
  }
}

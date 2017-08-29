#include <cstdio>
#include <cassert>
#include <cmath>

#define MAX_FILE_NAME_LENG 1024

#define EPS 1e-6

int main( int argc, char** argv ) {

  if ( argc < 4 ) {
    fprintf(stdout, "insufficient number of command line args\n");
    return 1;
  }

  char sInFile[MAX_FILE_NAME_LENG];
  char sDiffFile[MAX_FILE_NAME_LENG];
  char sOutFile[MAX_FILE_NAME_LENG];

  FILE *fpDiff = fopen(argv[4], "r");
  if ( !fpDiff ) {
    fprintf(stdout, "failed to open diff %s\n", argv[4]);
    return 1;
  }

  FILE *fpOut = fopen(argv[6], "r");
  if ( !fpOut ) {
    fprintf(stdout, "failed to open out %s\n", argv[6]);
    fclose( fpDiff );
    return 1;
  }

  double diff;
  fscanf(fpDiff, "%lf", &diff);
  fclose(fpDiff);

  double ans;
  fscanf(fpOut, "%lf", &ans);
  fclose(fpOut);

  assert( fabs( diff - ans ) <= EPS );

  return 0;
}

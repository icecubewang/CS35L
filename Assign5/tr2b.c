#include <stdio.h>
#include <stdlib.h>
#define SIZE 500

void checkInputError() {
  if (ferror(stdin)) {
    fprintf(stderr, "Error: Input failure.\n");
    exit(1);
  }
}

//  ./tr2b abcd wxyz < bigfile.txt
//  from is argv[1]
//  to is argv[2]
//  getChar() to read from bigfile.txt
int main(int argc, char *argv[]) {

  //read 'from' and 'to'
  char from[SIZE];
  char* a1;
  int trace1 = 0;
  for (a1 = argv[1]; *a1 != '\0'; a1++) {
    from[trace1] = *a1;
    trace1 += 1;
  }
  char to[SIZE];
  char* a2;
  int trace2 = 0;
  for (a2 = argv[2]; *a2 != '\0'; a2++) {
    to[trace2] = *a2;
    trace2 += 1;
  }
  if (trace1 != trace2) {
    printf("Error: from and to of different length.\n");
    exit(0);
  }

  int i;
  int k;
  char c;
  int fileSize = SIZE;
  for (i = 0; (c = getchar()) != EOF; i++) {
    checkInputError();

    for (k = 0; k != trace1; k++) {
      if (c == from[k])
	c = to[k];
    }

    if (c != EOF)
      putchar(c);
  }
}

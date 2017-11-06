#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 500
#define nbytes 1

void checkReadError(int bytes) {
  if (bytes < 0) {
    fprintf(stderr, "Error: Read failure.\n");
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
  char buf;
  ssize_t bytes_read = 1;
  int fd;
  int i;
  int fileSize = SIZE;
  for (i = 0; bytes_read != 0; i++) {
    fd = 0;
    bytes_read = read(fd, &buf, nbytes);
    int k;
    for (k = 0; k < trace1; k++) {
      if (buf == from[k]) 
	buf = to[k];
    }
    checkReadError(bytes_read);
    fd = 1;
    if (bytes_read != 0)
      write(fd, &buf, nbytes);
  }
}

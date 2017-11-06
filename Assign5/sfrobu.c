#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#define SIZE 500
#define BYTES 1

void checkMemAllocError(char* cp) {
  if (cp == NULL) {
    fprintf(stderr, "Error: Mem Alloc Failure.\n");
    exit(1);
  }
}

char decodebyte(char obj) {
  return (obj ^ 42);
}

int frobcmp (char const *a, char const *b) {
  while (*a != ' ' && *b != ' ') {
    char da = decodebyte(*a);
    char db = decodebyte(*b);
    if (da > db) return 1;
    else if (da < db) return -1;
    else {a++; b++;}
  }
  if (*a == ' ' && *b == ' ') return 0;
  else if (*a == ' ') return -1;
  else return 1;
}

int cmp(const void *a, const void *b) {
  return frobcmp(*(char const**)a, *(char const**)b);
}

int frobcmp_f (char const *a, char const *b) {
  while (*a != ' ' && *b != ' ') {
    char da = decodebyte(*a);
    char db = decodebyte(*b);
    da = (char) toupper((unsigned) da);
    db = (char) toupper((unsigned) db);
    if (da > db) return 1;
    else if (da < db) return -1;
    else {a++; b++;}
  }
  if (*a == ' ' && *b == ' ') return 0;
  else if (*a == ' ') return -1;
  else return 1;
}

int cmp_f(const void *a, const void *b) {
  return frobcmp_f(*(char const**)a, *(char const**)b);
}

int main(int argc, char *argv[]) {
  //breakdown arguments
  _Bool foption = false;
  struct stat sb;
  _Bool isRegularFile;
  int fileSize;
  char* input;
  char* f = "-f";
  if ((char)getopt(argc, argv, "f") == 'f') {
      foption = true;
  }
    int fd = 0;
    if (fstat(fd, &sb)) {
    printf("\nfstat error: [%s}\n", strerror(errno));
    exit(1);
  }
  if (S_ISREG(sb.st_mode))
    isRegularFile = true;
  else isRegularFile = false;
  
  //allocate memory according to reg/non-reg file
  int arrSize;
  if (isRegularFile) {
    fileSize = sb.st_size;
    input = (char*) malloc(fileSize);
    arrSize = fileSize;
  }
  else {
    input = (char*) malloc(SIZE);
    arrSize = SIZE;
  }
  checkMemAllocError(input);
  
  //read input
  int ithChar;
  int bytes_read;
  int wordCount = 0;
  char c;
  for (ithChar = 0; (bytes_read = read(fd, &c, BYTES)) != 0; ithChar++) {
    if (bytes_read != 1) break;
    //reallocate if full
    if (ithChar == arrSize) {
      arrSize *= 2;
      char* reallocate = (char*) realloc(input, arrSize);
      checkMemAllocError(reallocate);
      input = reallocate;
    }
    if (c == '\n' || c == ' ') {
      c = ' ';
      if (ithChar != 0 && input[ithChar - 1] != ' ') {
	input[ithChar] = c;
	wordCount += 1;
      }
    }
    else input[ithChar] = c;
  }

  //append a space to the end of input if there's none
  if (input[ithChar-1] != ' ') {
    if (ithChar == arrSize) {
      arrSize *= 2;
      char* reallocate = (char*) realloc(input, arrSize);
      checkMemAllocError(reallocate);
      input = reallocate;
    }
    input[ithChar] = ' ';
    wordCount += 1;
  }
  
  //store input in array of pointers to words
  char** words = (char**) malloc(sizeof(char*) * wordCount);
  if (words == NULL) {
    fprintf(stderr, "Error: Mem Alloc Failure.\n");
    exit(1);
  }
  char* iter = input;
  int ithWord;
  for (ithWord = 0; ithWord < wordCount; ithWord++) {
    words[ithWord] = iter;
    if (ithWord == (wordCount - 1)) break;
    while (*iter != ' ') {
      iter++;
    }
    iter++;
  }

  //sorting
  if (foption)
    qsort(words, wordCount, sizeof(char*), cmp_f);
  else
    qsort(words, wordCount, sizeof(char*), cmp);

  //write
  fd = 1;
  int bytes_write;
  char* cp;
  for (ithWord = 0; ithWord < wordCount; ithWord++) {
    cp = words[ithWord];
    while (*cp != ' ') {
      write(fd, cp, BYTES);
      cp += 1;
    }
    write(fd, cp, BYTES);
  }
  //free memory
  free(input);
  free(words);
}

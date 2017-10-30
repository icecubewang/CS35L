#include <stdio.h>
#include <stdlib.h>

//This fuction takes two arguments a and b
//uses byte-by-byte lexicographic conparison
//return an int result:
//negative when a < b
//zero when a == b
//positive shen a > b

char decodebyte(char obj);

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

/**
 **This function takes one char;
 **return its decoded version;
 **/

char decodebyte(char obj) {
  return (obj^42);//00101010 in decimal is 42
}

/**
 **Check for read input error
 **/

void checkInputError() {
  if (ferror(stdin)) {
    fprintf(stderr, "Error: Input failure.\n");
    exit(1);
  }
}

int main(void) {

  /*allocate storage to hold input and check for mem alocation failure*/
  size_t init_memory = sizeof(char);
  char* input1 = (char*) malloc(sizeof(char) * init_memory);
  if (input1 == NULL) {
    fprintf(stderr, "Error: Memory allocation failure.\n");
    exit(1);
  }

  /*read lines and store in array of pointers to word*/
  char c1, c2;
  char* reallocate;
  char** arrayOfWords;
  int ithChar;
  int ithWord = 0;
  c1 = getchar();
  //    printf("%c", c1);
  // printf("test\n");
  checkInputError();

  for (ithChar = 0; c1 != EOF; ithChar++) {
    //reallocate memory if reaches the end
    if (ithChar == init_memory) {
      //      fprintf(stderr, "mem alloc\n");
      init_memory *= 2;
      reallocate = (char*) realloc(input1, sizeof(char) * init_memory);
      if (reallocate == NULL) {
	fprintf(stderr, "Error: Memory reallocation failure.\n");
	exit(1);
      }
      else {
	input1 = reallocate;
      }
    }
    
    //avoid newlines at the end of the word
    if (c1 == '\n') {
      c1 = getchar();
      checkInputError();
      continue;
    }

    //count number of words
    if (c1 == ' ') ithWord++;

    //store char in the array 
    input1[ithChar] = c1;
    c1 = getchar();
    //    printf("%c", c1);
    checkInputError();
  }
  
  //  printf("Check: %s\n", input1);

  //append a space to the end of input1 if there's none
  if (input1[ithChar] != ' ') {
    input1[ithChar] = ' ';
    ithWord++;
  }
  
  unsigned int noOfWords = sizeof(char*);
  arrayOfWords = (char**) malloc(noOfWords);
  if (arrayOfWords == NULL) {
    fprintf(stderr, "Error: Memory allocation failure.\n");
    exit(1);
  }

  char* iter = input1;

  int j;
  for (j = 0; j < ithWord; j++) {    
    if (j * sizeof(char*) == noOfWords) {
      noOfWords *= 2;
      char** reallocate2 = (char**) realloc(arrayOfWords, noOfWords);
      //  fprintf(stderr, "word alloc\n");
      if (reallocate2 == NULL) {
	fprintf(stderr, "Error: Memory allocation failure.\n");
	exit(1);
      }
      else {
	arrayOfWords = reallocate2;
      }
    }
    
    arrayOfWords[j] = iter;
    if (j != ithWord-1) {
      while (*iter != ' ') iter++;
      iter++;//move to the start of the next word
    }
  }
  // int p;
  // for (p = 0; p < ithWord; p++)
  // fprintf(stderr, "%s\n", arrayOfWords[p]);
  
  //sorting
  qsort(arrayOfWords, ithWord, sizeof(char*), cmp);

  //output
  int k;
  for (k = 0; k < ithWord; k++) {
    char* cp = arrayOfWords[k];
    if (*cp == ' ') continue;
    while(*cp != ' ') {
      putchar(*cp);
      //      printf("%c", *cp);
      (cp)++;
    }
    putchar(' ');
  }
  
  if (ferror(stdout)) {
    fprintf(stderr, "Error: Output failure.\n");
    exit(1);
  }
  
  free(input1);
  free(arrayOfWords);
}

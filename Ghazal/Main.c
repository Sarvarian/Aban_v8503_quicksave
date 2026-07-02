#include <stdio.h>
#include <stdlib.h>

#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define NORM  "\033[0m"

int main(int argc, char** argv) {
  int exit_code = 0;

  if (argc != 2) {
    printf(GREEN"Test" NORM" " RED"Error" NORM" Code 0" /* No argument, no absolute path to aban executable. */ NORM);
    printf("\n");
    exit_code = 1;
    goto exit;
  }

  

  printf("    %d", argc);
  printf("    %s", argv[0]);
  printf("    %s", argv[1]);
  printf("\n");

exit:
  return exit_code;
}

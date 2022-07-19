// #include <iostream>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int o;
  const char *optstring = "abc:";
  while ((o = getopt(argc, argv, optstring)) != -1) {
    switch (o) {
    case 'a':
      printf("opt is a, optarg is %s\n", optarg);  // cout输出空指针会崩溃
      break;
    case 'b':
      printf("opt is b, optarg is %s\n", optarg);
      break;
    case 'c':
      printf("opt is c, optarg is %s\n", optarg);
      break;
    default:
      printf("invalid arguments\n");
      break;
    }
  }
  return 0;
}

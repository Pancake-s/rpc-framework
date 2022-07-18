#include <iostream>
#include <unistd.h>

int main(int argc, char **argv) {
  int o;
  const char *optstring = "abc:";
  while ((o = getopt(argc, argv, optstring) != -1)) {
    switch (o) {
    case 'a':
      std::cout << "opt is a, optarg is: " << optarg << std::endl;
        break;
    case 'b':
      std::cout << "opt is a, optarg is: " << optarg << std::endl;
        break;
    case 'c':
      std::cout << "opt is a, optarg is: " << optarg << std::endl;
        break;
    default:
        break;
    }
  }
}
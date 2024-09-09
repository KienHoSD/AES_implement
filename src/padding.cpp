#include "padding.h"
#include <iostream>

// check padding of a block
// input: input block (in bytes)
// size: size of input block (in bytes)
bool checkPadding(const unsigned char *input, int &size, int block_size){
  int padding = input[size - 1] & 0xff;
  if(padding > block_size){
    std::cerr << "Error: Invalid padding" << '\n';
    return 0;
  }
  for(int i = 0; i < padding; i++){
    if((input[size - 1] & 0xff) != padding){
      std::cerr << "Error: Invalid padding" << '\n';
      return 0;
    }
  }
  return 1;
}

bool pad(unsigned char *input, int &size, int block_size){
  int padding = block_size - (size % block_size);
  memset(input + size, padding, padding);
  size += padding;
  return 1;
}

bool unpad(unsigned char *input, int &size, int block_size){
  int padding = input[size - 1] & 0xff;
  if(checkPadding(input, size, block_size) == false){
    return 0;
  }
  size -= padding;
  memset(input + size, 0, padding);
  return 1;
}
#include "helper.h"

void XorUint32(uint32_t *input1, uint32_t *input2, uint32_t *output, int size){
  for(int i = 0; i < size; i++){
    output[i] = input1[i] ^ input2[i];
  }
}

// Print hex values of an array
// input: input array
// size: size of input array
template <typename T>
void printHex(T *input, int size){
  for(int i = 0; i < size; i++){
    std::cout << std::hex << input[i] << " ";
  }
  std::cout << std::endl;
}

// Explicit instantiation of printHex
template void printHex<uint32_t>(uint32_t *input, int size);
template void printHex<unsigned char>(unsigned char *input, int size);


// Convert a hex string to uint32_t array
// hex: input hex string
// output: output uint32_t array
// size: size of output array (in uint32_t)
void converHexStringToUint32(const char *hex, uint32_t *output, int size){
  for(int i = 0; i < size; i++){
    sscanf(hex + i * 8, "%8x", &output[i]);
  }
  // printHex(output, size);
}

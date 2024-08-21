#ifndef __HELPER_H
#define __HELPER_H

#include <iostream>
#include <cstdint>

// Xor two uint32_t arrays
// input1: first input array
// input2: second input array
// output: output array
// size: size of input arrays
template<typename T>
void Xor(T *input1, T *input2, T *output, int size);

// Print hex values of an array
// input: input array
// size: size of input array
template <typename T>
void printHex(T *input, int size);

// Convert a hex string to uint32_t array
// hex: input hex string
// output: output uint32_t array
// size: size of output array (in uint32_t)
void converHexStringToUint32(const char *hex, uint32_t *output, int size);

// Convert a hex string to unsigned char array
// hex: input hex string
// output: output unsigned char array
// size: size of output array (in unsigned char)
void convertHexToUChar(const char *hex, unsigned char *output, int size);

// unsigned char to big endian uint32_t
// input: input unsigned char array
// output: output uint32_t array
// size: size of input array
void ucharToUint32(unsigned char *input, uint32_t *output, int size);

void Uint32ToUchar(uint32_t *input, unsigned char *output, int size);

#endif
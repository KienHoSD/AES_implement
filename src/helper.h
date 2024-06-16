#ifndef __HELPER_H
#define __HELPER_H

#include <iostream>
#include <cstdint>

// Xor two uint32_t arrays
// input1: first input array
// input2: second input array
// output: output array
// size: size of input arrays
void XorUint32(uint32_t *input1, uint32_t *input2, uint32_t *output, int size);

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

#endif
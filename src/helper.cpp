#include "helper.h"

// Print hex values of an array
// input: input array
// size: size of input array
template <typename T>
void printHex(T *input, int size)
{
  for (int i = 0; i < size; i++)
  {
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
void converHexStringToUint32(const char *hex, uint32_t *output, int size)
{
  for (int i = 0; i < size; i++)
  {
    sscanf(hex + i * 8, "%8x", &output[i]);
  }
}

void convertHexToUChar(const char *hexString, unsigned char *hexBuffer, int size)
{
  for (int i = 0; i < size; i++)
  {
    // Convert each pair of hex characters to a single byte
    sscanf(hexString + 2 * i, "%2hhx", &hexBuffer[i]);
  }
}

// unsigned char to big endian uint32_t
// input: input unsigned char array
// output: output uint32_t array
// size: size of input array
void ucharToUint32(unsigned char *input, uint32_t *output, int size)
{
  for (int i = 0; i < size; i++)
  {
    output[i] = (input[i * 4] << 24) | (input[i * 4 + 1] << 16) | (input[i * 4 + 2] << 8) | input[i * 4 + 3];
  }
}

void Uint32ToUchar(uint32_t *input, unsigned char *output, int size)
{
  for (int i = 0; i < size; i++)
  {
    output[i * 4] = (input[i] >> 24) & 0xff;
    output[i * 4 + 1] = (input[i] >> 16) & 0xff;
    output[i * 4 + 2] = (input[i] >> 8) & 0xff;
    output[i * 4 + 3] = input[i] & 0xff;
  }
}
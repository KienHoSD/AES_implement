#ifndef AES_H
#define AES_H

#include <cstdint>
#include "helper.h"
#include "padding.h"
#include <iostream>
#include <cstring>

class AES
{
public:
  AES(const char *key);
  ~AES();
  bool encrypt(unsigned char *input, unsigned char *output, int bufsize);
  bool decrypt(unsigned char *input, unsigned char *output, int bufsize);
  bool encryptFile(const char *filein, const char *fileout, int bufsize);
  bool decryptFile(const char *filein, const char *fileout, int bufsize);

protected:
  static const unsigned char Sbox[256];
  static const unsigned char invSbox[256];
  static const unsigned char Rcon[11];
  static const unsigned char mul2[256];
  static const unsigned char mul3[256];
  static const unsigned char mul9[256];
  static const unsigned char mul11[256];
  static const unsigned char mul13[256];
  static const unsigned char mul14[256];

  bool encryptBlock(uint32_t *input, uint32_t *output);
  bool decryptBlock(uint32_t *input, uint32_t *output);
  void Subbytes(uint32_t *input);
  void invSubbytes(uint32_t *input);
  void Shiftrows(uint32_t *input);
  void invShiftrows(uint32_t *input);
  void Mixcolumns(uint32_t *input);
  void invMixcolumns(uint32_t *input);
  void AddKey(uint32_t *input, int round);
  void KeyExpansion();
  void Transpose(uint32_t *input);

  uint32_t *expkey = nullptr;
  int NumRounds;
};

#endif
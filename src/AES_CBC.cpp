#include "AES_CBC.h"

using std::cout;
using std::endl;

AES_CBC::AES_CBC(const char *key, const char *iv) : AES(key)
{
  IV = new uint32_t[4];
  tempIV = new uint32_t[4];

  if (iv == nullptr)
  {
    cout << "Warning: IV is not given or declared" << endl;
  }
  else
  {
    converHexStringToUint32(iv, IV, 4);
  }
}

AES_CBC::~AES_CBC()
{
  if (IV != nullptr)
  {
    delete[] IV;
    IV = nullptr;
  }
  if (tempIV != nullptr)
  {
    delete[] tempIV;
    tempIV = nullptr;
  }
}

bool AES_CBC::updateIV(const char *iv)
{
  // if IV is not given or declared
  if (iv == nullptr && IV == nullptr)
  {
    // print warning
    cout << "Warning: IV is not given or declared" << endl;
    return false;
  }

  // if IV is given and not declared
  else if (iv != nullptr && IV == nullptr)
  {
    IV = new uint32_t[4];
    memcpy(IV, iv, 16);
  }

  // if IV is given but declared
  else if (iv != nullptr && IV != nullptr)
  {
    memcpy(IV, iv, 16);
  }

  return true;
}

template <typename T>
bool AES_CBC::encrypt(T *input, T *output, const char *iv, int bufsize)
{
  // bufsize is in bytes, convert to 32-bit words
  bufsize /= 4;

  if (bufsize % 4 != 0 || bufsize == 0)
  {
    cout << "Error: bufsize must be a multiple of 16 bytes and not zero" << endl;
    return false;
  }

  updateIV(iv);

  // set tempIV to IV
  memcpy(tempIV, IV, 16);

  for (int i = 0; i < bufsize; i += 4)
  {
    XorUint32(tempIV, (uint32_t *)(input) + i, (uint32_t *)(output) + i, 4);

    AES::encrypt((uint32_t *)(output) + i, (uint32_t *)(output) + i, 16);

    // set tempIV to output (current  block ciphertext)
    memcpy(tempIV, (uint32_t *)(output) + i, 16);

  }

  return true;
}

template <typename T>
bool AES_CBC::decrypt(T *input, T *output, const char *iv, int bufsize)
{
  // bufsize is in bytes, convert to 32-bit words
  bufsize /= 4;

  if (bufsize % 4 != 0 || bufsize == 0)
  {
    cout << "Error: bufsize must be a multiple of 16 bytes and not zero" << endl;
    return false;
  }
  updateIV(iv);

  // set tempIV to IV
  memcpy(tempIV, IV, 16);

  for (int i = 0; i < bufsize; i += 4)
  {
    AES::decrypt((uint32_t *)(input) + i, (uint32_t *)(output) + i, 16);

    XorUint32(tempIV, (uint32_t *)(output) + i, (uint32_t *)(output) + i, 4);

    // set tempIV to input (current block ciphertext)
    memcpy(tempIV, (uint32_t *)(input) + i, 16);
  }

  return true;
}

// Explicit instantiation for required types
template bool AES_CBC::encrypt<unsigned int>(unsigned int* input, unsigned int* output, const char *iv, int bufsize);
template bool AES_CBC::decrypt<unsigned char>(unsigned char* input, unsigned char* output, const char *iv, int bufsize);
template bool AES_CBC::decrypt<unsigned int>(unsigned int* input, unsigned int* output, const char *iv, int bufsize);
template bool AES_CBC::encrypt<unsigned char>(unsigned char* input, unsigned char* output, const char *iv, int bufsize);

bool AES_CBC::encryptFile(const char *filein, const char *fileout, const char *iv, int bufsize)
{
  updateIV(iv);

  FILE *fin = fopen(filein, "rb");
  FILE *fout = fopen(fileout, "wb");

  if (fin == nullptr)
  {
    cout << "Error: Cannot open input file" << endl;
    return 0;
  }

  if (fout == nullptr)
  {
    cout << "Error: Cannot open output file" << endl;
    return 0;
  }

  unsigned char *inbuf = new unsigned char[bufsize];
  unsigned char *outbuf = new unsigned char[bufsize];
  int buflen;

  while ((buflen = fread(inbuf, 1, bufsize, fin)) == bufsize)
  {
    encrypt(inbuf, outbuf, nullptr, buflen);
    fwrite(outbuf, 1, buflen, fout);
  }

  // buflen changed after padding
  pad(inbuf, buflen, 16);
  encrypt(inbuf, outbuf, nullptr, buflen);
  fwrite(outbuf, 1, buflen, fout);

  delete[] inbuf;
  inbuf = nullptr;
  delete[] outbuf;
  outbuf = nullptr;

  fclose(fin);
  fclose(fout);

  return true;
}

bool AES_CBC::decryptFile(const char *filein, const char *fileout, const char *iv, int bufsize)
{
  updateIV(iv);

  FILE *fin = fopen(filein, "rb");
  FILE *fout = fopen(fileout, "wb");

  if (fin == nullptr)
  {
    cout << "Error: Cannot open input file" << endl;
    return 0;
  }

  if (fout == nullptr)
  {
    cout << "Error: Cannot open output file" << endl;
    return 0;
  }

  unsigned char *inbuf = new unsigned char[bufsize];
  unsigned char *outbuf = new unsigned char[bufsize];
  int buflen;

  while ((buflen = fread(inbuf, 1, bufsize, fin)) == bufsize)
  {
    decrypt(inbuf, outbuf, nullptr, buflen);
    fwrite(outbuf, 1, buflen, fout);
  }

  // deal with the last block
  decrypt(inbuf, outbuf, nullptr, buflen);
  // unpad the last block
  unpad(outbuf, buflen, 16);
  fwrite(outbuf, 1, buflen, fout);

  delete[] inbuf;
  inbuf = nullptr;
  delete[] outbuf;
  outbuf = nullptr;

  fclose(fin);
  fclose(fout);

  return true;
}

// int main()
// {
//   AES_CBC aes("12345678901234561234567890123456", "12345678901234561234567890123456");
//   aes.encryptFile("input.txt", "input.enc", "12345678901234561234567890123456");
//   aes.decryptFile("input.enc", "output.txt", "12345678901234561234567890123456");
// }
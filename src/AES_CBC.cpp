#include "AES_CBC.h"

using std::cout;
using std::cerr;
using std::clog;
using std::endl;

AES_CBC::AES_CBC(const char *key, const char *iv) : AES(key)
{
  IV = new u_char[16];
  tempIV = new u_char[16];

  if (iv == nullptr)
  {
    clog << "Warning: IV is not given or declared" << endl;
  }
  else
  {
    convertHexToUChar(iv, IV, 16);
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
  if (iv == nullptr && IV == nullptr)
  {
    clog << "Warning: IV is not given or declared" << endl;
    return false;
  }

  else if (iv != nullptr && IV == nullptr)
  {
    IV = new u_char[16];
    memcpy(IV, iv, 16);
  }

  else if (iv != nullptr && IV != nullptr)
  {
    memcpy(IV, iv, 16);
  }
  return true;
}

bool AES_CBC::encrypt(unsigned char *input, unsigned char *output, const char *iv, int bufsize)

{
  if (bufsize % 16 != 0 || bufsize == 0)
  {
    cerr << "Error: Buffer size must be a multiple of 16" << endl;
    return false;
  }

  updateIV(iv);

  tempIV = new u_char[16];
  memcpy(tempIV, IV, 16);

  for (int i = 0; i < bufsize; i += 16)
  {
    Xor(tempIV, input + i, output + i, 16);
    AES::encrypt(output + i, output + i, 16);
    memcpy(tempIV, output + i, 16);
  }

  delete[] tempIV;
  tempIV = nullptr;

  return true;
}

bool AES_CBC::decrypt(unsigned char *input, unsigned char *output, const char *iv, int bufsize)
{
  if (bufsize % 16 != 0 || bufsize == 0)
  {
    cerr << "Error: Buffer size must be a multiple of 16 bytes" << endl;
    return false;
  }
  updateIV(iv);

  tempIV = new u_char[16];
  memcpy(tempIV, IV, 16);

  for (int i = 0; i < bufsize; i += 16)
  {
    AES::decrypt(input + i, output + i, 16);
    Xor(tempIV, output + i, output + i, 16);
    memcpy(tempIV, input + i, 16);
  }

  delete[] tempIV;
  tempIV = nullptr;

  return true;
}

bool AES_CBC::encryptFile(const char *filein, const char *fileout, const char *iv, int bufsize)
{
  updateIV(iv);

  FILE *fin = fopen(filein, "rb");
  FILE *fout = fopen(fileout, "wb");

  if (fin == nullptr)
  {
    cerr << "Error: Cannot open input file" << endl;
    return 0;
  }

  if (fout == nullptr)
  {
    cerr << "Error: Cannot open output file" << endl;
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

  if(!pad(inbuf, buflen, 16)){
    cerr << "Error: Padding failed" << endl; // this error should never happen
  }
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
    cerr << "Error: Cannot open input file" << endl;
    return 0;
  }

  if (fout == nullptr)
  {
    cerr << "Error: Cannot open output file" << endl;
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
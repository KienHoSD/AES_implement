#ifndef AES_CBC_H
#define AES_CBC_H

#include "AES.h"

class AES_CBC : AES {
public:
  AES_CBC(const char *key, const char *iv = nullptr);
  ~AES_CBC();
  bool encrypt(unsigned char *input, unsigned char *output, const char *iv = nullptr, int bufsize = 1024);
  bool encryptFile(const char *input, const char *output, const char *iv = nullptr, int bufsize = 1024);
  bool decrypt(unsigned char *input, unsigned char *output, const char *iv = nullptr, int bufsize = 1024);
  bool decryptFile(const char *input, const char *output, const char *iv = nullptr, int bufsize = 1024);
  bool updateIV(const char *iv = nullptr);
protected:
  u_char *IV = nullptr;
  u_char *tempIV = nullptr;
};

#endif
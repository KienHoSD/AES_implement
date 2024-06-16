#ifndef AES_CBC_H
#define AES_CBC_H

#include "AES.h"
#include "padding.h"


class AES_CBC : AES {
public:
  AES_CBC(const char *key, const char *iv = nullptr);
  ~AES_CBC();
  template <typename T>
  bool encrypt(T *input, T *output, const char *iv = nullptr, int bufsize = 1024);
  bool encryptFile(const char *input, const char *output, const char *iv = nullptr, int bufsize = 1024);
  template <typename T>
  bool decrypt(T *input, T *output, const char *iv = nullptr, int bufsize = 1024);
  bool decryptFile(const char *input, const char *output, const char *iv = nullptr, int bufsize = 1024);
  bool updateIV(const char *iv = nullptr);
protected:
  uint32_t *IV = nullptr;
  uint32_t *tempIV = nullptr;
};

#endif
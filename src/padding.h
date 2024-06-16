#ifndef _PADDING_H
#define _PADDING_H

#include <cstring>

bool checkPadding(const unsigned char *input, int &size, int block_size);
bool pad(unsigned char *input, int &size, int block_size);
bool unpad(unsigned char *input, int &size, int block_size);

#endif
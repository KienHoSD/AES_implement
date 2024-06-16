#include "../src/AES_CBC.h"

using namespace std;

int main(){
  AES_CBC aes("0123456789abcdefdeadbeefdeadbeef", "0123456789abcdefdeadbeefdeadbeef");
  unsigned char plain[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'a', 'b', 'c', 'd', 'e', 'f'};
  unsigned char *cipher = new unsigned char[16];
  unsigned char *decipher = new unsigned char[16];

  aes.encrypt(plain, cipher, nullptr, 16);
  aes.decrypt(cipher, decipher, nullptr, 16);
  for (int i = 0; i < 16; i++)
  {
    cout << (int)decipher[i] << " ";
  }
  cout << endl;
}
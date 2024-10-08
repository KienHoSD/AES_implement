#include "../src/AES_CBC.h"

using namespace std;

int main(){
  AES_CBC aes("0123456789abcdefdeadbeefdeadbeef", "64656164626565666465616462656564");
  unsigned char plain[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  unsigned char *cipher = new unsigned char[16];
  unsigned char *decipher = new unsigned char[16];

  aes.encrypt(plain, cipher, nullptr, 16);
  aes.decrypt(cipher, decipher, nullptr, 16);
  for (int i = 0; i < 16; i++)
  {
    cout << (char)decipher[i] << " ";
  }
  cout << endl;


  unsigned char plain2[] = "Hello, World!!!!!!!!!!!!!!!!!!!!";
  unsigned char *cipher2 = new unsigned char[32];
  unsigned char *decipher2 = new unsigned char[32];
  aes.encrypt(plain2, cipher2, nullptr, 32);
  aes.decrypt(cipher2, decipher2, nullptr, 32);
  for (int i = 0; i < 32; i++)
  {
    cout << decipher2[i];
  }
  cout << endl;

  cout << "Encrypting and decrypting file... ";
  aes.encryptFile("test/test.txt", "test/test.enc", nullptr, 1024);
  aes.decryptFile("test/test.enc", "test/test.dec", nullptr, 1024);  
  cout << "Done" << endl;

  return 0;
}
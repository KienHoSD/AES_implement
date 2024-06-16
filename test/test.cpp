#include "../src/AES_CBC.h"

using namespace std;

int main(){
  AES_CBC aes("0123456789abcdefdeadbeefdeadbeef");
  aes.encryptFile("input.txt", "input.enc", "0123456789abcdefdeadbeefdeadbeef");
  aes.decryptFile("input.enc", "output.txt", "0123456789abcdefdeadbeefdeadbeef");
}
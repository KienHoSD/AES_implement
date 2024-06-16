#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <ctime>
#include <cstdlib>
#include "../src/AES_CBC.h"

const unsigned int MICROSECONDS = 1000000;

unsigned long getMicroseconds()
{
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  return MICROSECONDS * tv.tv_sec + tv.tv_usec;
}

unsigned char *getRandomPlain(unsigned int length)
{
  unsigned char *plain = new unsigned char[length];
  for (unsigned int i = 0; i < length; i++)
  {
    plain[i] = rand() % 256;
  }
  return plain;
}

int main()
{
  const unsigned int MEGABYTE = 1024 * 1024;
  const unsigned int MIN_SIZE = 1024;         // 1 KB
  const unsigned int MAX_SIZE = 2 * MEGABYTE; // 2 MB
  const unsigned int NUM_TESTS = 10000;       // Number of different random sizes to test

  const char key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
  const char iv[] = "0123456789abcdefdeadbeefdeadbeef";

  std::ofstream results("benchmark_results.csv");
  results << "Size(Bytes),Time(Microseconds)\n";

  std::cout << "Start speedtest" << std::endl;
  srand(static_cast<unsigned int>(std::time(nullptr)));

  AES_CBC aes(key, iv);

  for (unsigned int test = 0; test < NUM_TESTS; ++test)
  {
    int size = MIN_SIZE + rand() % (MAX_SIZE - MIN_SIZE + 1);

    // add random padding to the plain text
    int padding = 16 - size % 16;
    size += padding;
    unsigned char *plain = getRandomPlain(size);
    unsigned char *out = new unsigned char[size];

    unsigned long start = getMicroseconds();
    aes.encrypt(plain, out, nullptr, size);
    unsigned long delta = getMicroseconds() - start;

    results << size << "," << delta << "\n";

    delete[] plain;
    delete[] out;
  }

  results.close();
  std::cout << "Benchmark completed." << std::endl;

  return 0;
}

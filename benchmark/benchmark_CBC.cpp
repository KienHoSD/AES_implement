#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <ctime>
#include <random> // For std::mt19937 and std::uniform_int_distribution
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
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 255); // Distribution for random byte values
  for (unsigned int i = 0; i < length; i++)
  {
    plain[i] = static_cast<unsigned char>(dis(gen));
  }
  return plain;
}

int genRandomInt(int min = 0, int max = 0xFFFFFFFF)
{
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}

int main()
{
  const unsigned int MEGABYTE = 1024 * 1024;
  const unsigned int MIN_SIZE = 1024;         // 1 KB
  const unsigned int MAX_SIZE = 2 * MEGABYTE; // 2 MB
  const unsigned int NUM_TESTS = 10000;       // Number of different random sizes to test

  const char key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
  const char iv[] = "0123456789abcdefdeadbeefdeadbeef";

#ifdef _WIN32
  std::ofstream results_encrypt("benchmark_results_enc_win.csv");
  std::ofstream results_decrypt("benchmark_results_dec_win.csv");
#else
  std::ofstream results_encrypt("benchmark_results_enc_linux.csv");
  std::ofstream results_decrypt("benchmark_results_dec_linux.csv");
#endif

  results_encrypt << "Size(Bytes),Time(Microseconds)\n";
  results_decrypt << "Size(Bytes),Time(Microseconds)\n";

  std::cout << "Start speedtest" << std::endl;

  AES_CBC aes(key, iv);

  for (unsigned int test = 0; test < NUM_TESTS; ++test)
  {
    int size = genRandomInt(MIN_SIZE, MAX_SIZE);

    // add random padding to the plain text
    int padding = 16 - size % 16;
    size += padding;
    unsigned char *plain = getRandomPlain(size);
    unsigned char *out = new unsigned char[size];
    unsigned char *recovered = new unsigned char[size];
    
    // Encryption
    unsigned long start_enc = getMicroseconds();
    aes.encrypt(plain, out, nullptr, size);
    unsigned long delta_enc = getMicroseconds() - start_enc;

    // Decryption
    unsigned long start_dec = getMicroseconds();
    aes.decrypt(out, recovered, nullptr, size);
    unsigned long delta_dec = getMicroseconds() - start_dec;

    // Check if the decryption was successful
    if (memcmp(plain, recovered, size) != 0)
    {
      std::cerr << "Decryption failed!" << std::endl;
      return 1;
    }

    results_encrypt << size << "," << delta_enc << "\n";
    results_decrypt << size << "," << delta_dec << "\n";

    delete[] plain;
    delete[] out;
    delete[] recovered;
  }

  results_encrypt.close();
  std::cout << "Benchmark completed." << std::endl;

  return 0;
}

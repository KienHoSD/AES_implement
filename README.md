# AES_implement

This repository contains an implementation of the Advanced Encryption Standard (AES) algorithm. The AES algorithm is a widely used symmetric encryption algorithm that provides strong security for data confidentiality.

## Usage

To use this implementation, follow these steps:

1. Clone the repository: `git clone https://github.com/KienHoSD/AES_implement.git`
2. Navigate to the project directory: `cd AES_implement`
3. Build the project using the provided Makefile: `make`

## Notes

- Supports AES-128 encryption and decryption.
- Supports ECB/CBC mode of operation.
- Have the same result with the AES-128 encryption and decryption in the `openssl` library.
- Can encrypt and decrypt buffers of arbitrary length (manual padding is required) and files.
- Uses a fixed key and IV for encryption and decryption. You can change the key and IV in the `main.cpp` file.
- Need furthur optimization for better performance (multi-threading, SIMD instructions, AES-NI, etc...).
- Is not suitable for production use.

## Makefile

The Makefile included in this repository provides an easy way to build the project. It contains the following targets:

- `all` (default): Builds the AES program, the test program, and the benchmark program.
- `clean`: Removes the compiled binaries and object files.
- `test`: Run the test program.
- `benchmark`: Run the benchmark program.

You can use these targets by running `make <target>` in the project directory.

## Contributing

Contributions are welcome! If you find a bug or have an idea for an improvement, please create an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

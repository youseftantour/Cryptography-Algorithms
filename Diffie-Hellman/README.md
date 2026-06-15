# Diffie-Hellman Key Exchange

## Overview

This project demonstrates the Diffie-Hellman Key Exchange protocol implemented in C++. The program allows two parties (Alice and Bob) to securely establish a shared secret key over an insecure communication channel.

After generating the shared secret, the program uses the key to encrypt and decrypt messages using XOR encryption.

## Features

* Modular exponentiation
* Public key generation
* Shared secret generation
* Diffie-Hellman key exchange simulation
* Message encryption
* Message decryption
* User input support
* Encryption verification testing

## Files

* diffie_hellman.cpp – Diffie-Hellman implementation
* test_diffie_hellman.cpp – Testing program

## Technologies Used

* C++
* Cryptography
* Modular Arithmetic
* Secure Communication Concepts

## Skills Demonstrated

* Key Exchange Protocols
* Cryptographic Concepts
* C++ Programming
* Secure Communication
* Algorithm Implementation

## Example

Input:

Prime Number (p): 23

Primitive Root (g): 5

Alice Private Key: 6

Bob Private Key: 15

Message: Hello World

Output:

Key Exchange Successful!

Encryption Test Passed!

Both users generate the same shared secret key and successfully encrypt and decrypt a message.

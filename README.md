# Objective
MD5 (Message-Digest Algorithm 5) is a widely used cryptographic hash function that produces a 128-bit hash value. It is commonly used to verify data integrity.
# Algorithm
**1. Initialize MD5 state variables:**
   - Four 32-bit variables (A, B, C, D) are initialized with predefined constants.

**2. Pre-processing:**
   - Append padding bits to the message such that the length is congruent to 448 modulo 512.
   - Append the original message length as a 64-bit integer.

**3. Process the message in 512-bit blocks:**
   - Divide the message into blocks of 512 bits each.
   - For each block, perform the following steps:
       a. Divide the block into 16 words of 32 bits each.
       b. Perform a series of 64 operations, grouped into four rounds, using bitwise operations and modular addition.

**4. Output:**
   - Concatenate the variables (A, B, C, D) to form the final 128-bit hash value.

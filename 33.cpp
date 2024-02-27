#include <stdio.h>
#include <stdint.h>
#define KEY_LENGTH 56
#define SUBKEY_LENGTH 48
#define LEFT_ROTATE(key, bits) (((key) << (bits)) | ((key) >> (28 - (bits))))

void generateSubkeys(uint64_t initialKey, uint64_t* subkeys) {
    uint64_t permutedKey = 0;
    int pc1[] = {57, 49, 41, 33, 25, 17, 9, 1,
                 58, 50, 42, 34, 26, 18, 10, 2,
                 59, 51, 43, 35, 27, 19, 11, 3,
                 60, 52, 44, 36, 63, 55, 47, 39,
                 31, 23, 15, 7, 62, 54, 46, 38,
                 30, 22, 14, 6, 61, 53, 45, 37,
                 29, 21, 13, 5, 28, 20, 12, 4};

    for (int i = 0; i < 56; i++) {
        uint64_t bit = (initialKey >> (64 - pc1[i])) & 0x1;
        permutedKey = (permutedKey << 1) | bit;
    }
    uint32_t leftHalf = (permutedKey >> 28) & 0xFFFFFFF;
    uint32_t rightHalf = permutedKey & 0xFFFFFFF;
    for (int i = 15; i >= 0; i--) {
        int shiftAmount = (i < 2 || i == 8 || i == 15) ? 1 : 2;
        leftHalf = LEFT_ROTATE(leftHalf, shiftAmount);
        rightHalf = LEFT_ROTATE(rightHalf, shiftAmount);
        uint64_t combinedKey = ((uint64_t)leftHalf << 28) | rightHalf;
        uint64_t subkey = 0;
        int pc2[] = {14, 17, 11, 24, 1, 5, 3, 28,
                     15, 6, 21, 10, 23, 19, 12, 4,
                     26, 8, 16, 7, 27, 20, 13, 2,
                     41, 52, 31, 37, 47, 55, 30, 40,
                     51, 45, 33, 48, 44, 49, 39, 56,
                     34, 53, 46, 42, 50, 36, 29, 32};

        for (int j = 0; j < 48; j++) {
            uint64_t bit = (combinedKey >> (56 - pc2[j])) & 0x1;
            subkey = (subkey << 1) | bit;
        }

        subkeys[i] = subkey;
    }
}

void decrypt(uint64_t* subkeys, uint64_t ciphertext, uint64_t* plaintext) {
    uint64_t permutedData = 0;
    int initialPermutation[] = {58, 50, 42, 34, 26, 18, 10, 2,
                                60, 52, 44, 36, 28, 20, 12, 4,
                                62, 54, 46, 38, 30, 22, 14, 6,
                                64, 56, 48, 40, 32, 24, 16, 8,
                                57, 49, 41, 33, 25, 17, 9, 1,
                                59, 51, 43, 35, 27, 19, 11, 3,
                                61, 53, 45, 37, 29, 21, 13, 5,
                                63, 55, 47, 39, 31, 23, 15, 7};

    for (int i = 0; i < 64; i++) {
        uint64_t bit = (ciphertext >> (64 - initialPermutation[i])) & 0x1;
        permutedData = (permutedData << 1) | bit;
    }
    uint32_t leftHalf = (permutedData >> 32) & 0xFFFFFFFF;
    uint32_t rightHalf = permutedData & 0xFFFFFFFF;
    for (int i = 0; i < 16; i++) {
        uint32_t temp = leftHalf;
        rightHalf = temp;
    }
    uint64_t combinedData = ((uint64_t)rightHalf << 32) | leftHalf;
    uint64_t finalData = 0;
    int finalPermutation[] = {40, 8, 48, 16, 56, 24, 64, 32,
                              39, 7, 47, 15, 55, 23, 63, 31,
                              38, 6, 46, 14, 54, 22, 62, 30,
                              37, 5, 45, 13, 53, 21, 61, 29,
                              36, 4, 44, 12, 52, 20, 60, 28,
                              35, 3, 43, 11, 51, 19, 59, 27,
                              34, 2, 42, 10, 50, 18, 58, 26,
                              33, 1, 41, 9, 49, 17, 57, 25};

    for (int i = 0; i < 64; i++) {
        uint64_t bit = (combinedData >> (64 - finalPermutation[i])) & 0x1;
        finalData = (finalData << 1) | bit;
    }

    *plaintext = finalData;
}

int main() {
    uint64_t initialKey = 0x0123456789ABCDEF; 
    uint64_t subkeys[56];
    uint64_t ciphertext = 0x85E813540F0AB405; 
    uint64_t plaintext;

    generateSubkeys(initialKey, subkeys);
    decrypt(subkeys, ciphertext, &plaintext);

    printf("Plaintext: 0x%016llX\n", plaintext);

    return 0;
}
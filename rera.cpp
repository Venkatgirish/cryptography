#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void vigenereEncrypt(char *plaintext, int *key, int keyLength, char *ciphertext) {
    int i, j = 0;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            
            int shift = key[j] % 26;
            j = (j + 1) % keyLength;

            
            if (isupper(plaintext[i])) {
                ciphertext[i] = ((plaintext[i] - 'A' + shift) % 26) + 'A';
            }
            
            else {
                ciphertext[i] = ((plaintext[i] - 'a' + shift) % 26) + 'a';
            }
        }
        
        else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[] = "9 0 1 7 23 15 21 14 11 11 2 8 9.";
    int key[] = {3, 19, 5}; 
    int keyLength = sizeof(key) / sizeof(key[0]);
    char ciphertext[100];

    printf("Plaintext: %s\n", plaintext);

    
    vigenereEncrypt(plaintext, key, keyLength, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
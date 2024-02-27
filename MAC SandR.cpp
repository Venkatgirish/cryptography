#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
#define KEYWORD_MAX_LENGTH 50
char* generate_cipher_sequence(const char* keyword);
char monoalphabetic_encryption(char ch, const char* cipher_sequence);
char monoalphabetic_decryption(char ch, const char* cipher_sequence);
int main() {
    char keyword[KEYWORD_MAX_LENGTH];
    char cipher_sequence[ALPHABET_SIZE + 1]; 
    char plaintext[1000];
    char ciphertext[1000];
    int i;
    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; 
    strcpy(cipher_sequence, generate_cipher_sequence(keyword));
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    for (i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = monoalphabetic_encryption(tolower(plaintext[i]), cipher_sequence);
    }
    ciphertext[i] = '\0';
	printf("Encrypted text: %s\n", ciphertext);
    for (i = 0; ciphertext[i] != '\0'; i++) {
        printf("%c", monoalphabetic_decryption(ciphertext[i], cipher_sequence));
    }
    printf("\n");

    return 0;
}
char* generate_cipher_sequence(const char* keyword) {
    static char cipher_sequence[ALPHABET_SIZE + 1]; 
    int i, j, k;
    int keyword_length = strlen(keyword);
    int index = 0;
    char used[ALPHABET_SIZE] = {0}; 
    strcpy(cipher_sequence, keyword);
    for (i = 0; i < keyword_length; i++) {
        used[tolower(keyword[i]) - 'a'] = 1;
    }
    for (j = 0; j < ALPHABET_SIZE; j++) {
        if (!used[j]) {
            cipher_sequence[index++] = 'a' + j;
        }
    }
    cipher_sequence[index] = '\0'; 

    return cipher_sequence;
}
char monoalphabetic_encryption(char ch, const char* cipher_sequence) {
    if (isalpha(ch)) {
        if (islower(ch)) {
            return cipher_sequence[ch - 'a'];
        } else {
            return toupper(cipher_sequence[tolower(ch) - 'a']);
        }
    } else {
        return ch; 
    }
}
char monoalphabetic_decryption(char ch, const char* cipher_sequence) {
    if (isalpha(ch)) {
        char* found = strchr(cipher_sequence, tolower(ch));
        if (found != NULL) {
            int index = found - cipher_sequence;
            if (islower(ch)) {
                return 'a' + index;
            } else {
                return toupper('a' + index);
            }
        } else {
            return ch; 
        }
    } else {
        return ch; 
    }
}
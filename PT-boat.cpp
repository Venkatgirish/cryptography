#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MATRIX_SIZE 5
void generatePlayfairMatrix(const char* key, char matrix[MATRIX_SIZE][MATRIX_SIZE]);
void decryptMessage(const char* ciphertext, const char matrix[MATRIX_SIZE][MATRIX_SIZE], char* plaintext);
int main() {
    const char key[] = "PTBOAT";
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char plaintext[1000];
    generatePlayfairMatrix(key, matrix);
    decryptMessage(ciphertext, matrix, plaintext);
	printf("Decrypted message: %s\n", plaintext);
	return 0;
}
void generatePlayfairMatrix(const char* key, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int i, j, k = 0;
    int key_length = strlen(key);
    int used[26] = {0}; 
	for (i = 0; i < key_length; i++) {
        char current = toupper(key[i]);
        if (current == 'J') current = 'I'; 
        if (!isalpha(current)) continue; 
		if (!used[current - 'A']) {
            matrix[k / MATRIX_SIZE][k % MATRIX_SIZE] = current;
            used[current - 'A'] = 1;
            k++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (i != ('J' - 'A') && !used[i]) {
            matrix[k / MATRIX_SIZE][k % MATRIX_SIZE] = 'A' + i;
            k++;
        }
    }
}
void findPosition(const char matrix[MATRIX_SIZE][MATRIX_SIZE], char ch, int* row, int* col) {
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void decryptMessage(const char* ciphertext, const char matrix[MATRIX_SIZE][MATRIX_SIZE], char* plaintext) {
    int i, j;
    int len = strlen(ciphertext);
    int row1, col1, row2, col2;
    int idx = 0;
	for (i = 0; i < len; i += 2) {
        char ch1 = toupper(ciphertext[i]);
        char ch2 = toupper(ciphertext[i + 1]);
        findPosition(matrix, ch1, &row1, &col1);
        findPosition(matrix, ch2, &row2, &col2);
        if (row1 == row2) {
            plaintext[idx++] = matrix[row1][(col1 + MATRIX_SIZE - 1) % MATRIX_SIZE];
            plaintext[idx++] = matrix[row1][(col2 + MATRIX_SIZE - 1) % MATRIX_SIZE];
        }
        else if (col1 == col2) {
            plaintext[idx++] = matrix[(row1 + MATRIX_SIZE - 1) % MATRIX_SIZE][col1];
            plaintext[idx++] = matrix[(row2 + MATRIX_SIZE - 1) % MATRIX_SIZE][col2];
        }
        else {
            plaintext[idx++] = matrix[row1][col2];
            plaintext[idx++] = matrix[row2][col1];
        }
    }
    plaintext[idx] = '\0'; 
}
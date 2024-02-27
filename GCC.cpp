#include <stdio.h>
#include <ctype.h>

char encryptChar(int a, int b, char ch) 
{
    if (isalpha(ch))
	 {
        char base = isupper(ch) ? 'A' : 'a';
        return ((a * (ch - base) + b) % 26) + base;
    } else {
        return ch; 
    }
}


void encryptString(int a, int b, char *str) {
    while (*str != '\0') {
        *str = encryptChar(a, b, *str);
        str++;
    }
}

int main() {
    char plaintext[1000];
    int a, b;

    
    printf("Enter the value of a (must be coprime to 26): ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);

    
    if (a % 2 == 0 || a % 13 == 0) {
        printf("Invalid value of 'a'. It must be coprime to 26.\n");
        return 1;
    }

   
    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);
	encryptString(a, b, plaintext);
	printf("Ciphertext: %s\n", plaintext);

    return 0;
}
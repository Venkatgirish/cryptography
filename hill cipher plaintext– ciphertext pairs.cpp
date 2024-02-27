#include <stdio.h>
#include <string.h>
#include <ctype.h>


void matrixMultiply(int key[2][2], int message[2], int result[2]) 
{
    result[0] = key[0][0] * message[0] + key[0][1] * message[1];
    result[1] = key[1][0] * message[0] + key[1][1] * message[1];
}


void hillEncrypt(char *message, int key[2][2], char *encrypted)
 {
    int len = strlen(message);
    int i, j;

    
    if (len % 2 != 0)
	 {
        strcat(message, "X"); 
        len++;
    }

    
    int numericalMessage[len];
    for (i = 0; i < len; i++)
	 {
        if (isalpha(message[i]))
		 {
            numericalMessage[i] = toupper(message[i]) - 'A';
        } 
		else 
		{
            numericalMessage[i] = 25; 
        }
    }

    
    for (i = 0; i < len; i += 2) 
	{
        int messageBlock[2] = {numericalMessage[i], numericalMessage[i + 1]};
        int encryptedBlock[2];
        matrixMultiply(key, messageBlock, encryptedBlock);
        for (j = 0; j < 2; j++) 
		{
            encrypted[i + j] = (encryptedBlock[j] % 26) + 'A'; 
        }
    }
    encrypted[len] = '\0';
}

int main()
 {
    char message[] = "today afternoon meet mesufficient plaintext– ciphertext pairs ";
    int key[2][2] = {{9, 4}, {5, 7}};
    char encrypted[100];

    printf("Original Message: %s\n", message);

    hillEncrypt(message, key, encrypted);

    printf("Encrypted Message: %s\n", encrypted);

    return 0;
}
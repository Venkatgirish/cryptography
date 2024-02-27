#include <stdio.h>
#include <string.h>

int main()
 {
    char pt[20] = {'\0'}, ct[20] = {'\0'}, key[20] = {'\0'};
    int i, j;

    printf("\nEnter the plain text: ");
    scanf("%s", pt);

    printf("Enter the key: ");
    scanf("%s", key);

    j = 0;
    for (i = strlen(key); i < strlen(pt); i++) 
	{
        if (j == strlen(key)) 
		{
            j = 0;
        }
        key[i] = key[j];
        j++;
    }
    key[strlen(pt)] = '\0'; 

    printf("New key is: %s\n", key);

   
    for (i = 0; i < strlen(pt); i++)
	 {
        ct[i] = (((pt[i] - 'a') + (key[i] - 'a')) % 26) + 'a';
    }
    ct[strlen(pt)] = '\0'; 

    printf("Cipher text is: %s\n", ct);

    return 0;
}
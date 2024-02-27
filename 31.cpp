#include <stdio.h>


void left_shift(unsigned char *block, int block_size) {
    int i;
    unsigned char carry = 0;
    for (i = 0; i < block_size; i++) {
        unsigned char next_carry = block[i] >> (8 - 1);
        block[i] = (block[i] << 1) | carry;
        carry = next_carry;
    }
}
void xor_blocks(unsigned char *block1, unsigned char *block2, int block_size) {
    int i;
    for (i = 0; i < block_size; i++) {
        block1[i] ^= block2[i];
    }
}


void generate_subkeys(unsigned char *subkey1, unsigned char *subkey2, int block_size) {
    unsigned char zeros[block_size];
    int i;
    for (i = 0; i < block_size; i++) {
        zeros[i] = 0x00;
    }


    left_shift(zeros, block_size);
    if (block_size == 8) {
       
        zeros[block_size - 1] ^= 0x1B; 
    } else if (block_size == 16) {
        
        zeros[block_size - 1] ^= 0x87; 
    }
    for (i = 0; i < block_size; i++) {
        subkey1[i] = zeros[i];
    }
    left_shift(subkey1, block_size);
    if (block_size == 8) {
        subkey1[block_size - 1] ^= 0x1B; 
    } else if (block_size == 16) {
        subkey1[block_size - 1] ^= 0x87; 
    }
    for (i = 0; i < block_size; i++) {
        subkey2[i] = subkey1[i];
    }
}
void print_block(unsigned char *block, int block_size) {
    int i;
    for (i = 0; i < block_size; i++) {
        printf("%02X ", block[i]);
    }
    printf("\n");
}

int main() {
    int block_size = 16; 
    unsigned char subkey1[block_size];
    unsigned char subkey2[block_size];

    generate_subkeys(subkey1, subkey2, block_size);

    printf("First Subkey: ");
    print_block(subkey1, block_size);

    printf("Second Subkey: ");
    print_block(subkey2, block_size);

    return 0;
}

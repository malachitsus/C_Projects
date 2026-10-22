#include <stdio.h>
#include <limits.h>

void print_binary(unsigned int x) {
    for (int i = 31; i >= 0; i--) {
        printf("%u", (x >> i) & 1);
    }
}

int validate(unsigned int a, unsigned int b) {
    if (a > INT_MAX - b) {
        return 1;
    }
    return 0;
}

int main(void) {

    printf("Welcome.\n");

    do {
        int aint, bint;
        printf("Enter your numbers or enter any text to exit the program.\n");

        printf("First: ");
        if (scanf("%d", &aint) != 1) {
            break;
        }

        printf("Second: ");
        if (scanf("%d", &bint) != 1) {
            break;
        }

        if (aint < 0 || bint < 0) {
            printf("Error: number must be non-negative\n");
            continue;
        }
                
        if (validate(aint, bint)) {
           printf("Error: Overflow\n\n");
           continue;
        }



        unsigned int a = (unsigned int)aint;
        unsigned int b = (unsigned int)bint;
        
        unsigned int sum;
        unsigned int carry = 0;
        unsigned int result = 0;
        unsigned int new_carry = 0;

        for (int i = 0; i <= 31; i++) {
            unsigned int a_bit = (a >> i) & 0x1;
            unsigned int b_bit = (b >> i) & 0x1;
            sum = a_bit ^ b_bit ^ carry; 

            new_carry = ((a_bit & b_bit) | (a_bit & carry) | (b_bit & carry));

            result = result | (sum << i);
            carry = new_carry;
        }

        printf("==============================\n");
        printf("Result: %u\n\n", result);

        printf("a:      ");
        print_binary(a);
        printf("\n");

        printf("b:      ");
        print_binary(b);
        printf("\n");

        printf("Result(bin): ");
        print_binary(result);
        printf("\n\n");

        
    } while (1);

    return 0;
}
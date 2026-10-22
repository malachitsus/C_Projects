#include <stdio.h>

float unite_bit_parts(unsigned int sign, unsigned int exp, unsigned int mantiss) {

        union {
        unsigned int u;
        float f;
    } converter;

    // Сборка 32-битного числа из знака, экспоненты и мантиссы
    converter.u = ((unsigned int)sign << 31) | 
                  (((unsigned int)exp & 0xFF) << 23) | 
                  ((unsigned int)mantiss & 0x7FFFFF);

    return converter.f;
}

float a_to_bit_and_back(float a) {

    union {
        float f;
        unsigned int u;
    } converter;

    converter.f = a;
    unsigned int u = converter.u;

    // Выделение знака и экспоненты сдвигами
    unsigned int sign = (u >> 31) & 0x1;
    unsigned int exp = ((u >> 23) & 0xFF);

    // Увеличение экспоненты на 5 для умножения на 2^5 = 32
    if (exp != 0) {
        exp += 5;
    }

    // Выделение 23 бит мантиссы последовательными сдвигами влево и вправо
    unsigned int mantiss = (u << 9) >> 9;

    // Обработка переполнения порядка и перевод числа в Бесконечность (inf)
    if (exp >= 0xFF) {
        exp = 0xFF;    // Максимальный порядок для спец-значений
        mantiss = 0;   // При нулевой мантиссе и exp=255 float превращается в Infinity
    }



    return unite_bit_parts(sign, exp, mantiss);
}



int main(void) {

    printf("Welcome.\n");

    do {
        float a_input;
        printf("Enter your float number or enter any text to exit the program.\n");

        if (scanf("%f", &a_input) != 1) {
            break;
        }
        
        float a_edited = a_to_bit_and_back(a_input);
        printf("===========================\n");
        printf("Float*32: %f\n\n", a_edited);

    } while (1);

    return 0;
}
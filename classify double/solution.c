#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

# define EXP_MASK 0x7FF0000000000000
# define FRAC_MASK 0x000FFFFFFFFFFFFF


/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

bool getBit (const uint64_t number, const uint8_t index) {
    return (number >> index) & 1;
}


/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    bool minus_sing = getBit(number, 63);
    uint64_t exp = number & EXP_MASK;
    uint64_t frac = number & FRAC_MASK;
    return !minus_sing && exp == 0 && frac == 0;
}

bool checkForMinusZero (uint64_t number) {
    bool minus_sing = getBit(number, 63);
    uint64_t exp = number & EXP_MASK;
    uint64_t frac = number & FRAC_MASK;
    return minus_sing && exp == 0 && frac == 0;
}

bool checkForPlusInf (uint64_t number) {
    bool minus_sing = getBit(number, 63);
    uint64_t exp = number & EXP_MASK;
    uint64_t frac = number & FRAC_MASK;
    return !minus_sing && exp == EXP_MASK && frac == 0;
}

bool checkForMinusInf (uint64_t number) {
    bool minus_sing = getBit(number, 63);
    uint64_t exp = number & EXP_MASK;
    uint64_t frac = number & FRAC_MASK;
    return minus_sing && exp == EXP_MASK && frac == 0;
}

bool checkForPlusNormal (uint64_t number) {
    bool minus_sing = getBit(number, 63);
    uint64_t exp = number & EXP_MASK;
    uint64_t frac = number & FRAC_MASK;
    return !minus_sing && exp > 0 && exp != EXP_MASK;
}

bool checkForMinusNormal (uint64_t number) {
    bool minus_sing = getBit(number, 63);
    uint64_t exp = number & EXP_MASK;
    uint64_t frac = number & FRAC_MASK;
    return minus_sing && exp > 0 && exp != EXP_MASK;
}

bool checkForPlusDenormal (uint64_t number) {
    bool minus_sing = getBit(number, 63);
    uint64_t exp = number & EXP_MASK;
    uint64_t frac = number & FRAC_MASK;
    return !minus_sing && exp == 0 && frac != 0;
}

bool checkForMinusDenormal (uint64_t number) {
    bool minus_sing = getBit(number, 63);
    uint64_t exp = number & EXP_MASK;
    uint64_t frac = number & FRAC_MASK;
    return minus_sing && exp == 0 && frac != 0;
}

bool checkForSignalingNan (uint64_t number) {
    bool quiet_sign = getBit(number, 51);
    uint64_t exp = number & EXP_MASK;
    uint64_t frac = number & FRAC_MASK;
    return !quiet_sign && exp == EXP_MASK;
}

bool checkForQuietNan (uint64_t number) {
    bool quiet_sign = getBit(number, 51);
    uint64_t exp = number & EXP_MASK;
    uint64_t frac = number & FRAC_MASK;
    return quiet_sign && exp == EXP_MASK;
}


void classify (double number) {
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n");
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n");
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n");
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus normal\n");
    }

    else if (checkForMinusNormal(convertToUint64(number))) {
        printf("Minus normal\n");
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n");
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n");
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signailing NaN\n");
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n");
    }

    else {
        printf("Error.\n");
    }
}


int main (int argc, char **argv)
{
    if (argc > 1)
    {
        int i = 1;
        while (i < argc)
        {
            double num = atof(argv[i]);
            printf("read %.2f, this number is: ", num);
            classify(num);
            i++;
        }
    }
    else
        printf("waiting arguments for program");
    return (0);
}

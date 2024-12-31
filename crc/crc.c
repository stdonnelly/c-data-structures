#include <stdio.h>
#include <stdint.h>

uint32_t crc32(const char *input);

int main(int argc, char const *argv[])
{
    const char *crc_input = (argc >= 2) ? argv[1] : "";
    uint32_t crc_sum = crc32(crc_input);
    printf("CRC32 of '%s':\n%08X\n", crc_input, crc_sum);
    return 0;
}

uint32_t crc32(const char *input)
{
    // The result, start with 0
    // This is 64-bit because we need bit 32 to determine if we should XOR the polynomial
    uint64_t result = 0;
    // Polynomial for the standard CRC-32
    const uint32_t polynomial = 0x04C11DB7;

    while (*input)
    {
        // Look over bits in input, starting with the most significant
        for (int i = 7; i >= 0; i--)
        {
            // Shift result
            result <<= 1;
            // Shift in input
            result |= (*input >> i) & 1;

            // Do crc calculation
            // Check bit 32
            if (result & ((uint64_t)1 << 32))
                // If this matches, do the XOR
                result ^= polynomial;
        }
        // Next character
        input++;
    }

    // Do the last 32 bits
    for (int i = 0; i < 32; i++)
    {
        result <<= 1;
        // Do crc calculation
        // Check bit 32
        if (result & ((uint64_t)1 << 32))
            // If this matches, do the XOR
            result ^= polynomial;
    }

    // Invert the result before returning
    return ~(uint32_t)result;
}
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

enum { OPCODE_MASK = 0xFC };
enum { OPCODE_SHIFT = 2 };
enum { DIRECTION_MASK = 0x2 };
enum { DIRECTION_SHIFT = 1 };
enum { ISWORD_MASK = 0x1 };
enum { ISWORD_SHIFT = 0 };
enum { MODE_MASK = 0xC0 };
enum { MODE_SHIFT = 6 };
enum { REG_MASK = 0x38 };
enum { REG_SHIFT = 3 };
enum { RM_MASK = 0x07 };
enum { RM_SHIFT = 0 };

#define EXTRACT(v, field) (((v) & field##_MASK) >> field##_SHIFT)

#define MODE_REGISTER_TO_REGISTER 0x3

int FileReadAllBytes(const char *path, uint8_t **contents, uint32_t *length)
{
    FILE *f = fopen(path, "rb");
    if (!f) return -1;

    fseek(f, 0, SEEK_END);
    uint32_t fl = ftell(f);
    fseek(f, 0, SEEK_SET);

    uint8_t *bytes = calloc(1, fl);
    if (!bytes) return -1;

    if (fread(bytes, fl, 1, f) != 1) return -1;
    fclose(f);

    *length = fl;
    *contents = bytes;

    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) return -1;

    uint8_t *bytes;
    uint32_t length;

    if (FileReadAllBytes(argv[1], &bytes, &length)) return -1;

    #if 0
    for (uint32_t i = 0; i < length; ++i)
    {
        fprintf(stderr, "%02x ", bytes[i]);
        if ((i+1)%16 == 0) printf("\n");
    }
    fprintf(stderr, "\n");
    #endif

    printf("bits 16\n");

    uint8_t *at = bytes;
    uint8_t *end = bytes + length;

    while ((at+1) < end)
    {
        uint8_t byte1 = *at++;
        uint8_t byte2 = *at++;
        
        uint8_t opcode = EXTRACT(byte1, OPCODE);
        uint8_t direction = EXTRACT(byte1, DIRECTION);
        uint8_t word = EXTRACT(byte1, ISWORD);
        uint8_t mode = EXTRACT(byte2, MODE);
        uint8_t reg = EXTRACT(byte2, REG);
        uint8_t rm = EXTRACT(byte2, RM);

        const uint8_t OPCODE_MOV_RM = 0x22;

        if (opcode != OPCODE_MOV_RM)
        {
            fprintf(stderr, "Unexpected opcode %02x\n", opcode);
            return -1;
        }

        if (mode != MODE_REGISTER_TO_REGISTER)
        {
            fprintf(stderr, "Unsupported mode %02x\n", mode);
            return -1;
        }

        const char *registerNameLookup[] = {
            "al",
            "cl",
            "dl",
            "bl",
            "ah",
            "ch",
            "dh",
            "bh",

            "ax",
            "cx",
            "dx",
            "bx",
            "sp",
            "bp",
            "si",
            "di",
        };

        uint8_t reg1Index = (word << 3 | reg);
        uint8_t reg2Index = (word << 3 | rm);
        const char *reg1Name = registerNameLookup[reg1Index];
        const char *reg2Name = registerNameLookup[reg2Index];

        if (direction == 0)
        {
            const char *tmp = reg1Name;
            reg1Name = reg2Name;
            reg2Name = tmp;
        }
        printf("mov %s, %s\n", reg1Name, reg2Name);

        #if 0
        fprintf(stderr, "opcode: %02b\n", opcode);
        fprintf(stderr, "direction: %02b\n", direction);
        fprintf(stderr, "wordOrByte: %02b\n", word);
        fprintf(stderr, "mode: %02b\n", mode);
        fprintf(stderr, "reg1: %02b\n", reg1);
        fprintf(stderr, "reg2: %02b\n", reg2);
        #endif
    }

    return 0;
}

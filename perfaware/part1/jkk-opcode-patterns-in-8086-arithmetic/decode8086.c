#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "opcodes.h"

#define MODE_REGISTER_TO_REGISTER 0x3

int FileReadAllBytes(const char *path, uint8_t **contents, uint32_t *length) {
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

void DumpBytes(uint8_t *bytes, uint32_t length)
{
    for (uint32_t i = 0; i < length; ++i)
    {
        fprintf(stderr, "%02x ", bytes[i]);
        if ((i+1)%16 == 0) fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
}

int main(int argc, char **argv) {
    if (argc < 2) return -1;

    uint8_t *bytes;
    uint32_t length;

    if (FileReadAllBytes(argv[1], &bytes, &length)) return -1;

//    DumpBytes(bytes, length);

    printf("bits 16\n");

    uint8_t *at = bytes;
    uint8_t *end = bytes + length;

    while (at < end) {

        OcInfo info;
        if (GetOpcodeInfo(at, end, &info) == -1) {
            fprintf(stderr, "Could not get opcode info\n");
            return -1;
        }

        if (PrintOpcode(info, &at, end)) {
            return -1;
        }
    }

    return 0;
}

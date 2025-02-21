#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    const char *instructionName;
    const char *format;
    const char *description;
} InstEncodingText;

typedef struct {
    int8_t byte;
    int8_t bit;
} BitLoc;


typedef uint8_t InstFlags;
enum {
    InstFlags_EncodingInUse = (1u << 0),
    InstFlags_DataLo = (0u << 1),
    InstFlags_DataHi = (0u << 2),
    InstFlags_DispLo = (0u << 3),
    InstFlags_DispHi = (0u << 4),
    InstFlags_AddrLo = (0u << 5),
    InstFlags_AddrHi = (0u << 6),
};

typedef struct {
    struct {
        BitLoc d;
        BitLoc w;
        BitLoc mod;
        BitLoc reg;
        BitLoc regMem;
        BitLoc sr;
    } loc;
    InstFlags flags;
    uint8_t fixedBits;
    uint8_t fixedBitsMask;
} InstEncodingSpec;

static InstEncodingText instructionEncodingTexts[] = {
    {"mov",   "100010 d w | mod reg r/m | (DispL) | (DispH)", "Register/memory to/from register"},
    {"mov",   "1100011  w | mod reg r/m | (DispL) | (DispH) | DataL | (DataH)", "Immediate to register/memory"},
    {"mov",   "1011 w reg | DataL | (DataH)", "Immediate to register"},
    {"mov",   "1010000  w | AddrL | AddrH", "Memory to accumulator"},
    {"mov",   "1010001  w | AddrL | AddrH", "Accumulator to memory"},
    {"mov",   "10001110 | mod 0 sr r/m | (DispL) | (DispH)", "Register/memory to segment register"},
    {"mov",   "10001100 | mod 0 sr r/m | (DispL) | (DispH)", "Segment register to register memory"},
    {"push",  "11111111 | mod 110 r/m | (DispL) | (DispH)", "Register/memory"},
    {"push",  "01010 reg", "Register"},
    {"push",  "000 sr 110", "Segment register"},
    {"pop",   "10001111 | mod 000 r/m | (DispL) | (DispH)", "Register/memory"},
    {"pop",   "01011 reg", "Register"},
    {"pop",   "000 sr 111", "Segment register"},
    {"xchg",  "1000011 w | mod reg r/m | (DispL) | (DispH)", "Register/memory with register"},
    {"xchg",  "10010 reg", "Register with accumulator"},
    {"in",    "1110010 w | DataL", "Fixed port"},
    {"in",    "1110110 w", "Variable port"},
    {"out",   "1110011 w | DataL", "Fixed port"},
    {"out",   "1110111 w", "Variable port"},
    {"xlat",  "11010111", "Translate byte to AL"},
    {"lea",   "10001101 | mod reg r/m | (DispL) | (DispH)", "Load EA to register"},
    {"lds",   "11000101 | mod reg r/m | (DispL) | (DispH)", "Load pointer to DS"},
    {"les",   "11000100 | mod reg r/m | (DispL) | (DispH)", "Load pointer to ES"},
    {"lahf",  "10011111", "Load AH with flags"},
    {"sahf",  "10011110", "Store AH into flags"},
    {"pushf", "10011100", "Push flags"},
    {"popf",  "10011101", "Pop flags"},
    {"add",   "000000 d w | mod reg r/m | (DispL) | (DispH)", "Reg/memory with register to either"},
    {"add",   "100000 s w | mod 010 r/m | (DispL) | (DispH) | DataL | (DataH)", "Immediate to register/memory"},
    {"add",   "0000010 w | DataL | (DataH)", "Immediate to accumulator"},

};

InstEncodingSpec Blegh(InstEncodingText iet) {
    const char *at = iet.format;

    InstEncodingSpec spec = {0};
    memset(&spec.loc, ~0, sizeof(spec.loc));
    spec.flags |= InstFlags_EncodingInUse;

    for (int byte = 0; byte < 6 && *at; ++byte) {
        for (char bit = 7; bit >= 0 && *at;) {

            // Eat whitespace
            while(*at && *at <= ' ') ++at;

            BitLoc loc = {byte, bit};

            if (*at == '0' || *at == '1') {
                if (byte == 0) {
                    spec.fixedBitsMask |= 1 << bit;
                    if (*at == '1') spec.fixedBits |= 1 << bit;
                }
                bit -= 1;
                at += 1;
            } else if (*at == 'w') {
                spec.loc.w = loc;
                bit -= 1;
                at += 1;
            } else if (*at == 'd') {
                spec.loc.d = loc;
                bit -= 1;
                at += 1;
            } else if (strncmp(at, "mod", 3) == 0) {
                spec.loc.mod = loc;
                bit -= 2;
                at += 3;
            } else if (strncmp(at, "reg", 3) == 0) {
                spec.loc.reg = loc;
                bit -= 3;
                at += 3;
            } else if (strncmp(at, "r/m", 3) == 0) {
                spec.loc.regMem = loc;
                bit -= 3;
                at += 3;
            } else if (strncmp(at, "sr", 2) == 0) {
                spec.loc.regMem = loc;
                bit -= 2;
                at += 2;
            } else if (strncmp(at, "(DispL)", 7) == 0) {
                spec.flags |= InstFlags_DispLo;
                bit -= 8;
                at += 7;
            } else if (strncmp(at, "(DispH)", 7) == 0) {
                spec.flags |= InstFlags_DispHi;
                bit -= 8;
                at += 7;
            } else if (strncmp(at, "DataL", 5) == 0) {
                spec.flags |= InstFlags_DataLo;
                bit -= 8;
                at += 5;
            } else if (strncmp(at, "(DataH)", 7) == 0) {
                spec.flags |= InstFlags_DataHi;
                bit -= 8;
                at += 7;
            } else if (strncmp(at, "AddrL", 5) == 0) {
                spec.flags |= InstFlags_AddrLo;
                bit -= 8;
                at += 5;
            } else if (strncmp(at, "AddrH", 5) == 0) {
                spec.flags |= InstFlags_AddrHi;
                bit -= 8;
                at += 5;
            } else {
                fprintf(stderr, "TODO: %s\n", at);
                return spec;
            }
        }

        // Eat trailing whitespace
        while(*at && *at <= ' ') ++at;

        if (*at)
        {
            assert(*at == '|');
            ++at;
        }
    }

    return spec;
}

const char *byteStrings[256] = {
    "00000000","00000001","00000010","00000011","00000100","00000101","00000110","00000111","00001000","00001001","00001010","00001011","00001100","00001101","00001110","00001111","00010000","00010001","00010010","00010011","00010100","00010101","00010110","00010111","00011000","00011001","00011010","00011011","00011100","00011101","00011110","00011111","00100000","00100001","00100010","00100011","00100100","00100101","00100110","00100111","00101000","00101001","00101010","00101011","00101100","00101101","00101110","00101111","00110000","00110001","00110010","00110011","00110100","00110101","00110110","00110111","00111000","00111001","00111010","00111011","00111100","00111101","00111110","00111111","01000000","01000001","01000010","01000011","01000100","01000101","01000110","01000111","01001000","01001001","01001010","01001011","01001100","01001101","01001110","01001111","01010000","01010001","01010010","01010011","01010100","01010101","01010110","01010111","01011000","01011001","01011010","01011011","01011100","01011101","01011110","01011111","01100000","01100001","01100010","01100011","01100100","01100101","01100110","01100111","01101000","01101001","01101010","01101011","01101100","01101101","01101110","01101111","01110000","01110001","01110010","01110011","01110100","01110101","01110110","01110111","01111000","01111001","01111010","01111011","01111100","01111101","01111110","01111111","10000000","10000001","10000010","10000011","10000100","10000101","10000110","10000111","10001000","10001001","10001010","10001011","10001100","10001101","10001110","10001111","10010000","10010001","10010010","10010011","10010100","10010101","10010110","10010111","10011000","10011001","10011010","10011011","10011100","10011101","10011110","10011111","10100000","10100001","10100010","10100011","10100100","10100101","10100110","10100111","10101000","10101001","10101010","10101011","10101100","10101101","10101110","10101111","10110000","10110001","10110010","10110011","10110100","10110101","10110110","10110111","10111000","10111001","10111010","10111011","10111100","10111101","10111110","10111111","11000000","11000001","11000010","11000011","11000100","11000101","11000110","11000111","11001000","11001001","11001010","11001011","11001100","11001101","11001110","11001111","11010000","11010001","11010010","11010011","11010100","11010101","11010110","11010111","11011000","11011001","11011010","11011011","11011100","11011101","11011110","11011111","11100000","11100001","11100010","11100011","11100100","11100101","11100110","11100111","11101000","11101001","11101010","11101011","11101100","11101101","11101110","11101111","11110000","11110001","11110010","11110011","11110100","11110101","11110110","11110111","11111000","11111001","11111010","11111011","11111100","11111101","11111110","11111111",
};

static InstEncodingSpec FirstByteToSpec[256];

void IterateInstEncodingSpec(InstEncodingSpec spec)
{
    uint8_t mask = spec.fixedBitsMask;
    uint8_t x = mask;
    printf("%s (mask)\n", byteStrings[x]);
    for (;;)
    {
        uint8_t index = spec.fixedBits | (x & ~spec.fixedBitsMask);

        FirstByteToSpec[index] = spec;
        printf("%s\n", byteStrings[index]);
        x = (x + 1) | mask;
        if (x == mask) break;
    }

    printf("---\n");
}

int main(void)
{
    for (size_t i = 0; i < sizeof(instructionEncodingTexts) / sizeof(*instructionEncodingTexts); ++i)
    {
        InstEncodingText iet = instructionEncodingTexts[i];
        printf("inst: %s\n", iet.instructionName);
        InstEncodingSpec spec = Blegh(iet);
        IterateInstEncodingSpec(spec);

    }
}

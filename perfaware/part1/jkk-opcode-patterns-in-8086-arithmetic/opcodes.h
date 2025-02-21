#ifndef OPCODES_H
#define OPCODES_H

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#define ABS(v) ((v) < 0 ? -(v) : (v))
#define EXFIELD(v, h, l) (((v)>>(l))&((1<<(1+(h)-(l)))-1))
#define EXBIT(v, b) (((v)>>(b))&1)

typedef uint32_t OcFeatures;
enum {
    BitD = (1 << 0),
    BitS = (1 << 1),
    BitV = (1 << 2),
    BitW_00 = (1 << 3),
    BitW_03 = (1 << 4),
    BitW = BitW_00|BitW_03,
    BitZ = (1 << 5),
    FieldMod = (1 << 6),
    FieldReg_0_20 = (1 << 7),
    FieldReg_1_42 = (1 << 8),
    FieldReg = FieldReg_0_20|FieldReg_1_42,
    FieldRegMem = (1 << 9),
    FieldSegReg_0_43 = (1 << 10),
    FieldSegReg_1_43 = (1 << 11),
    FieldSegReg = FieldSegReg_0_43|FieldSegReg_1_43,
    FieldSubOc_0_53 = (1 << 12),
    FieldSubOc_1_53 = (1 << 13),
    FieldSubOc = FieldSubOc_0_53|FieldSubOc_1_53,
    Addr = (1 << 14),
    Data = (1 << 15),
    Data8 = (1 << 16),
    Disp = (1 << 17),
};

typedef struct {
    uint8_t length;
    OcFeatures features;
} OcSpec;

typedef struct {
    uint8_t w;
    uint8_t d;
    uint8_t s;
    uint8_t v;
    uint8_t z;
    uint8_t mode;
    uint8_t reg;
    uint8_t regMem;
    uint16_t data;
    uint16_t displacement;
} OcInfo;

typedef struct {
    uint8_t byte;
    uint8_t bit;
} BitPosition;

typedef struct {
    const char *instructionName;
    BitPosition reg;
    BitPosition regMem;
    BitPosition blank; // I.e. add vs. sub. vs cmp ...
    uint8_t dataPosition;
    uint8_t displacementPosition;
} DecodeInfo;

static const char *immedInsTable[8] =
    {"add", "or", "adc", "sbb", "and", "sub", "xor", "cmp"};

static const char *shiftInsTable[8] =
    {"rol", "ror", "rcl", "rcr", "shl", "shr", "--", "sar"};

static const char *group1InsTable[8] =
    {"test", "--", "not", "neg", "mul", "imul", "div", "idiv"};

static const char *group2InsTable[8] =
    {"inc", "dec", "call", "call", "jmp", "jmp", "push", "--"};


typedef struct {
    const char *instructionName;
    const char *format;
    const char *description;
} InstEncodingText;


static InstEncodingText instructionEncodingTexts[] = {
{"mov", "100010 d w | mod reg r/m | (disp_lo) | (disp_hi)"},
{"mov", "1100011  w | mod reg r/m | (disp_lo) | (disp_hi) | data | (data_hi)"},
{"mov", "1011 w reg | data | (data_hi)"},
{"mov", "1010000  w | addr_lo | addr_hi"},
{"mov", "1010001  w | addr_lo | addr_hi"},
{"mov", "10001110 | mod 0 SR r/m | (disp_lo) | (disp_hi)"},
};

// bits, group, format
#define OC_INFO_LIST(X) \
    X(0b00000000, add, BitD|BitW_00|FieldMod|FieldReg_1_42|FieldRegMem|Disp) \
    X(0b00000001, OC_TODO, 0, 1, 0) \
    X(0b00000010, OC_TODO, 0, 1, 0) \
    X(0b00000011, OC_TODO, 0, 1, 0) \
    X(0b00000100, OC_TODO, 0, 1, 0) \
    X(0b00000101, OC_TODO, 0, 1, 0) \
    X(0b00000110, OC_TODO, 0, 1, 0) \
    X(0b00000111, OC_TODO, 0, 1, 0) \
    X(0b00001000, OC_TODO, 0, 1, 0) \
    X(0b00001001, OC_TODO, 0, 1, 0) \
    X(0b00001010, OC_TODO, 0, 1, 0) \
    X(0b00001011, OC_TODO, 0, 1, 0) \
    X(0b00001100, OC_TODO, 0, 1, 0) \
    X(0b00001101, OC_TODO, 0, 1, 0) \
    X(0b00001110, OC_TODO, 0, 1, 0) \
    X(0b00001111, OC_TODO, 0, 1, 0) \
    X(0b00010000, OC_TODO, 0, 1, 0) \
    X(0b00010001, OC_TODO, 0, 1, 0) \
    X(0b00010010, OC_TODO, 0, 1, 0) \
    X(0b00010011, OC_TODO, 0, 1, 0) \
    X(0b00010100, OC_TODO, 0, 1, 0) \
    X(0b00010101, OC_TODO, 0, 1, 0) \
    X(0b00010110, OC_TODO, 0, 1, 0) \
    X(0b00010111, OC_TODO, 0, 1, 0) \
    X(0b00011000, OC_TODO, 0, 1, 0) \
    X(0b00011001, OC_TODO, 0, 1, 0) \
    X(0b00011010, OC_TODO, 0, 1, 0) \
    X(0b00011011, OC_TODO, 0, 1, 0) \
    X(0b00011100, OC_TODO, 0, 1, 0) \
    X(0b00011101, OC_TODO, 0, 1, 0) \
    X(0b00011110, OC_TODO, 0, 1, 0) \
    X(0b00011111, OC_TODO, 0, 1, 0) \
    X(0b00100000, OC_TODO, 0, 1, 0) \
    X(0b00100001, OC_TODO, 0, 1, 0) \
    X(0b00100010, OC_TODO, 0, 1, 0) \
    X(0b00100011, OC_TODO, 0, 1, 0) \
    X(0b00100100, OC_TODO, 0, 1, 0) \
    X(0b00100101, OC_TODO, 0, 1, 0) \
    X(0b00100110, OC_TODO, 0, 1, 0) \
    X(0b00100111, OC_TODO, 0, 1, 0) \
    X(0b00101000, OC_TODO, 0, 1, 0) \
    X(0b00101001, OC_TODO, 0, 1, 0) \
    X(0b00101010, OC_TODO, 0, 1, 0) \
    X(0b00101011, OC_TODO, 0, 1, 0) \
    X(0b00101100, OC_TODO, 0, 1, 0) \
    X(0b00101101, OC_TODO, 0, 1, 0) \
    X(0b00101110, OC_TODO, 0, 1, 0) \
    X(0b00101111, OC_TODO, 0, 1, 0) \
    X(0b00110000, OC_TODO, 0, 1, 0) \
    X(0b00110001, OC_TODO, 0, 1, 0) \
    X(0b00110010, OC_TODO, 0, 1, 0) \
    X(0b00110011, OC_TODO, 0, 1, 0) \
    X(0b00110100, OC_TODO, 0, 1, 0) \
    X(0b00110101, OC_TODO, 0, 1, 0) \
    X(0b00110110, OC_TODO, 0, 1, 0) \
    X(0b00110111, OC_TODO, 0, 1, 0) \
    X(0b00111000, OC_TODO, 0, 1, 0) \
    X(0b00111001, OC_TODO, 0, 1, 0) \
    X(0b00111010, OC_TODO, 0, 1, 0) \
    X(0b00111011, OC_TODO, 0, 1, 0) \
    X(0b00111100, OC_TODO, 0, 1, 0) \
    X(0b00111101, OC_TODO, 0, 1, 0) \
    X(0b00111110, OC_TODO, 0, 1, 0) \
    X(0b00111111, OC_TODO, 0, 1, 0) \
    X(0b01000000, OC_TODO, 0, 1, 0) \
    X(0b01000001, OC_TODO, 0, 1, 0) \
    X(0b01000010, OC_TODO, 0, 1, 0) \
    X(0b01000011, OC_TODO, 0, 1, 0) \
    X(0b01000100, OC_TODO, 0, 1, 0) \
    X(0b01000101, OC_TODO, 0, 1, 0) \
    X(0b01000110, OC_TODO, 0, 1, 0) \
    X(0b01000111, OC_TODO, 0, 1, 0) \
    X(0b01001000, OC_TODO, 0, 1, 0) \
    X(0b01001001, OC_TODO, 0, 1, 0) \
    X(0b01001010, OC_TODO, 0, 1, 0) \
    X(0b01001011, OC_TODO, 0, 1, 0) \
    X(0b01001100, OC_TODO, 0, 1, 0) \
    X(0b01001101, OC_TODO, 0, 1, 0) \
    X(0b01001110, OC_TODO, 0, 1, 0) \
    X(0b01001111, OC_TODO, 0, 1, 0) \
    X(0b01010000, OC_TODO, 0, 1, 0) \
    X(0b01010001, OC_TODO, 0, 1, 0) \
    X(0b01010010, OC_TODO, 0, 1, 0) \
    X(0b01010011, OC_TODO, 0, 1, 0) \
    X(0b01010100, OC_TODO, 0, 1, 0) \
    X(0b01010101, OC_TODO, 0, 1, 0) \
    X(0b01010110, OC_TODO, 0, 1, 0) \
    X(0b01010111, OC_TODO, 0, 1, 0) \
    X(0b01011000, OC_TODO, 0, 1, 0) \
    X(0b01011001, OC_TODO, 0, 1, 0) \
    X(0b01011010, OC_TODO, 0, 1, 0) \
    X(0b01011011, OC_TODO, 0, 1, 0) \
    X(0b01011100, OC_TODO, 0, 1, 0) \
    X(0b01011101, OC_TODO, 0, 1, 0) \
    X(0b01011110, OC_TODO, 0, 1, 0) \
    X(0b01011111, OC_TODO, 0, 1, 0) \
    X(0b01100000, OC_TODO, 0, 1, 0) \
    X(0b01100001, OC_TODO, 0, 1, 0) \
    X(0b01100010, OC_TODO, 0, 1, 0) \
    X(0b01100011, OC_TODO, 0, 1, 0) \
    X(0b01100100, OC_TODO, 0, 1, 0) \
    X(0b01100101, OC_TODO, 0, 1, 0) \
    X(0b01100110, OC_TODO, 0, 1, 0) \
    X(0b01100111, OC_TODO, 0, 1, 0) \
    X(0b01101000, OC_TODO, 0, 1, 0) \
    X(0b01101001, OC_TODO, 0, 1, 0) \
    X(0b01101010, OC_TODO, 0, 1, 0) \
    X(0b01101011, OC_TODO, 0, 1, 0) \
    X(0b01101100, OC_TODO, 0, 1, 0) \
    X(0b01101101, OC_TODO, 0, 1, 0) \
    X(0b01101110, OC_TODO, 0, 1, 0) \
    X(0b01101111, OC_TODO, 0, 1, 0) \
    X(0b01110000, OC_TODO, 0, 1, 0) \
    X(0b01110001, OC_TODO, 0, 1, 0) \
    X(0b01110010, OC_TODO, 0, 1, 0) \
    X(0b01110011, OC_TODO, 0, 1, 0) \
    X(0b01110100, OC_TODO, 0, 1, 0) \
    X(0b01110101, OC_TODO, 0, 1, 0) \
    X(0b01110110, OC_TODO, 0, 1, 0) \
    X(0b01110111, OC_TODO, 0, 1, 0) \
    X(0b01111000, OC_TODO, 0, 1, 0) \
    X(0b01111001, OC_TODO, 0, 1, 0) \
    X(0b01111010, OC_TODO, 0, 1, 0) \
    X(0b01111011, OC_TODO, 0, 1, 0) \
    X(0b01111100, OC_TODO, 0, 1, 0) \
    X(0b01111101, OC_TODO, 0, 1, 0) \
    X(0b01111110, OC_TODO, 0, 1, 0) \
    X(0b01111111, OC_TODO, 0, 1, 0) \
    X(0b10000000, OC_TODO, 0, 1, 0) \
    X(0b10000001, OC_TODO, 0, 1, 0) \
    X(0b10000010, OC_TODO, 0, 1, 0) \
    X(0b10000011, OC_TODO, 0, 1, 0) \
    X(0b10000100, OC_TODO, 0, 1, 0) \
    X(0b10000101, OC_TODO, 0, 1, 0) \
    X(0b10000110, OC_TODO, 0, 1, 0) \
    X(0b10000111, OC_TODO, 0, 1, 0) \
    X(0b10001000, OC_MOV, OCV_MOV_RM_TF_R, 2, 0) \
    X(0b10001001, OC_MOV, OCV_MOV_RM_TF_R, 2, OCF_W) \
    X(0b10001010, OC_MOV, OCV_MOV_RM_TF_R, 2, OCF_D) \
    X(0b10001011, OC_MOV, OCV_MOV_RM_TF_R, 2, OCF_D|OCF_W) \
    X(0b10001100, OC_TODO, 0, 1, 0) \
    X(0b10001101, OC_TODO, 0, 1, 0) \
    X(0b10001110, OC_TODO, 0, 1, 0) \
    X(0b10001111, OC_TODO, 0, 1, 0) \
    X(0b10010000, OC_TODO, 0, 1, 0) \
    X(0b10010001, OC_TODO, 0, 1, 0) \
    X(0b10010010, OC_TODO, 0, 1, 0) \
    X(0b10010011, OC_TODO, 0, 1, 0) \
    X(0b10010100, OC_TODO, 0, 1, 0) \
    X(0b10010101, OC_TODO, 0, 1, 0) \
    X(0b10010110, OC_TODO, 0, 1, 0) \
    X(0b10010111, OC_TODO, 0, 1, 0) \
    X(0b10011000, OC_TODO, 0, 1, 0) \
    X(0b10011001, OC_TODO, 0, 1, 0) \
    X(0b10011010, OC_TODO, 0, 1, 0) \
    X(0b10011011, OC_TODO, 0, 1, 0) \
    X(0b10011100, OC_TODO, 0, 1, 0) \
    X(0b10011101, OC_TODO, 0, 1, 0) \
    X(0b10011110, OC_TODO, 0, 1, 0) \
    X(0b10011111, OC_TODO, 0, 1, 0) \
    X(0b10100000, OC_MOV, OCV_MOV_ACC_TF_M, 3, 0) \
    X(0b10100001, OC_MOV, OCV_MOV_ACC_TF_M, 3, OCF_W) \
    X(0b10100010, OC_MOV, OCV_MOV_ACC_TF_M, 3, OCF_D) \
    X(0b10100011, OC_MOV, OCV_MOV_ACC_TF_M, 3, OCF_D|OCF_W) \
    X(0b10100100, OC_TODO, 0, 1, 0) \
    X(0b10100101, OC_TODO, 0, 1, 0) \
    X(0b10100110, OC_TODO, 0, 1, 0) \
    X(0b10100111, OC_TODO, 0, 1, 0) \
    X(0b10101000, OC_TODO, 0, 1, 0) \
    X(0b10101001, OC_TODO, 0, 1, 0) \
    X(0b10101010, OC_TODO, 0, 1, 0) \
    X(0b10101011, OC_TODO, 0, 1, 0) \
    X(0b10101100, OC_TODO, 0, 1, 0) \
    X(0b10101101, OC_TODO, 0, 1, 0) \
    X(0b10101110, OC_TODO, 0, 1, 0) \
    X(0b10101111, OC_TODO, 0, 1, 0) \
    X(0b10110000, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X(0b10110001, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X(0b10110010, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X(0b10110011, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X(0b10110100, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X(0b10110101, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X(0b10110110, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X(0b10110111, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X(0b10111000, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X(0b10111001, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X(0b10111010, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X(0b10111011, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X(0b10111100, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X(0b10111101, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X(0b10111110, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X(0b10111111, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X(0b11000000, OC_TODO, 0, 1, 0) \
    X(0b11000001, OC_TODO, 0, 1, 0) \
    X(0b11000010, OC_TODO, 0, 1, 0) \
    X(0b11000011, OC_TODO, 0, 1, 0) \
    X(0b11000100, OC_TODO, 0, 1, 0) \
    X(0b11000101, OC_TODO, 0, 1, 0) \
    X(0b11000110, OC_MOV, OCV_MOV_IMM_T_RM, 2, 0) \
    X(0b11000111, OC_MOV, OCV_MOV_IMM_T_RM, 2, OCF_W) \
    X(0b11001000, OC_TODO, 0, 1, 0) \
    X(0b11001001, OC_TODO, 0, 1, 0) \
    X(0b11001010, OC_TODO, 0, 1, 0) \
    X(0b11001011, OC_TODO, 0, 1, 0) \
    X(0b11001100, OC_TODO, 0, 1, 0) \
    X(0b11001101, OC_TODO, 0, 1, 0) \
    X(0b11001110, OC_TODO, 0, 1, 0) \
    X(0b11001111, OC_TODO, 0, 1, 0) \
    X(0b11010000, OC_TODO, 0, 1, 0) \
    X(0b11010001, OC_TODO, 0, 1, 0) \
    X(0b11010010, OC_TODO, 0, 1, 0) \
    X(0b11010011, OC_TODO, 0, 1, 0) \
    X(0b11010100, OC_TODO, 0, 1, 0) \
    X(0b11010101, OC_TODO, 0, 1, 0) \
    X(0b11010110, OC_TODO, 0, 1, 0) \
    X(0b11010111, OC_TODO, 0, 1, 0) \
    X(0b11011000, OC_TODO, 0, 1, 0) \
    X(0b11011001, OC_TODO, 0, 1, 0) \
    X(0b11011010, OC_TODO, 0, 1, 0) \
    X(0b11011011, OC_TODO, 0, 1, 0) \
    X(0b11011100, OC_TODO, 0, 1, 0) \
    X(0b11011101, OC_TODO, 0, 1, 0) \
    X(0b11011110, OC_TODO, 0, 1, 0) \
    X(0b11011111, OC_TODO, 0, 1, 0) \
    X(0b11100000, OC_TODO, 0, 1, 0) \
    X(0b11100001, OC_TODO, 0, 1, 0) \
    X(0b11100010, OC_TODO, 0, 1, 0) \
    X(0b11100011, OC_TODO, 0, 1, 0) \
    X(0b11100100, OC_TODO, 0, 1, 0) \
    X(0b11100101, OC_TODO, 0, 1, 0) \
    X(0b11100110, OC_TODO, 0, 1, 0) \
    X(0b11100111, OC_TODO, 0, 1, 0) \
    X(0b11101000, OC_TODO, 0, 1, 0) \
    X(0b11101001, OC_TODO, 0, 1, 0) \
    X(0b11101010, OC_TODO, 0, 1, 0) \
    X(0b11101011, OC_TODO, 0, 1, 0) \
    X(0b11101100, OC_TODO, 0, 1, 0) \
    X(0b11101101, OC_TODO, 0, 1, 0) \
    X(0b11101110, OC_TODO, 0, 1, 0) \
    X(0b11101111, OC_TODO, 0, 1, 0) \
    X(0b11110000, OC_TODO, 0, 1, 0) \
    X(0b11110001, OC_TODO, 0, 1, 0) \
    X(0b11110010, OC_TODO, 0, 1, 0) \
    X(0b11110011, OC_TODO, 0, 1, 0) \
    X(0b11110100, OC_TODO, 0, 1, 0) \
    X(0b11110101, OC_TODO, 0, 1, 0) \
    X(0b11110110, OC_TODO, 0, 1, 0) \
    X(0b11110111, OC_TODO, 0, 1, 0) \
    X(0b11111000, OC_TODO, 0, 1, 0) \
    X(0b11111001, OC_TODO, 0, 1, 0) \
    X(0b11111010, OC_TODO, 0, 1, 0) \
    X(0b11111011, OC_TODO, 0, 1, 0) \
    X(0b11111100, OC_TODO, 0, 1, 0) \
    X(0b11111101, OC_TODO, 0, 1, 0) \
    X(0b11111110, OC_TODO, 0, 1, 0) \
    X(0b11111111, OC_TODO, 0, 1, 0) \
    /*end*/

#define BUILD_OC_TABLE(_, byte1, group, variant, minLength, flags) {group, variant, minLength, flags, 0, 0, 0, 0, 0},

static OcInfo OcInfoFromByte1[256] = {
OC_INFO_LIST(BUILD_OC_TABLE)
};

static uint16_t GetWord(uint8_t *at)
{
    return (at[1] << 8) | at[0];
}

static uint16_t SignExtend(int8_t v)
{
    return (int16_t)v;
}

static uint32_t GetDisplacement(uint8_t *at, OcInfo *info)
{
    if (info->mode == 1) {
        info->displacement = SignExtend(at[0]);
        return 1;
    } else if (info->mode == 2 || (info->mode == 0 && info->regMem == 6)) {
        info->displacement = GetWord(at);
        return 2;
    }

    return 0;
}

static uint32_t GetData(uint8_t *at, OcInfo *info)
{
    if (info->flags & OCF_W) {
        info->data = GetWord(at);
        return 2;
    } else {
        info->data = at[0];
        return 1;
    }

    return 0;
}

static int GetOpcodeInfo(uint8_t *at, uint8_t *end, OcInfo *result) {
    assert(at < end);

    OcInfo info = OcInfoFromByte1[at[0]];
    assert(at+info.length <= end);

    switch (info.group << 8 | info.variant) {
        case (OC_MOV<<8)|OCV_MOV_RM_TF_R: {
            assert(info.length == 2);

            info.mode = EXFIELD(at[1], 7, 6);
            info.reg = EXFIELD(at[1], 5, 3);
            info.regMem = EXFIELD(at[1], 2, 0);

            info.length += GetDisplacement(at + info.length, &info);
        } break;

        case (OC_MOV<<8)|OCV_MOV_IMM_T_RM: {
            assert(info.length == 2);

            info.mode = EXFIELD(at[1], 7,6);
            info.regMem = EXFIELD(at[1], 2, 0);

            info.length += GetDisplacement(at + info.length, &info);
            info.length += GetData(at + info.length, &info);
        } break;

        case (OC_MOV<<8)|OCV_MOV_IMM_T_R: {
            info.reg = EXFIELD(at[0], 2, 0);
            info.data = at[1];
            if (info.flags & OCF_W) info.data |= at[2] << 8;
        } break;

        case (OC_MOV<<8)|OCV_MOV_ACC_TF_M: {
            info.data = GetWord(at + 1);
        } break;

        default:
            fprintf(stderr, "TODO INFO: opcode %02x\n", at[0]);

    }

    *result = info;
    return 0;
}

#undef BUILD_OC_TABLE

static const char *GetRegName(uint8_t w, uint8_t reg) {
    static const char *registerNameLookup[] = {
        "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh",
        "ax", "cx", "dx", "bx", "sp", "bp", "si", "di",
    };

    if (w > 1) return NULL;
    if (reg > 7) return NULL;

    return registerNameLookup[w << 3 | reg]; 
}

static const char *GetEffectiveAddressOperand(uint8_t mode, uint8_t regMem, int16_t displacement)
{
    static char buf[512] = {0};
    assert(regMem < 8);
    assert(mode != 1 || ABS(displacement) < 128);

    char dispOp = '+';
    if (displacement < 0) {
        dispOp = '-';
        displacement = -displacement;
    }

    const char *baseStrings[8] = {
        "bx + si",
        "bx + di",
        "bp + si",
        "bp + di",
        "si",
        "di",
        "bp",
        "bx",
    };

    if (mode == 0 && regMem == 6) {
        snprintf(buf, sizeof buf, "[%d]", displacement);
    } else if (mode == 0 || displacement == 0) {
        snprintf(buf, sizeof buf, "[%s]", baseStrings[regMem]);
    } else {
        snprintf(buf, sizeof buf, "[%s %c %d]", baseStrings[regMem], dispOp, displacement);
    }

    return buf;
}

static int PrintOpcode(OcInfo info, uint8_t **atPtr, uint8_t *end) {
    uint8_t length = info.length;
    uint8_t *at = *atPtr;
    *atPtr = at + length;

    if (at + length > end) {
        return -1;
    }

    // fprintf(stderr, "{%d, %d}\n", info.group, info.variant);

    uint8_t w = (info.flags&OCF_W) ? 1 : 0;
    uint8_t d = (info.flags&OCF_D) ? 1 : 0;
    const char *regName = GetRegName(w, info.reg);
    const char *regMemName = GetRegName(w, info.regMem);

    const char *operandL = NULL;
    const char *operandR = NULL;

    switch ((info.group<<8) | info.variant) {

        case (OC_MOV<<8)|OCV_MOV_RM_TF_R: {

            if (info.mode == 3) {
                // register to register
                operandL = regName;
                operandR = regMemName;
            } else {
                operandL = regName;
                operandR = GetEffectiveAddressOperand(info.mode, info.regMem, info.displacement);
            }

            if (!d) {
                const char *tmp = operandL;
                operandL = operandR;
                operandR = tmp;
            }

            printf("mov %s, %s\n", operandL, operandR);
        } break;

        case (OC_MOV<<8)|OCV_MOV_IMM_T_RM: {
            operandL = GetEffectiveAddressOperand(info.mode, info.regMem, info.displacement);
            printf("mov %s, %s %u\n", operandL, w?"word":"byte", info.data);
        } break;

        case (OC_MOV<<8)|OCV_MOV_IMM_T_R: {
            printf("mov %s, %u\n", regName, info.data);
        } break;

        case (OC_MOV<<8)|OCV_MOV_ACC_TF_M: {
            const char *a = w ? "ax" : "al";
            if (d) {
                printf("mov [%u], %s\n", info.data, a);
            } else {
                printf("mov %s, [%u]\n", a, info.data);
            }
        } break;

        case OC_TODO:
            fprintf(stderr, "TODO opcode %02x\n", at[0]);
            break;

        default:
            fprintf(stderr, "Unexpected opcode %02x\n", at[0]);
            *atPtr = at + 1;
            return -1;
    }

    return 0;
}

#endif //OPCODES_H

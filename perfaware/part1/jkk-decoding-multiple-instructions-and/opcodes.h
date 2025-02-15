#ifndef OPCODES_H
#define OPCODES_H

#include <assert.h>
#include <stdint.h>
#include <stdio.h>


#define EXFIELD(v, h, l) (((v)>>(l))&((1<<(1+(h)-(l)))-1))
#define EXBIT(v, b) (((v)>>(b))&1)

typedef uint8_t OcVariant;
enum {
    OCV_MOV_RM_TF_R = 1,
    OCV_MOV_IMM_T_RM,
    OCV_MOV_IMM_T_R,
};

typedef uint8_t OcGroup;
enum {
    OC_TODO,
    OC_MOV,
};

typedef uint8_t OcFlags;
enum {
    OCF_D = (1 << 0),
    OCF_W = (1 << 1),
};

typedef struct {
    OcGroup group;
    OcVariant variant;
    uint8_t length;
    OcFlags flags;
    uint8_t mode;
    uint8_t reg;
    uint8_t regMem;
    uint16_t immediate;
} OcInfo;

// bits, hex, group, variant, base_byte_count
#define OC_INFO_LIST(X) \
    X("0000 0000", 0x00, OC_TODO, 0, 1, 0) \
    X("0000 0001", 0x01, OC_TODO, 0, 1, 0) \
    X("0000 0010", 0x02, OC_TODO, 0, 1, 0) \
    X("0000 0011", 0x03, OC_TODO, 0, 1, 0) \
    X("0000 0100", 0x04, OC_TODO, 0, 1, 0) \
    X("0000 0101", 0x05, OC_TODO, 0, 1, 0) \
    X("0000 0110", 0x06, OC_TODO, 0, 1, 0) \
    X("0000 0111", 0x07, OC_TODO, 0, 1, 0) \
    X("0000 1000", 0x08, OC_TODO, 0, 1, 0) \
    X("0000 1001", 0x09, OC_TODO, 0, 1, 0) \
    X("0000 1010", 0x0a, OC_TODO, 0, 1, 0) \
    X("0000 1011", 0x0b, OC_TODO, 0, 1, 0) \
    X("0000 1100", 0x0c, OC_TODO, 0, 1, 0) \
    X("0000 1101", 0x0d, OC_TODO, 0, 1, 0) \
    X("0000 1110", 0x0e, OC_TODO, 0, 1, 0) \
    X("0000 1111", 0x0f, OC_TODO, 0, 1, 0) \
    X("0001 0000", 0x10, OC_TODO, 0, 1, 0) \
    X("0001 0001", 0x11, OC_TODO, 0, 1, 0) \
    X("0001 0010", 0x12, OC_TODO, 0, 1, 0) \
    X("0001 0011", 0x13, OC_TODO, 0, 1, 0) \
    X("0001 0100", 0x14, OC_TODO, 0, 1, 0) \
    X("0001 0101", 0x15, OC_TODO, 0, 1, 0) \
    X("0001 0110", 0x16, OC_TODO, 0, 1, 0) \
    X("0001 0111", 0x17, OC_TODO, 0, 1, 0) \
    X("0001 1000", 0x18, OC_TODO, 0, 1, 0) \
    X("0001 1001", 0x19, OC_TODO, 0, 1, 0) \
    X("0001 1010", 0x1a, OC_TODO, 0, 1, 0) \
    X("0001 1011", 0x1b, OC_TODO, 0, 1, 0) \
    X("0001 1100", 0x1c, OC_TODO, 0, 1, 0) \
    X("0001 1101", 0x1d, OC_TODO, 0, 1, 0) \
    X("0001 1110", 0x1e, OC_TODO, 0, 1, 0) \
    X("0001 1111", 0x1f, OC_TODO, 0, 1, 0) \
    X("0010 0000", 0x20, OC_TODO, 0, 1, 0) \
    X("0010 0001", 0x21, OC_TODO, 0, 1, 0) \
    X("0010 0010", 0x22, OC_TODO, 0, 1, 0) \
    X("0010 0011", 0x23, OC_TODO, 0, 1, 0) \
    X("0010 0100", 0x24, OC_TODO, 0, 1, 0) \
    X("0010 0101", 0x25, OC_TODO, 0, 1, 0) \
    X("0010 0110", 0x26, OC_TODO, 0, 1, 0) \
    X("0010 0111", 0x27, OC_TODO, 0, 1, 0) \
    X("0010 1000", 0x28, OC_TODO, 0, 1, 0) \
    X("0010 1001", 0x29, OC_TODO, 0, 1, 0) \
    X("0010 1010", 0x2a, OC_TODO, 0, 1, 0) \
    X("0010 1011", 0x2b, OC_TODO, 0, 1, 0) \
    X("0010 1100", 0x2c, OC_TODO, 0, 1, 0) \
    X("0010 1101", 0x2d, OC_TODO, 0, 1, 0) \
    X("0010 1110", 0x2e, OC_TODO, 0, 1, 0) \
    X("0010 1111", 0x2f, OC_TODO, 0, 1, 0) \
    X("0011 0000", 0x30, OC_TODO, 0, 1, 0) \
    X("0011 0001", 0x31, OC_TODO, 0, 1, 0) \
    X("0011 0010", 0x32, OC_TODO, 0, 1, 0) \
    X("0011 0011", 0x33, OC_TODO, 0, 1, 0) \
    X("0011 0100", 0x34, OC_TODO, 0, 1, 0) \
    X("0011 0101", 0x35, OC_TODO, 0, 1, 0) \
    X("0011 0110", 0x36, OC_TODO, 0, 1, 0) \
    X("0011 0111", 0x37, OC_TODO, 0, 1, 0) \
    X("0011 1000", 0x38, OC_TODO, 0, 1, 0) \
    X("0011 1001", 0x39, OC_TODO, 0, 1, 0) \
    X("0011 1010", 0x3a, OC_TODO, 0, 1, 0) \
    X("0011 1011", 0x3b, OC_TODO, 0, 1, 0) \
    X("0011 1100", 0x3c, OC_TODO, 0, 1, 0) \
    X("0011 1101", 0x3d, OC_TODO, 0, 1, 0) \
    X("0011 1110", 0x3e, OC_TODO, 0, 1, 0) \
    X("0011 1111", 0x3f, OC_TODO, 0, 1, 0) \
    X("0100 0000", 0x40, OC_TODO, 0, 1, 0) \
    X("0100 0001", 0x41, OC_TODO, 0, 1, 0) \
    X("0100 0010", 0x42, OC_TODO, 0, 1, 0) \
    X("0100 0011", 0x43, OC_TODO, 0, 1, 0) \
    X("0100 0100", 0x44, OC_TODO, 0, 1, 0) \
    X("0100 0101", 0x45, OC_TODO, 0, 1, 0) \
    X("0100 0110", 0x46, OC_TODO, 0, 1, 0) \
    X("0100 0111", 0x47, OC_TODO, 0, 1, 0) \
    X("0100 1000", 0x48, OC_TODO, 0, 1, 0) \
    X("0100 1001", 0x49, OC_TODO, 0, 1, 0) \
    X("0100 1010", 0x4a, OC_TODO, 0, 1, 0) \
    X("0100 1011", 0x4b, OC_TODO, 0, 1, 0) \
    X("0100 1100", 0x4c, OC_TODO, 0, 1, 0) \
    X("0100 1101", 0x4d, OC_TODO, 0, 1, 0) \
    X("0100 1110", 0x4e, OC_TODO, 0, 1, 0) \
    X("0100 1111", 0x4f, OC_TODO, 0, 1, 0) \
    X("0101 0000", 0x50, OC_TODO, 0, 1, 0) \
    X("0101 0001", 0x51, OC_TODO, 0, 1, 0) \
    X("0101 0010", 0x52, OC_TODO, 0, 1, 0) \
    X("0101 0011", 0x53, OC_TODO, 0, 1, 0) \
    X("0101 0100", 0x54, OC_TODO, 0, 1, 0) \
    X("0101 0101", 0x55, OC_TODO, 0, 1, 0) \
    X("0101 0110", 0x56, OC_TODO, 0, 1, 0) \
    X("0101 0111", 0x57, OC_TODO, 0, 1, 0) \
    X("0101 1000", 0x58, OC_TODO, 0, 1, 0) \
    X("0101 1001", 0x59, OC_TODO, 0, 1, 0) \
    X("0101 1010", 0x5a, OC_TODO, 0, 1, 0) \
    X("0101 1011", 0x5b, OC_TODO, 0, 1, 0) \
    X("0101 1100", 0x5c, OC_TODO, 0, 1, 0) \
    X("0101 1101", 0x5d, OC_TODO, 0, 1, 0) \
    X("0101 1110", 0x5e, OC_TODO, 0, 1, 0) \
    X("0101 1111", 0x5f, OC_TODO, 0, 1, 0) \
    X("0110 0000", 0x60, OC_TODO, 0, 1, 0) \
    X("0110 0001", 0x61, OC_TODO, 0, 1, 0) \
    X("0110 0010", 0x62, OC_TODO, 0, 1, 0) \
    X("0110 0011", 0x63, OC_TODO, 0, 1, 0) \
    X("0110 0100", 0x64, OC_TODO, 0, 1, 0) \
    X("0110 0101", 0x65, OC_TODO, 0, 1, 0) \
    X("0110 0110", 0x66, OC_TODO, 0, 1, 0) \
    X("0110 0111", 0x67, OC_TODO, 0, 1, 0) \
    X("0110 1000", 0x68, OC_TODO, 0, 1, 0) \
    X("0110 1001", 0x69, OC_TODO, 0, 1, 0) \
    X("0110 1010", 0x6a, OC_TODO, 0, 1, 0) \
    X("0110 1011", 0x6b, OC_TODO, 0, 1, 0) \
    X("0110 1100", 0x6c, OC_TODO, 0, 1, 0) \
    X("0110 1101", 0x6d, OC_TODO, 0, 1, 0) \
    X("0110 1110", 0x6e, OC_TODO, 0, 1, 0) \
    X("0110 1111", 0x6f, OC_TODO, 0, 1, 0) \
    X("0111 0000", 0x70, OC_TODO, 0, 1, 0) \
    X("0111 0001", 0x71, OC_TODO, 0, 1, 0) \
    X("0111 0010", 0x72, OC_TODO, 0, 1, 0) \
    X("0111 0011", 0x73, OC_TODO, 0, 1, 0) \
    X("0111 0100", 0x74, OC_TODO, 0, 1, 0) \
    X("0111 0101", 0x75, OC_TODO, 0, 1, 0) \
    X("0111 0110", 0x76, OC_TODO, 0, 1, 0) \
    X("0111 0111", 0x77, OC_TODO, 0, 1, 0) \
    X("0111 1000", 0x78, OC_TODO, 0, 1, 0) \
    X("0111 1001", 0x79, OC_TODO, 0, 1, 0) \
    X("0111 1010", 0x7a, OC_TODO, 0, 1, 0) \
    X("0111 1011", 0x7b, OC_TODO, 0, 1, 0) \
    X("0111 1100", 0x7c, OC_TODO, 0, 1, 0) \
    X("0111 1101", 0x7d, OC_TODO, 0, 1, 0) \
    X("0111 1110", 0x7e, OC_TODO, 0, 1, 0) \
    X("0111 1111", 0x7f, OC_TODO, 0, 1, 0) \
    X("1000 0000", 0x80, OC_TODO, 0, 1, 0) \
    X("1000 0001", 0x81, OC_TODO, 0, 1, 0) \
    X("1000 0010", 0x82, OC_TODO, 0, 1, 0) \
    X("1000 0011", 0x83, OC_TODO, 0, 1, 0) \
    X("1000 0100", 0x84, OC_TODO, 0, 1, 0) \
    X("1000 0101", 0x85, OC_TODO, 0, 1, 0) \
    X("1000 0110", 0x86, OC_TODO, 0, 1, 0) \
    X("1000 0111", 0x87, OC_TODO, 0, 1, 0) \
    X("1000 1000", 0x88, OC_MOV, OCV_MOV_RM_TF_R, 2, 0) \
    X("1000 1001", 0x89, OC_MOV, OCV_MOV_RM_TF_R, 2, OCF_W) \
    X("1000 1010", 0x8a, OC_MOV, OCV_MOV_RM_TF_R, 2, OCF_D) \
    X("1000 1011", 0x8b, OC_MOV, OCV_MOV_RM_TF_R, 2, OCF_D|OCF_W) \
    X("1000 1100", 0x8c, OC_TODO, 0, 1, 0) \
    X("1000 1101", 0x8d, OC_TODO, 0, 1, 0) \
    X("1000 1110", 0x8e, OC_TODO, 0, 1, 0) \
    X("1000 1111", 0x8f, OC_TODO, 0, 1, 0) \
    X("1001 0000", 0x90, OC_TODO, 0, 1, 0) \
    X("1001 0001", 0x91, OC_TODO, 0, 1, 0) \
    X("1001 0010", 0x92, OC_TODO, 0, 1, 0) \
    X("1001 0011", 0x93, OC_TODO, 0, 1, 0) \
    X("1001 0100", 0x94, OC_TODO, 0, 1, 0) \
    X("1001 0101", 0x95, OC_TODO, 0, 1, 0) \
    X("1001 0110", 0x96, OC_TODO, 0, 1, 0) \
    X("1001 0111", 0x97, OC_TODO, 0, 1, 0) \
    X("1001 1000", 0x98, OC_TODO, 0, 1, 0) \
    X("1001 1001", 0x99, OC_TODO, 0, 1, 0) \
    X("1001 1010", 0x9a, OC_TODO, 0, 1, 0) \
    X("1001 1011", 0x9b, OC_TODO, 0, 1, 0) \
    X("1001 1100", 0x9c, OC_TODO, 0, 1, 0) \
    X("1001 1101", 0x9d, OC_TODO, 0, 1, 0) \
    X("1001 1110", 0x9e, OC_TODO, 0, 1, 0) \
    X("1001 1111", 0x9f, OC_TODO, 0, 1, 0) \
    X("1010 0000", 0xa0, OC_TODO, 0, 1, 0) \
    X("1010 0001", 0xa1, OC_TODO, 0, 1, 0) \
    X("1010 0010", 0xa2, OC_TODO, 0, 1, 0) \
    X("1010 0011", 0xa3, OC_TODO, 0, 1, 0) \
    X("1010 0100", 0xa4, OC_TODO, 0, 1, 0) \
    X("1010 0101", 0xa5, OC_TODO, 0, 1, 0) \
    X("1010 0110", 0xa6, OC_TODO, 0, 1, 0) \
    X("1010 0111", 0xa7, OC_TODO, 0, 1, 0) \
    X("1010 1000", 0xa8, OC_TODO, 0, 1, 0) \
    X("1010 1001", 0xa9, OC_TODO, 0, 1, 0) \
    X("1010 1010", 0xaa, OC_TODO, 0, 1, 0) \
    X("1010 1011", 0xab, OC_TODO, 0, 1, 0) \
    X("1010 1100", 0xac, OC_TODO, 0, 1, 0) \
    X("1010 1101", 0xad, OC_TODO, 0, 1, 0) \
    X("1010 1110", 0xae, OC_TODO, 0, 1, 0) \
    X("1010 1111", 0xaf, OC_TODO, 0, 1, 0) \
    X("1011 0000", 0xb0, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X("1011 0001", 0xb1, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X("1011 0010", 0xb2, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X("1011 0011", 0xb3, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X("1011 0100", 0xb4, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X("1011 0101", 0xb5, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X("1011 0110", 0xb6, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X("1011 0111", 0xb7, OC_MOV, OCV_MOV_IMM_T_R, 2, 0) \
    X("1011 1000", 0xb8, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X("1011 1001", 0xb9, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X("1011 1010", 0xba, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X("1011 1011", 0xbb, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X("1011 1100", 0xbc, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X("1011 1101", 0xbd, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X("1011 1110", 0xbe, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X("1011 1111", 0xbf, OC_MOV, OCV_MOV_IMM_T_R, 3, OCF_W) \
    X("1100 0000", 0xc0, OC_TODO, 0, 1, 0) \
    X("1100 0001", 0xc1, OC_TODO, 0, 1, 0) \
    X("1100 0010", 0xc2, OC_TODO, 0, 1, 0) \
    X("1100 0011", 0xc3, OC_TODO, 0, 1, 0) \
    X("1100 0100", 0xc4, OC_TODO, 0, 1, 0) \
    X("1100 0101", 0xc5, OC_TODO, 0, 1, 0) \
    X("1100 0110", 0xc6, OC_TODO, 0, 1, 0) \
    X("1100 0111", 0xc7, OC_TODO, 0, 1, 0) \
    X("1100 1000", 0xc8, OC_TODO, 0, 1, 0) \
    X("1100 1001", 0xc9, OC_TODO, 0, 1, 0) \
    X("1100 1010", 0xca, OC_TODO, 0, 1, 0) \
    X("1100 1011", 0xcb, OC_TODO, 0, 1, 0) \
    X("1100 1100", 0xcc, OC_TODO, 0, 1, 0) \
    X("1100 1101", 0xcd, OC_TODO, 0, 1, 0) \
    X("1100 1110", 0xce, OC_TODO, 0, 1, 0) \
    X("1100 1111", 0xcf, OC_TODO, 0, 1, 0) \
    X("1101 0000", 0xd0, OC_TODO, 0, 1, 0) \
    X("1101 0001", 0xd1, OC_TODO, 0, 1, 0) \
    X("1101 0010", 0xd2, OC_TODO, 0, 1, 0) \
    X("1101 0011", 0xd3, OC_TODO, 0, 1, 0) \
    X("1101 0100", 0xd4, OC_TODO, 0, 1, 0) \
    X("1101 0101", 0xd5, OC_TODO, 0, 1, 0) \
    X("1101 0110", 0xd6, OC_TODO, 0, 1, 0) \
    X("1101 0111", 0xd7, OC_TODO, 0, 1, 0) \
    X("1101 1000", 0xd8, OC_TODO, 0, 1, 0) \
    X("1101 1001", 0xd9, OC_TODO, 0, 1, 0) \
    X("1101 1010", 0xda, OC_TODO, 0, 1, 0) \
    X("1101 1011", 0xdb, OC_TODO, 0, 1, 0) \
    X("1101 1100", 0xdc, OC_TODO, 0, 1, 0) \
    X("1101 1101", 0xdd, OC_TODO, 0, 1, 0) \
    X("1101 1110", 0xde, OC_TODO, 0, 1, 0) \
    X("1101 1111", 0xdf, OC_TODO, 0, 1, 0) \
    X("1110 0000", 0xe0, OC_TODO, 0, 1, 0) \
    X("1110 0001", 0xe1, OC_TODO, 0, 1, 0) \
    X("1110 0010", 0xe2, OC_TODO, 0, 1, 0) \
    X("1110 0011", 0xe3, OC_TODO, 0, 1, 0) \
    X("1110 0100", 0xe4, OC_TODO, 0, 1, 0) \
    X("1110 0101", 0xe5, OC_TODO, 0, 1, 0) \
    X("1110 0110", 0xe6, OC_TODO, 0, 1, 0) \
    X("1110 0111", 0xe7, OC_TODO, 0, 1, 0) \
    X("1110 1000", 0xe8, OC_TODO, 0, 1, 0) \
    X("1110 1001", 0xe9, OC_TODO, 0, 1, 0) \
    X("1110 1010", 0xea, OC_TODO, 0, 1, 0) \
    X("1110 1011", 0xeb, OC_TODO, 0, 1, 0) \
    X("1110 1100", 0xec, OC_TODO, 0, 1, 0) \
    X("1110 1101", 0xed, OC_TODO, 0, 1, 0) \
    X("1110 1110", 0xee, OC_TODO, 0, 1, 0) \
    X("1110 1111", 0xef, OC_TODO, 0, 1, 0) \
    X("1111 0000", 0xf0, OC_TODO, 0, 1, 0) \
    X("1111 0001", 0xf1, OC_TODO, 0, 1, 0) \
    X("1111 0010", 0xf2, OC_TODO, 0, 1, 0) \
    X("1111 0011", 0xf3, OC_TODO, 0, 1, 0) \
    X("1111 0100", 0xf4, OC_TODO, 0, 1, 0) \
    X("1111 0101", 0xf5, OC_TODO, 0, 1, 0) \
    X("1111 0110", 0xf6, OC_TODO, 0, 1, 0) \
    X("1111 0111", 0xf7, OC_TODO, 0, 1, 0) \
    X("1111 1000", 0xf8, OC_TODO, 0, 1, 0) \
    X("1111 1001", 0xf9, OC_TODO, 0, 1, 0) \
    X("1111 1010", 0xfa, OC_TODO, 0, 1, 0) \
    X("1111 1011", 0xfb, OC_TODO, 0, 1, 0) \
    X("1111 1100", 0xfc, OC_TODO, 0, 1, 0) \
    X("1111 1101", 0xfd, OC_TODO, 0, 1, 0) \
    X("1111 1110", 0xfe, OC_TODO, 0, 1, 0) \
    X("1111 1111", 0xff, OC_TODO, 0, 1, 0) \
    /*end*/

#define BUILD_OC_TABLE(_, byte1, group, variant, minLength, flags) {group, variant, minLength, flags, 0, 0, 0, 0},

static OcInfo OcInfoFromByte1[256] = {
OC_INFO_LIST(BUILD_OC_TABLE)
};

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

            if (info.mode == 1) {
                info.immediate = at[info.length];
                info.length += 1;
            } else if (info.mode == 2 || (info.mode == 0 && info.regMem == 6)) {
                info.length += 2;
                info.immediate = (at[info.length-1]<<8) | at[info.length-2];
            }
        } break;

        // case (OC_MOV<<8)|OCV_MOV_IMM_T_RM: {
        // } break;

        case (OC_MOV<<8)|OCV_MOV_IMM_T_R: {
            info.reg = EXFIELD(at[0], 2, 0);
            info.immediate = at[1];
            if (info.flags & OCF_W) info.immediate |= at[2] << 8;
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

static const char *GetEffectiveAddressOperand(uint8_t mode, uint8_t regMem, uint16_t immediate)
{
    static char buf[512] = {0};
    assert(regMem < 8);
    assert(mode != 1 || immediate < 256);

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

    if (mode == 0) {
        if (regMem == 6) {
            snprintf(buf, sizeof buf, "[%d]", immediate);
        } else {
            snprintf(buf, sizeof buf, "[%s]", baseStrings[regMem]);
        }
    } else {
        snprintf(buf, sizeof buf, "[%s + %d]", baseStrings[regMem], immediate);
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
    uint8_t reg = info.reg;
    uint8_t regMem = info.regMem;
    const char *regName = GetRegName(w, reg);
    const char *regMemName = GetRegName(w, regMem);

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
                operandR = GetEffectiveAddressOperand(info.mode, info.regMem, info.immediate);
            }

            if (!d) {
                const char *tmp = operandL;
                operandL = operandR;
                operandR = tmp;
            }

            printf("mov %s, %s\n", operandL, operandR);
        } break;

        case (OC_MOV<<8)|OCV_MOV_IMM_T_R: {
            printf("mov %s, %u\n", regName, info.immediate);
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

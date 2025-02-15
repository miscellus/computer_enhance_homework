#!/usr/bin/env bash

set -xe

gcc -Wall -Wextra -pedantic -ggdb -O0 decode8086.c -o decode8086

decode_and_compare() {
  ./decode8086 "$1" > output.asm
  nasm output.asm -o output.bin
  cmp output.bin "$1"
}

# decode_and_compare ../listing_0037_single_register_mov
# decode_and_compare ../listing_0038_many_register_mov
decode_and_compare ../listing_0039_more_movs

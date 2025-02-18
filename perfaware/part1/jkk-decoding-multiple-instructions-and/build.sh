#!/usr/bin/env bash

set -e

gcc -Wall -Wextra -pedantic -ggdb -O0 decode8086.c -o decode8086.elf

decode_and_compare() {
  ./decode8086.elf "$1" > output.asm
  nasm output.asm -o output.bin
  cmp output.bin "$1"
}

decode_and_compare ../listing_0037_single_register_mov
decode_and_compare ../listing_0038_many_register_mov
decode_and_compare ../listing_0039_more_movs
decode_and_compare ../listing_0040_challenge_movs

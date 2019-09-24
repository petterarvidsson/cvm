#ifndef __CVM_H__
#define __CVM_H__

#include <stdint.h>

// ALU
#define ADD 0x00
#define SUB 0x01
#define MUL 0x02
#define DIV 0x03
#define MOD 0x04

// BRANCH
#define SET 0x10
#define SETN 0x11

// MEMORY
#define LOAD 0x20
#define CNT 0x21

typedef struct {
    uint16_t opcode;
    uint16_t in1;
    uint16_t in2;
    uint16_t out;
} instruction_t;

typedef struct {
    instruction_t *instructions;
    uint16_t size;
} instructions_t;

typedef struct {
    int32_t *data;
    uint16_t mask;
} memory_t;

typedef struct {
    memory_t memory;
    instructions_t instructions;
} program_t;

int32_t decode_program(program_t program);

#endif

#ifndef __OPCODES_H__
#define __OPCODES_H__

#define ADD 0x00
#define SUB 0x01
#define MUL 0x02
#define DIV 0x03
#define MOD 0x04

#define SET 0x10
#define SETN 0x11

#define LOAD 0x20
#define CNT 0x21

typedef struct {
    uint16_t opcode;
    uint16_t a;
    uint16_t b;
    uint16_t c;
} instruction_t;

typedef struct {
    uint32_t instructions;
    instruction_t *program;
    uint16_t stack_size;
} program_t;

typedef struct {
    int32_t *data;
    uint16_t size;
} memory_t;

#endif

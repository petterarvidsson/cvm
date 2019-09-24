#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <cvm.h>

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");

    uint32_t num_instructions;
    fread(&num_instructions, sizeof(uint32_t), 1, f);
    num_instructions = ntohl(num_instructions);
    instruction_t *instructions = (instruction_t *)malloc(sizeof(instruction_t) * num_instructions);
    fread(instructions, sizeof(instruction_t),  num_instructions, f);
    for(int i = 0; i < num_instructions; i++) {
        printf("READ: #%d [%d] in1=%d in2=%d out=%d\n", i, instructions[i].opcode, instructions[i].in1, instructions[i].in2, instructions[i].out);

        instructions[i].opcode = ntohs(instructions[i].opcode);
        instructions[i].in1 = ntohs(instructions[i].in1);
        instructions[i].in2 = ntohs(instructions[i].in2);
        instructions[i].out = ntohs(instructions[i].out);
        printf("TRANSFORMED: #%d [%d] in1=%d in2=%d out=%d\n", i, instructions[i].opcode, instructions[i].in1, instructions[i].in2, instructions[i].out);
    }
    uint16_t stack_size;
    fread(&stack_size, sizeof(uint16_t), 1, f);
    stack_size = htons(stack_size);
    fclose(f);

    printf("Instructions: %d\n", num_instructions);
    printf("Stack size: %d [%d]\n", stack_size, (1 << stack_size));

    int32_t *stack = (int32_t*)malloc(sizeof(int32_t) * (1 << stack_size));
    memory_t memory = {
        stack,
        ((uint32_t)0xFFFFFFFF) >> (32 - stack_size)
    };

    for(int i = 2; i < argc; i++) {
        int arg_num = i - 2;
        int arg = atoi(argv[i]);
        printf("Arguent[%d] = %d\n", arg_num, arg);
        stack[i - 2] = arg;
    }
    program_t program = {
        memory,
        {
            instructions,
            num_instructions
        }
    };

    if(decode_program(program) == 0) {
        printf("Result: %d\n", stack[argc - 2]);
    } else {
        printf("Program failed\n");
    }
}

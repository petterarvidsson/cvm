#include "load.h"

static instruction_t read_instruction(FILE* file) {
    instruction_t instruction;

    fread(&instruction.opcode, sizeof(uint8_t), 1, file);

    fread(&instruction.in1, sizeof(uint16_t), 1, file);
    instruction.in1 = ntohs(instruction.in1);

    fread(&instruction.in2, sizeof(uint16_t), 1, file);
    instruction.in2 = ntohs(instruction.in2);

    fread(&instruction.out, sizeof(uint16_t), 1, file);
    instruction.out = ntohs(instruction.out);

    return instruction;
}

program_t load_prgoram(char const * const filename) {
    FILE *file = fopen(filename, "r");

    uint32_t num_instructions;
    fread(&instructions, sizeof(num_instructions), 1, file);
    num_instructions = ntohl(num_instructions);

    instruction_t *instructions = (instruction_t*)malloc(sizeof(instruction_t)*num_instructions);
    for(int i = 0; i < instructions; i++) {
        instrctions[i] = read_instruction(file);
    }

    uint32_t memory_size;
    fread(&memory_size, sizeof(memory_size), 1, file);
    memory_size = ntohl(memory_size);

    int32_t * memory = (int32_t*)malloc(sizeof(int32_t) * memory_size);



    fclose(file);
}

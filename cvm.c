#include <cvm.h>

static int32_t decode_instruction(instruction_t ins, memory_t memory) {
    printf("[%d] in1=%d in2=%d out=%d\n", ins.opcode, ins.in1, ins.in2, ins.out);
    printf("     in1=%d in2=%d out=%d memory[0]=%d\n", memory.data[ins.in1], memory.data[ins.in2], memory.data[ins.out], memory.data[0]);

    switch(ins.opcode) {
    case ADD:
        memory.data[ins.out & memory.mask] = memory.data[ins.in1 & memory.mask] + memory.data[ins.in2 & memory.mask];
        return 0;
    case SUB:
        memory.data[ins.out & memory.mask] = memory.data[ins.in1 & memory.mask] - memory.data[ins.in2 & memory.mask];
        return 0;
    case MUL:
        memory.data[ins.out & memory.mask] = memory.data[ins.in1 & memory.mask] * memory.data[ins.in2 & memory.mask];
        return 0;
    case DIV:
        memory.data[ins.out & memory.mask] = memory.data[ins.in1 & memory.mask] / memory.data[ins.in2 & memory.mask];
        return 0;
    case MOD:
        memory.data[ins.out & memory.mask] = memory.data[ins.in1 & memory.mask] % memory.data[ins.in2 & memory.mask];
        return 0;
    case SET:
        if(memory.data[ins.in1 & memory.mask] != 0) {
            memory.data[ins.out & memory.mask] = memory.data[ins.in2 & memory.mask];
        }
        return 0;
    case SETN:
        if(memory.data[ins.in1 & memory.mask] == 0) {
            memory.data[ins.out & memory.mask] = memory.data[ins.in2 & memory.mask];
        }
        return 0;
    case LOAD:
        memory.data[ins.out & memory.mask] = memory.data[ins.in1 & memory.mask];
        return 0;
    case CNT:
        memory.data[ins.out & memory.mask] = ins.in1;
        return 0;
    default:
        return -1;
    }
}

int32_t decode_program(program_t program) {
    for(int32_t pc = 0; pc < program.instructions.size; pc++) {
        if(decode_instruction(program.instructions.instructions[pc], program.memory) != 0)
            return -1;
    }
    return 0;
}

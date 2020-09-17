#ifndef RUNNER_H
#define RUNNER_H

#include "memory.h"
#include "instructions.h"

class Runner
{
public:
    Runner() : num_mem(Memory<double>(0xFFFF)){}
    bool add_instruction(int instr);
    bool run_next();
    bool run_all();
    bool done() { return (!instructions.has_next()); }

    void x() {
        instructions.print();
    }

    static bool is_valid_instruction(int i);

private:
    instr_list_t instructions{};
    unsigned int program_counter = 0;

    Memory<double> num_mem{0xFFFF};

    double num_acc  = 0.0;
    bool   bool_acc = true;
};

#endif // RUNNER_H

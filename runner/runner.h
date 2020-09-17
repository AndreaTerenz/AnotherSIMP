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

    void print_instr_list() {
        std::cout<<"\n";
        instructions.print();
        std::cout<<"\n";
    }

private:
    instr_list_t instructions{};

    Memory<double> num_mem{0xFFFF};

    double num_acc  = 0.0;
    bool   bool_acc = true;
};

#endif // RUNNER_H

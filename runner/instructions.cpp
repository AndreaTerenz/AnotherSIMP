#include "instructions.h"

std::map<INSTRUCTION_CODE_T, unsigned short> args_per_op =
{
    {NUM_IN, 1},
    {NUM_OUT, 1},

    {LOAD, 1},
    {STORE, 1},

    {ADD, 1},
    {SUBTR, 1},
    {MULT, 1},
    {DIV, 1},

    {BRANCH, 1},
    {BRANCH_NEG, 1},
    {BRANCH_POS, 1},
    {BRANCH_ZERO, 1},
    {HALT, 0}
};

instruction_t* instr_list_t::next() {
    if (!has_next())
        return nullptr;
    else {
        instruction_t* output = new instruction_t(list.at(cursor));
        cursor++;
        return output;
    }
}

void instr_list_t::print() {
    std::cout<<"\nQUEUE :\n";
    for (int x = 0; x < size(); x++) {
        std::cout<<list.at(x).get_info()<<"\n";
    }
}

short instruction_t::get_arg(unsigned short a) {
    switch (a) {
    case 0: return arg0;
    case 1: return arg1;
    }

    return -1;
}

std::string instruction_t::get_info() {
    std::stringstream stream;
    stream << "op code:" << std::hex << code << "\t";
    stream << "args #:" << args_count << "\t";

    if (args_count == 1)
        stream << std::hex << "arg:" << arg0 << "\t";
    else if (args_count == 2)
        stream << std::hex << "args:[" << arg0 << "  " << arg1 << "]\t";

    return stream.str();
}

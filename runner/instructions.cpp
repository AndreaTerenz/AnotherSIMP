#include "instructions.h"

std::map<INSTRUCTION_CODE_T, instr_info_t> op_infos =
{
    {NUM_IN, {"NUM_IN", 1}},
    {NUM_OUT, {"NUM_OUT", 1}},

    {LOAD, {"LOAD", 1}},
    {STORE, {"STORE", 1}},

    {ADD, {"ADD", 1}},
    {SUBTR, {"SUBTR", 1}},
    {MULT, {"MULT", 1}},
    {DIV, {"DIV", 1}},

    {BRANCH, {"BRANCH", 1}},
    {BRANCH_NEG, {"BRANCH_NEG", 1}},
    {BRANCH_POS, {"BRANCH_POS", 1}},
    {BRANCH_ZERO, {"BRANCH_ZERO", 1}},
    {HALT, {"HALT", 0}}
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
    //std::cout<<"\nQUEUE :\n";

    for (unsigned int x = 0; x < size(); x++) {
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
    unsigned int count = info.get_args_count();
    stream << "op code:" << std::hex << code << " ("<<info.get_name()<<")\t";
    stream << "args #:" << count << "\t";

    if (info.get_args_count() == 1)
        stream << std::hex << "arg:" << arg0 << "\t";
    else if (count == 2)
        stream << std::hex << "args:[" << arg0 << "  " << arg1 << "]\t";

    return stream.str();
}

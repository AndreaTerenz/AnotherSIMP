#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>

enum INSTRUCTION_CODE_T {
    NUM_IN  = 0x00,
    NUM_OUT = 0x01,

    LOAD  = 0x10,
    STORE = 0x11,

    ADD   = 0x20,
    SUBTR = 0x21,
    MULT  = 0x22,
    DIV   = 0x23,

    BRANCH      = 0x30,
    BRANCH_NEG  = 0x31,
    BRANCH_POS  = 0x32,
    BRANCH_ZERO = 0x33,
    HALT        = 0x34
};
#define MAX_INSTR_CODE 0x34

extern std::map<INSTRUCTION_CODE_T, unsigned short> args_per_op;

struct instruction_t {
    instruction_t(INSTRUCTION_CODE_T c) : code(c), args_count(args_per_op[c]) { }
    instruction_t(instruction_t* other) :
        code(other->code), args_count(other->args_count),
        arg0(other->arg0), arg1(other->arg1) { }

    void set_args(short a0 = 0, short a1 = 0) { arg0 = a0; arg1 = a1; }

    INSTRUCTION_CODE_T get_code() { return code; }
    unsigned int get_args_count() { return args_count; }
    short get_arg(unsigned short a);
    std::string get_info();

private:
    INSTRUCTION_CODE_T code;
    unsigned int args_count;
    short arg0 = 0;
    short arg1 = 0;
};

struct instr_list_t {
    instr_list_t() : list(std::vector<instruction_t>()), cursor(0) {}

    bool has_next() { return !halt && cursor < list.size(); }
    unsigned int size() { return list.size(); }
    void enqueue (instruction_t* instr) { list.insert(list.end(), instr); }
    instruction_t* head() { return (has_next()) ? nullptr : &list.front(); }
    bool move_cursor_to(unsigned int pos) {
        if (pos < list.size()) cursor = pos;
        return pos < list.size();
    }
    instruction_t* next();
    bool halt = false;

    void print();

private:
    std::vector<instruction_t> list{};
    unsigned int cursor = 0;

};

#endif // INSTRUCTIONS_H
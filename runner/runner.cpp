#include "runner.h"

bool Runner::is_valid_instruction(int i) {
    if (i >= 0x0 && i <= 0xFFFFFF)
    {
        int op_code = (i & 0xFF0000) / 0x10000;

        switch (op_code) {
        case NUM_IN:
        case NUM_OUT:
        case LOAD:
        case STORE:
        case ADD:
        case SUBTR:
        case MULT:
        case DIV:
        case BRANCH:
        case BRANCH_NEG:
        case BRANCH_POS:
        case BRANCH_ZERO:
        case HALT : return true;
        }

    }
    return false;
}

bool Runner::add_instruction(int instr) {
    if (Runner::is_valid_instruction(instr)) {
        int op_code = (instr & 0xFF0000) / 0x10000;

        instruction_t instruction{static_cast<INSTRUCTION_CODE_T>(op_code)};

        switch (instruction.get_args_count()) {
            case 0: break; //instruction.set_args();
            case 1: {
                short a = instr & 0x00FFFF;
                instruction.set_args(a);
                break;
            }
            case 2: {
                short a1 = (instr & 0x00FF00) / 0x100;
                short a2 = (instr & 0x0000FF);
                instruction.set_args(a1, a2);
                break;
            }
        }

        instructions.enqueue(&instruction);

        return true;
    }

    return false;
}

bool Runner::run_all() {
    bool proceed = true;

    while (!done() && proceed){
        proceed = run_next();
    }

    return proceed;
}

bool Runner::run_next() {
    if (!done()) {
        instruction_t *next = instructions.next();

        switch (next->get_code()) {
        case NUM_IN: {
            short dest = next->get_arg(0);
            double val = 0.0;

            std::cout << " ? ";
            std::cin  >> val;

            if(!num_mem.set_value_at(val, dest)) {
                std::cout<<"\nGOOFED\n";
            }

            break;
        }
        case NUM_OUT: {
            short src = next->get_arg(0);
            double* val = num_mem.get_value_at(src);

            if (val != nullptr)
                std::cout << " > " << *val << "\n";
            else
                std::cout << "GOOFED\n";

            break;
        }

        case LOAD: {
            short src = next->get_arg(0);
            double* val = num_mem.get_value_at(src);

            if (val != nullptr)
                num_acc = *val;
            else
                std::cout << "GOOFED\n";

            break;
        }
        case STORE: {
            short dest = next->get_arg(0);

            if(!num_mem.set_value_at(num_acc, dest)) {
                std::cout<<"\nGOOFED\n";
            }

            break;
        }

        case ADD: {
            short src = next->get_arg(0);
            double* val = num_mem.get_value_at(src);

            if (val != nullptr)
                num_acc += *val;
            else
                std::cout << "GOOFED\n";

            break;
        }
        case SUBTR: {
            short src = next->get_arg(0);
            double* val = num_mem.get_value_at(src);

            if (val != nullptr)
                num_acc -= *val;
            else
                std::cout << "GOOFED\n";

            break;
        }
        case MULT: {
            short src = next->get_arg(0);
            double* val = num_mem.get_value_at(src);

            if (val != nullptr)
                num_acc *= *val;
            else
                std::cout << "GOOFED\n";

            break;
        }
        case DIV: {
            short src = next->get_arg(0);
            double* val = num_mem.get_value_at(src);

            if (val == nullptr)
                std::cout << "GOOFED\n";
            else if (val == 0)
                std::cout<<"ALSO GOOFED\n";
            else
                num_acc /= *val;

            break;
        }

        case BRANCH: {
            short pos = next->get_arg(0);
            instructions.move_cursor_to(pos);

            break;
        }
        case BRANCH_NEG: {
            if (num_acc < 0) {
                short pos = next->get_arg(0);
                instructions.move_cursor_to(pos);
            }

            break;
        }
        case BRANCH_POS: {
            if (num_acc > 0) {
                short pos = next->get_arg(0);
                instructions.move_cursor_to(pos);
            }

            break;
        }
        case BRANCH_ZERO: {
            if (num_acc == 0) {
                short pos = next->get_arg(0);
                instructions.move_cursor_to(pos);
            }

            break;
        }
        case HALT:
            std::cout<<"HALTED\n";
            instructions.halt = true;
            break;

        }
//      NOOOOOOOOOOOOT GOOD
        program_counter++;

        return true;
    }

    return false;
}

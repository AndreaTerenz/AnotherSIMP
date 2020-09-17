#include <iostream>
#include <vector>
#include <queue>
#include "runner/runner.h"

int main()
{
    //int latest = 0;
    Runner r{};
    bool halt_input = false;

    std::cout << "----SIMPLETRON----\n";

//    std::cout << "Input program instructions (-1 to terminate):\n\n";
//    #define INPUT_HALT "-1"
//    while (!halt_input) {
//        bool valid = true;

//        do {
//            std::string s = "";
//            std::cout << " > ";
//            std::cin >> s;

//            halt_input = (s == INPUT_HALT);

//            if (!halt_input) {
//                int latest = 0;
//                std::istringstream(s) >> std::hex >> latest;

//                valid = r.add_instruction(latest);

//                if (!valid) {
//                    std::cout << "GOOFED\n";
//                }
//            }
//        } while (!valid);
//    }

//    std::cout<<"\nInput completed - Program :\n";
    //r.print_instr_list();

        r.add_instruction(0x001000);  //input 1000
        r.add_instruction(0x001001);  //input 1001

        r.add_instruction(0x101000);  //load 1000 in acc
        r.add_instruction(0x211001);  //subtr 1001 to acc (acc = #1000-#1001)

        r.add_instruction(0x360003);  //branch by 3 if acc > 0
        r.add_instruction(0x350004);  //branch by 4 if acc < 0
        r.add_instruction(0x370004);  //branch by 4 if acc = 0

        r.add_instruction(0x011000);  //output 1000
        r.add_instruction(0x380000); //HALT

        r.add_instruction(0x011001);  //output 1001
        r.add_instruction(0x380000); //HALT

        r.add_instruction(0x380000); //HALT



    std::cout << "Executing...\n\n";




    r.run_all();

    return 0;
}

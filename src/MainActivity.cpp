#include "../include/MySimpleComputer.h"

void MySimpleComputer::runComputer()
{
    keys key{};
    setbuf(stdout, nullptr);
    int impulse = 1;
    sc_regSet(IGNORE_IMPULSE, 1);
    DrawAll();
    while (key != key_quit) {
        sc_regGet(IGNORE_IMPULSE, impulse);
        if (impulse == 1) {
            rk_readkey(key);
            switch (key) {
            case key_load: {
                std::string value;
                std::cout << "Load. File name + file extension: ";
                std::cin >> value;
                if (value.substr(value.length() - 3, 3) == "asm") {
                    translateASM(value);
                } else if (value.substr(value.length() - 3, 3) == "bas") {
                    translateBAS(value);
                } else if (value.substr(value.length() - 2, 2) == ".o") {
                    sc_memoryLoad(value);
                } else {
                    sc_memoryInit();
                    std::cout << "Incorrect file format!" << std::endl;
                    std::cout << "Press enter key to continue..." << std::endl;
                    std::cin.ignore(
                            std::numeric_limits<std::streamsize>::max(), '\n');
                    getchar();
                }
                sc_regInit();
                sc_accumulatorInit();
                instructionCounter = 0;
                sc_regSet(IGNORE_IMPULSE, 1);
                break;
            }
            case key_save: {
                std::string value;
                std::cout << "Saving. File name: ";
                std::cin >> value;
                sc_memorySave(value + ".o");
                break;
            }
            case key_reset:
                signal(SIGUSR1, stopHandler);
                raise(SIGUSR1);
                sc_memoryInit();
                sc_regInit();
                sc_accumulatorInit();
                sc_regSet(IGNORE_IMPULSE, 1);
                break;
            case key_up:
                if (selector / 10 == 0) {
                    selector += 90;
                } else {
                    selector -= 10;
                }
                break;
            case key_down:
                if (selector / 10 == 9) {
                    selector -= 90;
                } else {
                    selector += 10;
                }
                break;
            case key_left:
                if (selector == 0) {
                    selector = 99;
                } else {
                    --selector;
                }
                break;
            case key_right:
                if (selector == 99) {
                    selector = 0;
                } else {
                    ++selector;
                }
                break;
            case key_run:
                runEachMemory();
                break;
            case key_step:
                oneStep();
                break;
            case key_enter: {
                int value = 0;
                std::cout << "Value of memory: ";
                std::cin >> value;
                sc_memorySet(selector, value);
                break;
            }
            case key_f5: {
                int value = 0;
                std::cout << "Value of accumulator: ";
                std::cin >> value;
                sc_accumulatorSet(value);
                break;
            }
            case key_f6: {
                int value = 0;
                std::cout << "InstructionCounter position: ";
                std::cin >> value;
                sc_instructionCounterSet(value);
                break;
            }
            case key_quit:
                mt_clrscr();
                continue;
            case key_other:
                break;
            }
            DrawAll();
        }
    }
}
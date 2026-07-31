#include "register/registers.hpp"

int main() {
    Registers regs;
    regs.write(1, 10);
    regs.write(2, 20);
    regs.dump();
    return 0;
}

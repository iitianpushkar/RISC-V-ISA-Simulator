#include <iostream>
#include <array>

using namespace std;

class Registers {
private:
    array<uint32_t, 32> regs{};

public:
    int read(int index) {
        if (index == 0) return 0;
        return regs[index];
    }

    void write(int index, int value) {
        if (index == 0) return;
        regs[index] = value;
    }

    void dump() {
        for (int i = 0; i < 32; i++) {
            cout << "R" << i << ": " << read(i) << endl;
        }
    }
};

int main() {
    Registers regs;
    regs.write(1, 10);
    regs.write(2, 20);
    regs.dump();
    return 0;
}
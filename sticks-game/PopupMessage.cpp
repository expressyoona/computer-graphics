#include <iostream>
#include <windows.h>

int main(int argc, char const *argv[]) {
    // std::cout<<argv[1]<<std::endl;
    if (strcmp(argv[1], "win") == 0) {
        MessageBox(NULL, "You win!", "Congratulation", MB_OK);
    } else {
        MessageBox(NULL, "You lose!", "Game over", MB_OK);
    }
    return 0;
}

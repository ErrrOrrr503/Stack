#include <iostream>
#include <fstream>
#include "stack.h"

int main(int argc, char *argv[], char* envp[])
{
    Stack <int> Stack_int = {};
    Stack_int.init ();
    Stack <char> Stack_char = {};
    Stack_char.init ();
    Stack_int.push (5);
    Stack_char.push ('W');
    int a = 0;
    Stack_int.top (a);
    std::cout << a << std::endl;
    Stack_int.pop (a);
    std::cout << a << std::endl;
    char ch = 0;
    Stack_char.pop (ch);
    std::cout << ch << std::endl;

    for (int i = 0; i < 50; i++) {
        Stack_int.push (i);
    }
    Stack_int.fwrite ("Stack.txt");
    Stack_int.clean ();
    Stack_int.fwrite ("Stack_cleaned.txt");
    for (int i = 0; i < 10; i++) {
        if (Stack_int.pop (a) != STACK_UNDERFLOW)
            std::cout << a << std::endl;
    }
    Stack_int.destroy ();
    Stack_char.destroy ();
        logfile.close();
    return 0;
}

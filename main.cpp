#include <iostream>
#include <fstream>
#include "stack.h"

int main(int argc, char *argv[], char* envp[])
{
    Stack <int> Stack_int = {};
    Stack_construct (Stack_int);
    Stack <char> Stack_char = {};
    Stack_construct (Stack_char);
    Stack_push (Stack_int, 5);
    Stack_push (Stack_char, 'W');
    int a = 0;
    Stack_pop (Stack_int, a);
    std::cout << a << std::endl;
    char ch = 0;
    Stack_pop (Stack_char, ch);
    std::cout << ch << std::endl;

    for (int i = 0; i < 50; i++) {
        Stack_push (Stack_int, i);
    }

    Stack_destruct (Stack_int);
    Stack_destruct (Stack_char);
    return 0;
}

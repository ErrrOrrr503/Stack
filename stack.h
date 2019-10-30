#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#endif // STACK_H_INCLUDED
#include <cstring>

std::ofstream logfile ("log.txt");

const size_t CAP = 7;
const int OVERFLOW = 1;
const int UNDERFLOW = -1;
const int REALLOC_ERROR = 2;
const size_t REALLOC_LIMIT = 10;
const int CLEAN_ERROR = 3;
const int OPEN_FILE_ERROR = -1;

template <typename T>
struct Stack
{
    T *Data;
    size_t Size;
    size_t Capacity;
};

template <typename T>
void Stack_construct (Stack <T> &Stack);
template <typename T>
void Stack_destruct (Stack <T> &Stack);
template <typename T1, typename T2>
int Stack_push (Stack <T1> &Stack, T2 value);
template <typename T>
int Stack_realloc (Stack <T> &Stack);
template <typename T1, typename T2>
int Stack_pop (Stack <T1> &Stack, T2 &value);
template <typename T1, typename T2>
int Stack_top (Stack <T1> &Stack, T2 &value);
template <typename T>
int Stack_clean (Stack <T> &Stack);
template <typename T>
int Stack_clean_fast (Stack <T> &Stack);
template <typename T>
int Stack_fwrite (const char* File, Stack <T> &Stack);

#include "stack.cpp"

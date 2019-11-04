#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#endif // STACK_H_INCLUDED
#include <cstring>

std::ofstream logfile ("log.txt");

const size_t CAP = 7;
const int STACK_OVERFLOW = 11;
const int STACK_UNDERFLOW = -1;
const int STACK_SEG_FAULT = 1;
const int STACK_CAN_ERROR = 7;
const int STACK_REALLOC_ERROR = 2;
const size_t STACK_REALLOC_LIMIT = 10;
const int STACK_CLEAN_ERROR = 3;
const int STACK_UNID_ERROR = -666;
const int STACK_HASH_ERROR = -13;
const int OPEN_FILE_ERROR = -1;

template <typename T>
class Stack
{
    private:
        T *Data;
        char* Alloc_pointer;
        size_t Size;
        size_t Capacity;
        long long Hashsum;
        int Can1 = -13;
        int Can2 = -17;
        int OK ();
        long long Hash ();
        int realloc ();
    public:
        void init (); //deal with memory
        void destroy ();
        int clean ();

        int push (T value); //no-deal with memory
        int pop (T &value);
        int top (T &value);
        int clean_fast ();
        int fwrite (const char* File);
};

#include "stack.cpp"

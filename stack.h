#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#endif // STACK_H_INCLUDED
#include <cstring>
#include <cstdlib>
#include <ctime>

std::ofstream logfile ("log.txt");

const size_t CAP = 7;
const size_t STACK_REALLOC_LIMIT = 10;

template <typename T>
class Stack
{
    private:
        int Can_struct1 = -13;
        T *Data = NULL;
        char *Alloc_pointer = NULL;
        size_t Size = 0;
        long Can_struct_verify = 0;
        int Status = -1;
        size_t Capacity = 0;
        long long Hashsum = 0;
        int Can1 = -13;
        int Can2 = -17;
        int Can_struct2 = -17;


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
        int filewrite (const char* File);
        int hard_dump_struct (const char* File);
        int hard_dump_Data (const char* File);
        int errtell ();
};

#include "stack.cpp"

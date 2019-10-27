template <typename T>
void Stack_construct (Stack <T> &Stack)
{
    Stack.Data = new T[CAP];
    Stack.Size = 0;
    Stack.Capacity = CAP;
        logfile << "Construct...\n";
}

template <typename T>
void Stack_destruct (Stack <T> &Stack)
{
    delete[] Stack.Data;
    Stack.Size = 0;
    Stack.Capacity = 0;
        logfile << "destruct...well, ask valgrind about it IT IS NOT MY FUCKING DEAL!\n ";
}

template <typename T1, typename T2>
int Stack_push (Stack <T1> &Stack, T2 value)
{
    if (Stack.Size >= Stack.Capacity - 1)
        if (Stack_realloc (Stack) == REALLOC_ERROR)
            return OVERFLOW;
    Stack.Data[Stack.Size++] = value;
        logfile << "Pushing " << value << " & size = " << Stack.Size << std::endl;
    return 0;
}

template <typename T>
int Stack_realloc (Stack <T> &Stack)
{
    size_t New_Size = 0;
    if (Stack.Capacity >= REALLOC_LIMIT)
        New_Size = REALLOC_LIMIT + Stack.Capacity;
    else
        New_Size = 2 * Stack.Capacity;
    T *New_Data = new T[New_Size];
    if (New_Data == NULL)
        return REALLOC_ERROR;
    for (size_t i = 0; i < Stack.Capacity; i++)
        *(New_Data + i) = *(Stack.Data + i);
    delete[] Stack.Data;
    Stack.Data = New_Data;
    Stack.Capacity = New_Size;
        logfile << "Realloced to " << Stack.Capacity << std::endl;
    return 0;
}

template <typename T1, typename T2>
int Stack_pop (Stack <T1> &Stack, T2 &value)
{
        logfile << "popping...\n";
    if (Stack.Size <= 0)
        return UNDERFLOW;
    value = Stack.Data[--Stack.Size];
    return 0;
}

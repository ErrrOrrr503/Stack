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
        logfile << "destruct...well, ask valgrind about it IT IS NOT MY DEAL!\n";
}

template <typename T1, typename T2>
int Stack_push (Stack <T1> &Stack, T2 value)
{
    if (Stack.Size >= Stack.Capacity - 1)
        if (Stack_realloc (Stack) == REALLOC_ERROR) {
                logfile << "ERROR OVERFLOW at <" << typeid(T1).name() << "> Stack!\n";
            return OVERFLOW;
        }
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
    if (New_Data == NULL) {
            logfile << "ERROR REALLOCING at <" << typeid(T).name() << "> Stack!\n";
        return REALLOC_ERROR;
    }
    std::memcpy (New_Data, Stack.Data, Stack.Capacity * sizeof (T));
    delete[] Stack.Data;
    Stack.Data = New_Data;
    Stack.Capacity = New_Size;
        logfile << "Realloced to " << Stack.Capacity << std::endl;
    return 0;
}

template <typename T1, typename T2>
int Stack_pop (Stack <T1> &Stack, T2 &value)
{
    if (Stack.Size <= 0) {
            logfile << "ERROR UNDERFLOW at <" << typeid(T1).name() << "> Stack by Stack_pop()!\n";
        return UNDERFLOW;
    }
    value = Stack.Data[--Stack.Size];
        logfile << "Popping " << value << " & size = " << Stack.Size << std::endl;
    return 0;
}

template <typename T1, typename T2>
int Stack_top (Stack <T1> &Stack, T2 &value)
{
    if (Stack.Size <= 0) {
            logfile << "ERROR UNDERFLOW at <" << typeid(T1).name() << "> Stack by Stack_top()!\n";
        return UNDERFLOW;
    }
    value = Stack.Data[Stack.Size - 1];
        logfile << "Topping " << value << " & size = " << Stack.Size << std::endl;
    return 0;
}

template <typename T>
int Stack_clean (Stack <T> &Stack)
{
    delete[] Stack.Data;
    Stack.Size = 0;
    Stack.Data = new T[CAP];
    if (Stack.Data == NULL) {
            logfile << "ERROR while cleaning in Stack_clean!\n";
        return CLEAN_ERROR;
    }
    Stack.Capacity = CAP;
        logfile << "Cleaned...\n";
    return 0;
}

template <typename T>
int Stack_clean_fast (Stack <T> &Stack)
{
    Stack.Size = 0;
    logfile << "fast-cleaned\n";
    return 0;
}

template <typename T>
int Stack_fwrite (const char* File, Stack <T> &Stack)
{
    std::ofstream Stack_out (File);
    if (!Stack_out) {
        return OPEN_FILE_ERROR;
            logfile << "ERROR opening file in Stack_fwrite\n";
    }
    Stack_out << "Stack.Size = " << Stack.Size << " Stack.Capacity = " << Stack.Capacity << "\n";
    for (size_t i = 0; i < Stack.Size; i++) {
        Stack_out << "[" << i << "/" << Stack.Size - 1 << "] = " << Stack.Data[i] << std::endl;
    }
        logfile << "Stack written successfilly\n";
    Stack_out.close();
    return 0;
}

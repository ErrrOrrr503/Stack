template <typename T>
void Stack<T>::init ()
{
    this->Alloc_pointer = new char[CAP * sizeof(T) + 2 * sizeof(int)];
    if (this->Alloc_pointer == NULL) {
            logfile << "ERROR INITING at Stack!\n";
    }
    this->Data = (T*) (this->Alloc_pointer + sizeof(int));
    *((int*) this->Alloc_pointer) = this->Can1; //setting Can1
    *((int*) (this->Data + CAP)) = this->Can2;  //setting Can2
    this->Can1 = *((int*) this->Alloc_pointer);
    this->Can2 = *((int*) (this->Data + CAP));
    this->Size = 0;
    this->Capacity = CAP;
    this->Hashsum = Stack<T>::Hash ();
        logfile << "INIT...\n";
}

template <typename T>
void Stack<T>::destroy ()
{
    int Err = this->OK ();
    if (Err) {
        logfile << "Trying to destroy corrupted stack, hope no devil`ll appear...\n";
    }
    delete[] this->Alloc_pointer;
    this->Size = 0;
    this->Capacity = 0;
    this->Hashsum = Stack<T>::Hash ();
        logfile << "Destroy...well, ask valgrind about it IT IS NOT MY DEAL!\n";
}

template <typename T>
int Stack<T>::realloc ()
{
    size_t New_Size = 0;
    if (this->Capacity >= STACK_REALLOC_LIMIT)
        New_Size = STACK_REALLOC_LIMIT + this->Capacity;
    else
        New_Size = 2 * this->Capacity;

    char* New_Alloc_pointer = new char[New_Size * sizeof(T) + 2 * sizeof(int)];
    if (New_Alloc_pointer == NULL) {
            logfile << "ERROR REALLOCING at Stack!\n";
        return STACK_REALLOC_ERROR;
    }
    T* New_Data = (T*) (New_Alloc_pointer + sizeof(int));

    std::memcpy (New_Data, this->Data, this->Capacity * sizeof (T));
    *((int*) New_Alloc_pointer) = this->Can1; //setting Can1
    *((int*) (New_Data + New_Size)) = this->Can2; //setting Can2
    delete[] this->Alloc_pointer;
    this->Alloc_pointer = New_Alloc_pointer;
    this->Data = New_Data;
    this->Capacity = New_Size;
    this->Hashsum = Stack<T>::Hash ();
        logfile << "Realloced to " << this->Capacity << std::endl;
    return 0;
}

template <typename T>
int Stack<T>::clean ()
{
    int Err = this->OK ();
    if (Err)
        return Err;
    this->destroy ();
    this->init ();
        logfile << "Cleaned...\n";
    return 0;
}

template <typename T>
int Stack<T>::push (T value)
{
    int Err = this->OK ();
    if (Err)
        return Err;
    if (this->Size > this->Capacity - 1)
        if (this->realloc () == STACK_REALLOC_ERROR) {
                logfile << "ERROR OVERFLOW at Stack!\n";
            return STACK_OVERFLOW;
        }
    this->Data[this->Size] = value;
    this->Size++;
    this->Hashsum = this->Hash ();
        logfile << "Pushing " << value << " & newsize = " << this->Size << std::endl;
    return 0;
}

template <typename T>
int Stack<T>::pop (T &value)
{
    int Err = this->OK ();
    if (Err)
        return Err;
    this->Size--;
    if (this->Size > this->Capacity - 1) {
            logfile << "ERROR UNDERFLOW at Stack by Stack_pop()!\n";
        this->Size++;
        return STACK_UNDERFLOW;
    }
    value = this->Data[this->Size];
    this->Hashsum = this->Hash ();
        logfile << "Popping " << value << " & size = " << this->Size << std::endl;
    return 0;
}

template <typename T>
int Stack<T>::top (T &value)
{
    int Err = this->OK ();
    if (Err)
        return Err;
    this->Size--;
    if (this->Size > this->Capacity - 1) {
            logfile << "ERROR UNDERFLOW at Stack by Stack_top()!\n";
        this->Size++;
        return STACK_UNDERFLOW;
    }
    value = this->Data[this->Size];
    this->Size++;
    this->Hashsum = this->Hash ();
        logfile << "Topping " << value << " & size = " << this->Size << std::endl;
    return 0;
}

template <typename T>
int Stack<T>::clean_fast ()
{
    int Err = this->OK ();
    if (Err)
        return Err;
    this->Size = 0;
    this->Hash = this->Hash ();
        logfile << "fast-cleaned\n";
    return 0;
}

template <typename T>
int Stack<T>::fwrite (const char* File)
{
    std::ofstream Stack_out (File);
    if (!Stack_out) {
        return OPEN_FILE_ERROR;
            logfile << "ERROR opening file in Stack_fwrite\n";
    }
    Stack_out << "Stack.Size = " << this->Size << " Stack.Capacity = " << this->Capacity << std::endl;
    Stack_out << "Stack.Can1_saved = " << this->Can1 << " Stack.Can2_saved = " << this->Can2 << std::endl;
    Stack_out << "Stack.Can1_real = " << *((int*) this->Alloc_pointer) << " Stack.Can2_real = " << *((int*) (this->Data + this->Capacity)) << std::endl;
    Stack_out <<"Stack.Hashsum = " << this->Hashsum << std::endl;
    for (size_t i = 0; i < this->Size; i++) {
        Stack_out << "[" << i << "/" << this->Size - 1 << "] = " << this->Data[i] << std::endl;
    }
        logfile << "Stack written successfilly\n";
    Stack_out.close();
    return 0;
}

template <typename T>
int Stack<T>::OK ()
{
    if (this->Can1 != *((int*) this->Alloc_pointer) || this->Can2 != *((int*) (this->Data + this->Capacity))) {
            logfile << "ERROR CANARY DEAD ⊗_⊗\n";
        return STACK_CAN_ERROR;
    }
    if (this->Hash () != this->Hashsum) {
            logfile << "ERROR HASH\n";
        return STACK_HASH_ERROR;
    }
    if (this->Size > this->Capacity) {
            logfile << "ERROR SEG FAULT\n";
        return STACK_SEG_FAULT;
    }
    return 0;
}

template <typename T>
long long Stack<T>::Hash ()
{
    return (this->Size * 666) % 13 + (93 * this->Can1 % this->Can2) + 2 * ((long long) this->Data % 3141) + 'I' * 's' * 'o' * 'L' * 'a' / 't' / 'o' / 'r' * (this->Capacity) % 7;
}

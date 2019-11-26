const int STACK_OVERFLOW_ERROR = 11; //function, not stack errors
const int STACK_UNDERFLOW_ERROR = 12;
const int STACK_REALLOC_ERROR = 2;
const int STACK_CLEAN_ERROR = 3;
const int OPEN_FILE_ERROR = -2;

const int STACK_SEG_FAULT_ERROR = 1; //Stack errors
const int STACK_CAN_struct_ERROR = 7;
const int STACK_CAN_Data_ERROR = 8;
const int STACK_UNID_ERROR = -666;
const int STACK_HASH_ERROR = -13;

const int READY = 0;
const int NOT_INIT = -1;

template <typename T>
void Stack<T>::init ()
{
    this->Alloc_pointer = new char[CAP * sizeof(T) + 2 * sizeof(int)];
    if (this->Alloc_pointer == NULL) {
            logfile << "ERROR INITING at Stack!\n";
    }
    this->Data = (T*) (this->Alloc_pointer + sizeof(int));
        //setting struct canaries
    srand (clock ());
    this->Can_struct1 = rand ();
    srand (clock ());
    this->Can_struct2 = rand ();
    this->Can_struct_verify = this->Can_struct1 + this->Can_struct2;
        //setting DATA canaries
    srand (clock ());
    this->Can1 = rand ();
    srand (clock ());
    this->Can2 = rand ();
    *((int*) this->Alloc_pointer) = this->Can1;
    *((int*) (this->Data + CAP)) = this->Can2;

    this->Size = 0;
    this->Capacity = CAP;
    this->Status = READY;
    this->Hashsum = this->Hash ();
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
    this->Status = NOT_INIT;
    this->Hashsum = this->Hash ();
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
    this->Hashsum = this->Hash ();
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
            return STACK_OVERFLOW_ERROR;
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
        return STACK_UNDERFLOW_ERROR;
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
        return STACK_UNDERFLOW_ERROR;
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
    this->Hashsum = this->Hash ();
        logfile << "fast-cleaned\n";
    return 0;
}

template <typename T>
int Stack<T>::filewrite (const char* File)
{
    std::ofstream Stack_out (File);
    if (!Stack_out) {
            logfile << "ERROR opening file in Stack_fwrite\n";
        return OPEN_FILE_ERROR;
    }
    Stack_out << "Stack.Data* =          " << (size_t) this->Data << std::endl << "Stack.Alloc_pointer* = " << (size_t) this->Alloc_pointer << std::endl;
    Stack_out << "Stack.Size =     " << this->Size << std::endl << "Stack.Capacity = " << this->Capacity << std::endl;
    Stack_out << "Stack.Can1_saved = " << this->Can1 << " Stack.Can2_saved = " << this->Can2 << std::endl;
    Stack_out << "Stack.Can1_real =  " << *((int*) this->Alloc_pointer) << " Stack.Can2_real =  " << *((int*) (this->Data + this->Capacity)) << std::endl;
    Stack_out << "Stack.Can_struct1 = " << this->Can_struct1 << " Stack.Can_struct2 = " << this->Can_struct2 << " Stack.Can_struct_verify = " << this->Can_struct_verify << std::endl;
    Stack_out << "Stack.Hashsum = " << this->Hashsum << std::endl;
    Stack_out << "Calc  Hashsum = " << this->Hash () << std::endl;
    for (size_t i = 0; i < this->Capacity; i++) {
        Stack_out << "[" << i << "/" << this->Capacity - 1 << "] = " << this->Data[i] << std::endl;
    }
        logfile << "Stack written successfilly) Is it that bad that you used me?\n";
    Stack_out.close();
    return 0;
}

template <typename T>
int Stack<T>::errtell ()
{
    switch (this->Status) {
        case READY:
            std::cout << "ALL GOOD, Stack is ready\n";
            break;
        case STACK_CAN_Data_ERROR:
            std::cout << "ERROR DATA CANARY DEAD ⊗_⊗\n";
            break;
        case STACK_CAN_struct_ERROR:
            std::cout << "ERROR STRUCT CANARY DEAD ⊗_⊗\n";
            break;
        case STACK_HASH_ERROR:
            std::cout << "ERROR HASH\n";
            break;
        case STACK_SEG_FAULT_ERROR:
            std::cout << "ERROR SEG FAULT\n";
        default:
            break;
    }
    return 0;
}

template <typename T>
int Stack<T>::hard_dump_struct (const char* File)
{
        logfile << "Started hard_dumping_struct, cheap & serious...\n";
    FILE* dump = NULL;
    dump = fopen (File, "wb");
    if (dump == NULL) {
            logfile << "ERROR even while hard_dumping, it seems the processor exploaded...\n";
        return OPEN_FILE_ERROR;
    }
    char *dump_buf = new char[sizeof (*this)];
    std::memcpy (dump_buf, this, sizeof (*this));
    fwrite (dump_buf, sizeof (char), sizeof (*this), dump);
    fclose (dump);
    return 0;
}

template <typename T>
int Stack<T>::hard_dump_Data (const char* File)
{
        logfile << "Started hard_dumping_data, cheap & serious...\n";
    FILE* dump = NULL;
    dump = fopen (File, "wb");
    if (dump == NULL) {
            logfile << "ERROR even while hard_dumping, be careful, your RAM must be burning right now...\n";
        return OPEN_FILE_ERROR;
    }
    char *dump_buf = new char[this->Capacity * sizeof (T) + 2 * sizeof (int)];
    std::memcpy (dump_buf, this->Alloc_pointer, this->Capacity * sizeof (T) + 2 * sizeof (int));
    fwrite (dump_buf, sizeof (char), this->Capacity * sizeof (T) + 2 * sizeof (int), dump);
    fclose (dump);
    return 0;
}

template <typename T>
int Stack<T>::OK ()
{
    if (this->Can1 != *((int*) this->Alloc_pointer) || this->Can2 != *((int*) (this->Data + this->Capacity))) {
            logfile << "ERROR DATA CANARY DEAD ⊗_⊗\n";
        this->Status = STACK_CAN_Data_ERROR;
        return STACK_CAN_Data_ERROR;
    }
    if (this->Can_struct1 + this->Can_struct2 != this->Can_struct_verify) {
            logfile << "ERROR STRUCT CANARY DEAD ⊗_⊗\n";
        this->Status = STACK_CAN_struct_ERROR;
        return STACK_CAN_struct_ERROR;
    }
    if (this->Hash () != this->Hashsum) {
            logfile << "ERROR HASH\n";
        this->Status = STACK_HASH_ERROR;
        return STACK_HASH_ERROR;
    }
    if (this->Size > this->Capacity) {
            logfile << "ERROR SEG FAULT\n";
        this->Status = STACK_SEG_FAULT_ERROR;
        return STACK_SEG_FAULT_ERROR;
    }
    return 0;
}

template <typename T>
long long Stack<T>::Hash ()
{
    long long Hashsum = 0;
    char *ptr = (char *) this;
    char *ptr_end = ptr + sizeof (*this);
    char *ptr_Hashsum = (char*) &(this->Hashsum);
    for (; ptr < ptr_Hashsum; ptr += 1) {
        Hashsum += (*ptr * 359 + 5193) % 3141;
    }
    ptr += sizeof (this->Hashsum);
    for (; ptr < ptr_end; ptr += 1) {
        Hashsum += (*ptr * 359 + 5193) % 3141;
    }
    return Hashsum;
}

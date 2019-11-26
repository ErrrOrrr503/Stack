stack with some safety features:

1)it is dynamic, default capacity is 7. Aggressive realloc (doubles the size) works until capacity is below realloc limit.
Othrewise (realloc limit) number of new elements is added to capacity.

2)uses templates that allow you to create any stack type you want

3)consists of stack.h & stack.cpp, in main.cpp an example of use is provided

4)every event is logging to log.txt

5)stack.cpp can be pre-compiled to avoid unexpected changes, so it contains all error codes to avoid changing them.


use:

1)use init() to create stack & destroy() to delete it.

2)you can use push() pop() top() clean() clean_fast() to operate with stack.


debugging:

1)you can use filewrite() to create a user-friendly dump.

2)hard_dump(struct/Data)() just copy a piece of memory, containing stack(structure/Data array) to file.

3)errtell() returns current stack state and explains errors.


protection:

1)canaries on strucrure and type-independed canaries on Data are used.

2)Hashsum is calculated by Hash() out of structure data, it is designed to be independed of number of variables in structure.

3)No hashsum on Data is used as it was considered to be too slow.

4)Hashsum and Canaries are always checked before operations with stack by OK()

For dumping "Hard_dump" and "fwrite" functions are used

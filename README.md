stack with some safety features:
it is dynamic, default capacity is 7. Aggressive realloc (doubles the size) works until capacity is below realloc limit. Othrewise [realloc limit] number of new elements is added to capacity.
uses templates that allow you to create any stack type you want
consists of stack.h & stack.cpp, in main.cpp an example of use is provided
every event is logging to log.txt
stack.cpp can be pre-compiled to avoid unexpected changes, so it contains all error codes to avoid changing them.

use:
use init() to create stack & destroy() to delete it.
you can use push() pop() top() clean() clean_fast() to operate with stack.

debugging:
you can use filewrite() to create a user-friendly dump.
hard_dump[struct/Data]() just copy a piece of memory, containing stack[structure/Data array] to file.
errtell() returns current stack state and explains errors.

protection:
canaries on strucrure and type-independed canaries on Data are used.
Hashsum is calculated by Hash() out of structure data, it is designed to be independed of number of variables in structure.
No hashsum on Data is used as it was considered to be too slow.
Hashsum and Canaries are always checked before operations with stack by OK()

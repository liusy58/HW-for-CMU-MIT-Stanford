### Lecture 06 Debugging Programs with GDB and memory leaks

### Lecture 07 Pointers, *, ** and ***

A pointer is an address in the memory


##### Passing a pointer to a function
Example 1: This example shows how to pass the address of a `char*` to assign a string to a location.
```C
char* s = NULL; 
/* this does not allocate memory for the string*/ 
allocate(&s, n); 
/*call the function to allocate memory of n bytes for s*/

int allocate(char** ptr, int n){ 
    if ((*ptr=malloc(n)) != NULL) 
        return 0;
    return 1; }
```
Example 2: This example shows how to pass the address of a char** to assign an array of char*’s to a location.

```C
char** s = NULL;
/* this does not allocate memory for the array of strings */ 
 allocate(&s, n);
/*call the function to allocate memory of for an array of char*’s */

int allocate(char*** ptr, int n){ 
    if ((*ptr=malloc(n*sizeof(char*))) != NULL) 
        return 0;
    return 1; 
}
```

Example 3: This example shows how to pass the address of a `char** ` to double the size of an array of length n.

```C
char** s = NULL; 
/* this does not allocates memory for the array of strings */

allocate(&s,n); 
/* allocate as defined in example 2. Now this allocates an array of n char’*s */

doubleArray(&s, n); 
/*call the function to double the size of the array */

int doubleArray(char*** ptr, int n){ 
    if ((*ptr=malloc(2*n*sizeof(char*))) != NULL) 
        return 0;
    return 1; 
}
```

Example 4:A function matrixAllocate that takes two integers, m and n and allocate an m by n block of memory.

```C
int matrixAllocate(int*** Mptr, int n, int m){ 
    *Mptr = (int**)malloc(m*sizeof(int*)); 
    int i=0; 
    for (i=0;i<m;i++) 
        (*Mptr)[i] = malloc(n*sizeof(int)); 
}
```

##### Run time errors
|Index|Reasons|
|-|-|
|A| dereference of uninitialized or otherwise invalid pointer|
|B| insufficient (or none) allocated storage for operation|
|C| storage used after free|
|D| allocation freed repeatedly|
|E| free of unallocated or potentially storage|
|F| free of stack space|
|G| return, directly or via argument, of pointer to local variable H) dereference of wrong type|
|I| assignment of incompatible types|
|J| program logic confuses pointer and referenced type|
|K| incorrect use of pointer arithmetic|
|L| array index out of bounds|

##### Memory Copy
`memcpy(void *dest,void *src,size_t n)`:The `memcpy( )` function copies n bytes from memory area src to memory area dest.**The memory areas should not overlap.**

`memmove(void *dest,void *src,size_t n)`:The `memmove( )` function copies n bytes from memory area src to memory area dest.**The memory areas can overlap.**

Example:
A:
|1|2|3|4|5|6|
|-|-|-|-|-|-|
`memmove(A+1,A,4*sizeof(int))`
|1|1|2|3|4|6|
|-|-|-|-|-|-|

### Recitation
`./a.out`:This command says to look in the current directory (.) and run a.out. Normally the system doesn't look in the current directory for executable programs unless you have "." in your PATH.


### Lecture 08 Dynamic Memory Allocation
|Function|Description|
|-|-|
|`void *calloc(size_t nmemb, size_t size);`|`calloc()` allocates memory for an array of nmemb elements of size bytes each and returns a pointer to the allocated memory. The memory is set to zero.|
|`void *malloc(size_t size);`|`malloc()`allocates size bytes and returns a pointer to the allocated memory. **The memory is not cleared.**|
|`void free(void *ptr);`|`free()` frees the memory space pointed to by ptr, which must have been returned by a previous call to malloc(), calloc() or realloc(). Otherwise, or if free(ptr) has already been called before, undefined behaviour occurs. If ptr is NULL, no operation is performed.|
|`void *realloc(void *ptr, size_t size);`|`realloc()` changes the size of the memory block pointed to by ptr to size bytes. The contents will be unchanged to the minimum of the old and new sizes; **newly allocated memory will be uninitialized.** If ptr is NULL, the call is equivalent to `malloc(size)`; if size is equal to `zero`, the call is equivalent to `free(ptr)`. Unless ptr is NULL, it must have been returned by an earlier call to `malloc()`, `calloc()` or `realloc()`.|

##### Memory Leaks
Memory leaks refer to memory that has been allocated by an application, but not properly released back once that memory is no longer needed.

**It is a good idea to assign NULL to a pointer that has been freed.**


We call variables that are assigned space through `malloc` or `calloc` **dynamic variables**.

`void*` ptr or can be specific like `int*`, `char*` etc.. The type (`int*`, `char*`..) determines how many bytes are dereferenced when the actual pointer is dereferenced.

### Lecture 09 C Structs and Linked Lists

Structs in C are used to package several data fields into one unit.

The amount of memory necessary to hold struct is not always the sum of the data sizes. It is possible that a padding may occur for word alignment.


##### Structs within BMP files

```C
typedef struct { 
    unsigned short int type; 
    /* BMP type identifier */ 
    unsigned int size; 
    /* size of the file in bytes*/ 
    unsigned short int reserved1, reserved2; unsigned int offset;
     /* starting address of the byte */ } HEADER;

The next 40 bytes are reserved for a structure as follows.

typedef struct { 
    unsigned int size; 
    /* Header size in bytes */ 
    int width,height; 
    /* Width and height in pixels */ 
    unsigned short int planes; 
    /* Number of color planes */ 
    unsigned short int bits; 
    /* Bits per pixel */ 
    unsigned int compression; 
    /* Compression type */ 
    unsigned int imagesize; 
    /* Image size in bytes */ 
    int xresolution,yresolution; 
    /* Pixels per meter */ 
    unsigned int ncolors; 
    /* Number of colors */ 
    unsigned int importantcolors; 
    /* Important colors */ } INFOHEADER;
```

### Lecture 11 Doubly Linked Lists & Array of Linked Lists

##### Doubly Linked Lists(DLL)

```C

typedef struct node { 
    void* data; 
    struct node* next; 
    struct node* prev; } node;
```

```C
head data = malloc(sizeof(int)); 
*((int*)(head data)) = 12;

head data = malloc(strlen(“guna”)+1); 
strcpy((char*)(headdata), “guna”);

```
###### Inserting to a Doubly Linked Lists
```C
newnode->next = current->next; 
current->next = newnode; 
newnode->prev = current; 
(newnode->next)->prev = newnode;
```
###### Deleting a Node from a Doubly Linked Lists

```C
node* N = current->prev;
N->next = current->next;
(N->next)->prev = N;
free(current);
```

##### An Array of Linked Lists

Suppose that a linked list needs to be created starting at `A[i]`. The first node can be created as follows.

```C
A[i] = (node*)malloc(sizeof(node)); 
// allocate memory for node 
A[i]->size = 10; 
A[i]->name = (char*)malloc(strlen(“guna”+1)); strcpy(A[i]->name, “guna\0”); 
A[i]->next = NULL;
```


### Lecture 12 Doubly Linked Lists(with Recursion)

A doubly linked list is a collection of objects linked together by references from one object to another object, both forward and backward.


### Lecture 14 Function Pointers

###### Functions with variable number of arguments

`printf` and `scanf` are two IO functions that take variable number of arguments.

```C
#include <stdarg.h> 
/* header for variable argument list */ 
int sum(int argcnt, …) /* argcnt supplies count of other args */ 
{   va_list ap; /* argument pointer */
    int ans = 0; 
    va_start(ap, argcnt);
     /* initialize ap */ 
     while (argcnt-- > 0) /* process all args */ 
        ans += va_arg(ap, int); 
    va_end(ap) ; 
        /* clean up before function returns */ return (ans); }
```

The `<stdarg.h>` is a macro library that contains a set of macros, which allows portable functions, that, accepts variable argument lists to be coded.

* `va_start()` This is a macro that is invoked to initialize ap, a pointer to argument list. This macro must be called to initialize the list before any calls to va_arg().
* `va_arg()` This macro returns the next argument in the list pointed to by ap. Each invocation of `va_arg()` modifies ap so that the values of successive arguments are returned in turn. The type parameter is the type the argument is expected to be. This is the type name specified such that the type of a pointer to an object that has the specified type can be obtained simply by suffixing a * to type. Different types can be mixed, but it is up to the routine to know what type of arguments are expected.
* `va_end()` This macro is used to clean up; it invalidates ap for use (unless `va_start()` is invoked again).


###### Introduction to Function Pointers

The syntax of function pointers can sometimes be confusing. So we can use a typedef statement to make things simpler.

`typedef <return_type> (* fpointer)(argument list);`

```C
int (*Convert(const char code)) (int, int) { 
    if (code = = ‘+’) 
        return &Sum; 
    if (code = = ‘-’) 
        return &Difference; }

=>

typedef int (*Ptr)(int,int);
Ptr Convert(const char code) { 
    if (code = = ‘+’) 
        return &Sum; 
    if (code = = ‘-’) 
        return &Difference; 
}

Use the Convert function as follows 
int main ( ) {  
    int (*ptr)(int,int); 
    /* or: Ptr ptr; if you have a typedef */
    ptr = Convert(‘+’);
    printf( “%d \n”, ptr(2,4)); }
```

###### Passing Function Pointers to a Another Function

###### Generic Functions

One of the major benefits of a function pointer is that it can be passed to another function as one of the arguments.


### Lecture 15 Generic Data Structures

we define a generic LIST_ELEM that can hold any data type as its data.

```C
typedef struct LIST_ELEM {
    void * data;
    struct LIST_ELEM } LIST_ELEM;
```

### Lecture 17 Introduction to Hashing

###### Finding a “good” hash Function


### Lecture 20-1 Regular Expressions

`ls *.c`

Lists all the files with c extension or

`ls ab*`

lists all file names that starts with ab in the current directory. These type of commands (ls,dir etc) work with windows, unix and most operating systems. That is, the command ls will look for files with a certain name patterns but are limited in ways we can describe patterns. The wild card (*) is typically used with many commands in unix. For example,

`cp *.c /afs/andrew.cmu.edu/course/15/123/handin/Lab6/guna`

copies all .c files in the current directory to the given directory




### Lec20-1 Regular Expressions

###### Text Processing Languages

###### Regular Expression Grammar



# Spring 2025 System Programming — Final Project

## Written Portion

### 1. Describe what happens to memory released by the OS with regard to virtual memory

<!-- The memory is returned to the process’s heap but is not necessarily released to the OS. Most implementations (like glibc's malloc) maintain an internal memory pool for efficiency. Freed memory is kept in this pool and reused for future malloc() calls. This means the virtual memory space still reserves that region, even though the memory is marked as available by the allocator.

For memory unmapped with munmap() or released through mmap() allocations: These memory regions are typically returned to the OS immediately. The virtual address space of the process is updated, and the pages may be marked as available for reuse by other processes.

Virtual memory refers to the address space visible to a process. When memory is freed, that virtual space may be released or remapped. However, the physical memory (RAM) backing those pages may not be released immediately. The operating system may hold onto it temporarily to optimize performance, especially if it anticipates that the memory may be reused soon.

Many OSes use lazy reclamation, meaning freed memory is not immediately zeroed or returned to the free list. Instead, it may be cached to reduce the overhead of future allocations. Background processes may zero these pages over time.

Example:

char *block = malloc(1024 * 1024); // allocate 1 MB
free(block); // block is now available to malloc again, but may not return to OS

void *mapped = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
munmap(mapped, 4096); // immediately returns memory back to the OS

-->

---

### 2. In a C program, why does `argv[argv]` return `NULL`?

REPLACE THIS CONTENT WITH YOUR ANSWER

---

### 3. When a system call is made the CPU changes from user mode to kernel mode. Why?

REPLACE THIS CONTENT WITH YOUR ANSWER

---

### 4. Explain the relationship between the return value of a system call and the global variable `errno`

REPLACE THIS CONTENT WITH YOUR ANSWER

---

### 5. Consider the following C program. The variables and functions get allocated to which memory segments? Write your answers in comments to the right of each item

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 128

char my_string[MAX];
char class_name[] = "System Programming";
int global_integer = 3;

void print_global() {
  printf("%d\n", global_integer);
}

int square(int x) {
  int result = x * x;

  return result;
}

int main (int argc, char *argv[]) {
  char *dynamic_memory;
  dynamic_memory = malloc(MAX);
  free(dynamic_memory);
  dynamic_memory = NULL;

  return 0;
}
```

---

### 6. Explain the difference between `malloc`, `calloc`, `realloc`

REPLACE THIS CONTENT WITH YOUR ANSWER

---

### 7. Explain the difference between `brk` and `sbrk`. Why is `malloc` a better option of `brk`, and `sbrk`?

REPLACE THIS CONTENT WITH YOUR ANSWER

---

### 8. Explain why a shadow password file is needed

REPLACE THIS CONTENT WITH YOUR ANSWER

---

### 9. What is the numeric equivalent of the `README.md` file’s permission bits below, and what is the command to give the file full access, across the board?

```sh
-rw-r--r-- 1  johnnythunders  staff  3476 May  1 11:57 README.md
```

REPLACE THIS CONTENT WITH YOUR ANSWER

---

### 10. What does `kill -9 1` do? Explain in detail

REPLACE THIS CONTENT WITH YOUR ANSWER

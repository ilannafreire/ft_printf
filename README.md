*This project has been created as part of the 42 curriculum by ifreire.*

# ft_printf

## Description

`ft_printf` is a C library that reimplements the standard `printf()` function from libc.
The goal is to understand how variadic functions work in C — functions that accept a variable number of arguments — and to reproduce the formatting and output behaviour of `printf()` from scratch, without using any of the original's internal buffer management.

The library is compiled as a static archive (`libftprintf.a`) and handles the following conversion specifiers:

| Specifier | Output |
|-----------|--------|
| `%c` | Single character |
| `%s` | String (prints `(null)` if pointer is NULL) |
| `%p` | Pointer address in hexadecimal (`0x...`), prints `(nil)` if NULL |
| `%d` | Signed decimal integer |
| `%i` | Signed integer in base 10 |
| `%u` | Unsigned decimal integer |
| `%x` | Hexadecimal integer, lowercase |
| `%X` | Hexadecimal integer, uppercase |
| `%%` | Literal percent sign |

## Algorithm and Data Structure

### Strategy: linear scan + dispatch

The format string is read **character by character** in a single pass (`while (format[i])`):

- If the character is **not** `%` → it is printed immediately with `ft_putchar`.
- If the character **is** `%` → the next character is read and passed to `handle_conversion()`, which dispatches to the correct handler using a chain of `if/else if`.

Each handler writes its output directly to **file descriptor 1** (stdout) via `write(2)` — no intermediate buffer is ever built. Each handler returns the number of characters it wrote, and those values are accumulated into `count`, which `ft_printf` returns at the end.

### Data structures

No dynamic data structures (lists, arrays, trees) are used. The only allocated memory is inside `ft_itoa()`, which produces a temporary string to print a signed integer — it is freed immediately after printing.

### Why this design?

- **`va_list` / `va_arg`**: The only way to access an unknown number of arguments at runtime. `va_start` initialises the list after the last named parameter; `va_arg` consumes one argument at a time with its type; `va_end` cleans up. This is the core mechanism the project is built around.
- **Direct `write` to stdout**: The subject explicitly forbids reimplementing `printf`'s internal buffering. Writing one character at a time via `ft_putchar_fd(c, 1)` satisfies this requirement cleanly.
- **Recursion for unsigned/hex printing**: `ft_putunsigned` and `ft_puthex` recurse on `n / base` until reaching a single digit, then print on the way back up — this naturally produces the correct left-to-right order without needing a temporary array or string reversal.
- **`ft_itoa` for signed integers**: Handling `INT_MIN` (-2147483648) manually requires casting through `long` to avoid undefined behaviour when negating. `ft_itoa` (from libft) already handles this correctly, so it is reused via the `Libft/` dependency.
- **Libft reuse**: The subject authorises libft. Four functions are included in `Libft/` — only those actually used: `ft_strlen`, `ft_itoa`, `ft_putchar_fd`, `ft_putstr_fd`. The rest were removed to keep the folder minimal and honest.
- **`static` for `handle_conversion`**: This function is an internal implementation detail of `ft_printf.c`. Marking it `static` prevents it from being visible outside that translation unit, which is correct encapsulation and avoids polluting the library's symbol table.

## Instructions

### Compilation

```bash
make
```

Compiles the `Libft/` sources first (via its own Makefile), then compiles `ft_printf.c` and `ft_printf_utils.c`, and finally merges all objects into `libftprintf.a` at the root of the repository using `ar rcs`.

### Makefile rules

| Rule | Action |
|------|--------|
| `make` / `make all` | Build `libftprintf.a` |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and `libftprintf.a` |
| `make re` | Full recompile from scratch |

### Using the library in another project

```bash
cc -Wall -Wextra -Werror your_file.c -L. -lftprintf -o your_program
```

```c
#include "ft_printf.h"

int main(void)
{
    int count;

    count = ft_printf("Name: %s | Number: %d | Hex: %x\n", "ifreire", 42, 255);
    ft_printf("Characters printed: %d\n", count);
    return (0);
}
```

Output:
```
Name: ifreire | Number: 42 | Hex: ff
Characters printed: 37
```

## Resources

- [Linux man page — printf(3)](https://man7.org/linux/man-pages/man3/printf.3.html) — Reference for the original `printf` behaviour and conversion specifiers.
- [Linux man page — stdarg(3)](https://man7.org/linux/man-pages/man3/stdarg.3.html) — Documentation for `va_list`, `va_start`, `va_arg`, `va_copy`, `va_end`.
- [Linux man page — write(2)](https://man7.org/linux/man-pages/man2/write.2.html) — Syscall used for all output in this project.
- [C Standard — ISO/IEC 9899:2011](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf) — C11 specification, covering variadic functions and integer type behaviour.
- [42 Norm](https://github.com/42School/norminette) — Code style rules enforced at 42.

### AI usage

AI (GitHub Copilot) was used in this project for:

- **README** — structure and writing, following the subject's requirements.


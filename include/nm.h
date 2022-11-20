#pragma once

#include <elf.h>
#include "../libft/include/libft.h"

typedef struct      s_symbol
{
    size_t          value;
    unsigned char   type;
    uint64_t        size;
    char            *name;
}                   t_symbol;

int handle_file(char *filename, char *data, size_t len);

int parse_32(char *filename, char *data, size_t len);
int parse_64(char *filename, char *data, size_t len);

void sort_symbols(t_symbol *symbols, size_t len);
void print_symbols(t_symbol *symbols, size_t len);

char get_symbol_type_32(Elf32_Sym symbol, Elf32_Shdr *sections, size_t shnum);
char get_symbol_type_64(Elf64_Sym symbol, Elf64_Shdr *sections, size_t shnum);


#include "nm.h"

char get_symbol_type_64(Elf64_Sym symbol, Elf64_Shdr *sections, size_t shnum) {
    uint8_t bind = ELF64_ST_BIND(symbol.st_info);
    uint8_t type = ELF64_ST_TYPE(symbol.st_info);

    if (bind >= STB_NUM) {
        return '?';
    }
    if (bind == STB_WEAK) {
        if (type == STT_OBJECT) {
            return symbol.st_shndx == SHN_UNDEF ? 'v' : 'V';
        }
        return symbol.st_shndx == SHN_UNDEF ? 'w' : 'W';
    }
    if (bind == STB_GNU_UNIQUE) {
        return 'u';
    }
    if (symbol.st_shndx == SHN_COMMON) {
        return 'C';
    }
    if (symbol.st_shndx == SHN_UNDEF) {
        return 'U';
    }
    if (symbol.st_shndx == SHN_MIPS_SCOMMON) {
        return bind == STB_GLOBAL ? 'G' : 'g';
    }
    if (symbol.st_shndx == SHN_MIPS_SUNDEFINED) {
        return bind == STB_GLOBAL ? 'S' : 's';
    }
    if (symbol.st_shndx == SHN_ABS || symbol.st_shndx >= shnum) {
        return 'A';
    }
    if (type == STT_GNU_IFUNC) {
        return 'i';
    }
    Elf64_Shdr *sctn = &sections[symbol.st_shndx];
    if (sctn->sh_type == SHT_GROUP) {
        return bind == STB_GLOBAL ? 'N' : 'n';
    }
    if (sctn->sh_type == SHT_X86_64_UNWIND) {
        return 'p';
    }
    if (sctn->sh_type == SHT_MIPS_DEBUG) {
        return ('-');
    }
    if (symbol.st_shndx < shnum && sctn->sh_type == SHT_NOBITS) {
        return bind == STB_GLOBAL ? 'B' : 'b';
    }
    if ((type == STT_NOTYPE || type == STT_OBJECT) && 
        sctn->sh_flags == SHF_WRITE + SHF_ALLOC) {
        return bind == STB_GLOBAL ? 'D' : 'd';
    }
    if (sctn->sh_type == SHT_PROGBITS && type == STT_FUNC &&
        sctn->sh_flags == SHF_ALLOC + SHF_EXECINSTR) {
        return bind == STB_GLOBAL ? 'T' : 't';
    }
    if ((sctn->sh_type == SHT_PROGBITS || sctn->sh_type == SHT_NOTE) &&
        sctn->sh_flags == SHF_ALLOC) {
        return bind == STB_GLOBAL ? 'R' : 'r';
    }
    return ('?');
}

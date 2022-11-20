#include "nm.h"

int parse_64(char *filename, char *data, size_t len) {
    Elf64_Ehdr *header = (Elf64_Ehdr*)data;

    // Symbols can't be found if the header describes 0 sections or
    // has a section offset of null
    if (!header->e_shnum || !header->e_shoff) {
        return (2);
    }

    // Check if the section header table entry size matches the size defined
    // in elf.h to avoid going out of bounds when looping through it later on
    if (header->e_shentsize != sizeof(Elf64_Shdr)) {
        return (2);
    }

    // Check if the file is long enough for all headers to exist
    if (header->e_shoff + sizeof(Elf64_Shdr) * header->e_shnum > len) {
        return (2);
    }

    Elf64_Shdr *sections = (Elf64_Shdr*)(data + header->e_shoff);
    Elf64_Shdr *symtab_hdr = NULL;
    uint32_t strtab_ndx = 0;

    for (int i = 0; i < header->e_shnum; i++) {
        // Check if the section goes out of bounds to detect corruption
        if (sections[i].sh_offset + sections[i].sh_size > len) {
            return (2);
        }
        // Account for an overflow occurring during incrementation
        if (sections[i].sh_offset + sections[i].sh_size < sections[i].sh_offset) {
            return (2);
        }

        if (sections[i].sh_type == SHT_SYMTAB) {
            // Check for double symtab headers and an incorrect strtab index
            // to detect corruption
            if (symtab_hdr || sections[i].sh_link >= header->e_shnum) {
                return (2);
            }

            symtab_hdr = &sections[i];
            strtab_ndx = sections[i].sh_link;

            // Check if the symbol entry size matches the size defined in elf.h
            // to avoid going out of bounds when looping through it later on
            if (symtab_hdr->sh_entsize != sizeof(Elf64_Sym)) {
                return (2);
            }
        }
    }
    if (!symtab_hdr || !symtab_hdr->sh_size) {
        return (1);
    }

    // An invalid string table index indicates a corrupt file
    if (header->e_shstrndx >= header->e_shnum || 
        header->e_shstrndx == SHN_UNDEF ||
        sections[header->e_shstrndx].sh_type != SHT_STRTAB) {
        ft_dprintf(STDERR_FILENO,
                    "nm: warning: %s has a corrupt string table index - ignoring\n",
                    filename);
        return (1);
    }

    char *strtab = (char*)(data + sections[strtab_ndx].sh_offset);
    Elf64_Sym *entries = (Elf64_Sym*)(data + symtab_hdr->sh_offset);
    size_t strtab_len = sections[strtab_ndx].sh_size;
    size_t valid_sym = 0;

    size_t total_sym = symtab_hdr->sh_size / sizeof(Elf64_Sym);
    t_symbol symbols[total_sym];

    // Starting at 1 because the first symbol should be empty in a valid ELF file
    for (size_t i = 1; i < total_sym; i++) {
        symbols[valid_sym].name = NULL;
        symbols[valid_sym].value = entries[i].st_value;
        symbols[valid_sym].size = entries[i].st_size;
        symbols[valid_sym].type = get_symbol_type_64(entries[i], sections, header->e_shnum);

        if (entries[i].st_name) {
            // Symtab must link to strtab, otherwise the section is corrupted
            if (sections[strtab_ndx].sh_type != SHT_STRTAB) {
                ft_dprintf(STDERR_FILENO, "nm: %s: attempt to load strings ", filename);
                ft_dprintf(STDERR_FILENO, "from a non-string section (number %d)\n", strtab_ndx);
            }
            // Strtab is invalid if the last byte is not null or if the size overflows
            // into the headers. Printing would result in random memory being shown
            else if (!strtab[strtab_len - 1] && strtab_len > 0 &&
                     sections[strtab_ndx].sh_offset + strtab_len <= header->e_shoff)
            {
                if (entries[i].st_name >= strtab_len) {
                    ft_dprintf(STDERR_FILENO,
                        "nm: %s: invalid string offset %u >= %u for section `.strtab'\n",
                        filename, entries[i].st_name, strtab_len);
                }
                else {
                    symbols[valid_sym].name = ft_strdup(strtab + entries[i].st_name);
                }
            }
        }
        // The real nm only displys symbols of these 2 types
        if (ELF64_ST_TYPE(entries[i].st_info) != STT_SECTION &&
            ELF64_ST_TYPE(entries[i].st_info) != STT_FILE) {
            // If the type is correct but the name isn't, the symbol should be printed as ""
            // instead of the default "(null)"
            if (!entries[i].st_name) {
                symbols[valid_sym].name = ft_strdup("");
            }
            valid_sym++;
        }
        else if (symbols[valid_sym].name) {
            free(symbols[valid_sym].name);
        }
    }
    if (!valid_sym) {
        return (1);
    }

    sort_symbols(symbols, valid_sym);
    print_symbols(symbols, valid_sym);

    for (size_t i = 0; i < valid_sym; i++) {
        if (symbols[i].name) {
            free(symbols[i].name);
        }
    }
    return (0);
}
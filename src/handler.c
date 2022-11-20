#include "nm.h"

int handle_file(char *filename, char *data, size_t len) {
    // Check the magic bytes to determine if file is in ELF format
    if (len <= EI_NIDENT || ft_strncmp(data, ELFMAG, SELFMAG)) {
        return (2);
    }

    // Check the file's data encoding to make sure the file can be processed correctly
    if (len < EI_DATA || !data[EI_DATA] || data[EI_DATA] >= ELFCLASSNUM) {
        return (2);
    }

    // Validate the file version to make sure it's compatible with the 
    // system's current ELF specification
    if (len < EI_VERSION || data[EI_VERSION] != EV_CURRENT) {
        return (2);
    }

    // Determine the file architecture to know which ELF header struct to use
    if (len >= EI_CLASS && data[EI_CLASS] == ELFCLASS32) {
        if (len < sizeof(Elf32_Ehdr)) {
            return (2);
        }
        return (parse_32(filename, data, len));
    }
    else if (len >= EI_CLASS && data[EI_CLASS] == ELFCLASS64) {
        if (len < sizeof(Elf64_Ehdr)) {
            return (2);
        }
        return (parse_64(filename, data, len));
    }
    else {
        return (2);
    }

    return (0);
}
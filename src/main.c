#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "nm.h"

int open_file(char *filename, struct stat *file) {
    int fd;

    if ((fd = open(filename, O_RDONLY)) < 0) {
        ft_dprintf(STDERR_FILENO, "nm: '%s': No such file\n", filename);
        return (-1);
    }
    if (fstat(fd, file) < 0) {
        ft_dprintf(STDERR_FILENO, "nm: '%s' Failed to retreive file status\n", filename);
        close(fd);
        return (-1);
    }
    if (S_ISDIR(file->st_mode)) {
        ft_dprintf(STDERR_FILENO, "nm: Warning: '%s' is a directory\n", filename);
        close(fd);
        return (-1);
    }
    if (!S_ISREG(file->st_mode)) {
        ft_dprintf(STDERR_FILENO, "nm: Warning: '%s' is not an ordinary file\n", filename);
        close(fd);
        return (-1);
    }
    if (file->st_size == 0) {
        close(fd);
        return (-1);
    }
    return (fd);
}

int main(int ac, char **av) {
    int fd;
    int res;
    int ret = 0;
    int i = ac > 1 ? 1 : 0;

    for (; i < ac; i++) {
        char *filename = ac > 1 ? av[i] : "a.out";
        struct stat file;
        char *data;

        fd = open_file(filename, &file);
        if (fd == -1) {
            ret++;
            continue;
        }
        data = mmap(0, file.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        close(fd);

        if (data == MAP_FAILED) {
            ft_dprintf(STDERR_FILENO, "nm: '%s' Failed to read file contents\n", filename);
            ret++;
            continue;
        }
        if (ac > 2) {
            ft_printf("\n%s:\n", filename);
        }

        res = handle_file(filename, data, file.st_size);
        if (res) {
            if (res == 1) {
                ft_dprintf(STDERR_FILENO, "nm: %s: no symbols\n", filename);
            }
            else if (res == 2) {
                ft_dprintf(STDERR_FILENO, "nm: %s: file format not recognized\n", filename);
                ret++;
            }
        }
        if (munmap(data, file.st_size) < 0) {
            ft_dprintf(STDERR_FILENO, "nm: Warning: '%s' Failed to unmap\n", filename);
            if (res != 2) {
                ret++;
            }
        }
    }
    return (ret);
}

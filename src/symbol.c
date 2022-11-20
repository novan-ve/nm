#include "nm.h"

void sort_symbols(t_symbol *symbols, size_t len) {
    t_symbol tmp;

    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < len - i - 1; j++) {
            char *str1 = symbols[j].name;
            char *str2 = symbols[j + 1].name;

            if (str1) {
                if (!str2 || ft_strcmp(str1, str2) > 0) {
                    tmp = symbols[j];
                    symbols[j] = symbols[j + 1];
                    symbols[j + 1] = tmp;
                }
            }
        }
    }
}

void print_symbols(t_symbol *symbols, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (symbols[i].value || (!symbols[i].value && symbols[i].size)) {
            ft_printf("%.16x ", symbols[i].value);
        }
        else {
            ft_printf("%17s", "");
        }
        ft_printf("%c ", symbols[i].type);
        ft_printf("%s\n", symbols[i].name ? symbols[i].name : "(null)");
    }
}

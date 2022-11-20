/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 17:39:33 by novan-ve      #+#    #+#                 */
/*   Updated: 2022/07/11 17:40:51 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(const char *s1, const char *s2) {
    size_t  index = 0;

    while (s1[index])
    {
        if (s1[index] != s2[index])
            return ((unsigned char)s1[index] - (unsigned char)s2[index]);
        index++;
    }
    return (0);
}

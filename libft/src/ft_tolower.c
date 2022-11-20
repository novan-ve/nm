/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_todown.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 15:07:45 by novan-ve      #+#    #+#                 */
/*   Updated: 2019/11/14 16:35:48 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_things.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <nabih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 11:20:25 by nabih             #+#    #+#             */
/*   Updated: 2020/01/11 11:55:41 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

char                *check_file(int ac, char **av)
{
    int         i;
    size_t      size;
    char        *str;

    i = 1;
    size = 0;
    str = NULL;
    while (i < ac)
    {
        size = ft_strlen(av[i]);
        if (av[i][size - 1] == 's' && av[i][size - 2] == '.')
            str = av[i];
        i++;
    }
    return (str);
}

int8_t              check_arguments(int ac)
{
    if (ac < 2)
        return (ASM_ERROR);
    return (ASM_SUCCESS);
}

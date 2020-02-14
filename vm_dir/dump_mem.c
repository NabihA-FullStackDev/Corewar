/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:03:37 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/07 10:16:07 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		dump_mem(uint8_t *arena)
{
	size_t	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02hhx ", arena[i]);
		if ((i + 1) % 32 == 0)
			ft_printf("\n");
		i++;

//a supprimer
		if (i / 32 > 10)
		{
			exit(0);
		}
/////////////////

	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_champ_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 06:55:52 by nabih             #+#    #+#             */
/*   Updated: 2020/02/01 08:43:27 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int8_t				set_register(t_champ *champ, char *arg, int size, int pos)
{
	int			i;
	char		c;

	i = 1;
	if (size == 0)
		return (ASM_ERROR);
	c = arg[size];
	arg[size] = '\0';
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (ASM_ERROR);
		i++;
	}
	(champ->type)[pos] = T_REG;
	(champ->val)[pos] = ft_atoi(arg + 1);
	if ((champ->val)[pos] < 1 || (champ->val)[pos] > REG_NUMBER)
		return (ASM_ERROR);
	arg[size] = c;
	return (ASM_SUCCESS);
}

int8_t				set_direct(t_champ *champ, char *arg, int size, int pos)
{
	int			i;
	char		c;

	i = 1;
	if (size == 0)
		return (ASM_ERROR);
	c = arg[size];
	arg[size] = '\0';
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (ASM_ERROR);
		i++;
	}
	(champ->type)[pos] = T_DIR;
	(champ->val)[pos] = ft_atoi(arg + 1);
	arg[size] = c;
	return (ASM_SUCCESS);
}

int8_t				set_indirect(t_champ *champ, char *arg, int size, int pos)
{
	int			i;
	char		c;

	i = 0;
	if (size == 0)
		return (ASM_ERROR);
	c = arg[size];
	arg[size] = '\0';
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (ASM_ERROR);
		i++;
	}
	(champ->type)[pos] = T_IND;
	(champ->val)[pos] = ft_atoi(arg);
	arg[size] = c;
	return (ASM_SUCCESS);
}

static void			set_label_nb(t_champ *champ, char *lab, int pos, int nb)
{
	champ->type[pos] |= T_LAB;
	champ->val[pos] = nb;
	if (nb == 1)
		champ->lab1 = ft_strdup(lab);
	else if (nb == 2)
		champ->lab2 = ft_strdup(lab);
}

int8_t				set_label(t_asm *a, t_champ *champ, char *label, int size)
{
	char		c;

	if (is_valide_name(label, size) == ASM_TRUE)
	{
		c = label[size];
		label[size] = '\0';
		if (champ->lab1 == NULL)
			set_label_nb(champ, label, a->pos, 1);
		else
			set_label_nb(champ, label, a->pos, 2);
		champ->type[a->pos] |= a->type;
		label[size] = c;
	}
	return (ASM_SUCCESS);
}

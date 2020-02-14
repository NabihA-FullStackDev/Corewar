/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:01:11 by nabih             #+#    #+#             */
/*   Updated: 2020/02/01 08:42:39 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int8_t				check_op(char *str, size_t size)
{
	int			op_code;

	op_code = 0;
	while (g_op_tab[op_code].name != NULL && str)
	{
		if (ft_strncmp(g_op_tab[op_code].name, str, size) == 0)
		{
			if (str[size] == ' ' || str[size] == '\t')
			{
				str[size] = '\0';
				ft_memmove(str, &(str[size + 1]), ft_strlen(&(str[size + 1])) + 1);
				skip_start(str);
				return (op_code);
			}
			else
				return (ASM_ERROR);
		}
		op_code++;
	}
	return (ASM_ERROR);
}

int8_t				check_line(t_asm *a, int *lab)
{
	int			size;
	t_champ		*tmp;

	tmp = NULL;
	if (a->line != NULL && *(a->line) != '\0')
	{
		size = 0;
		while ((a->line)[size] != ' ' && (a->line)[size] != '\t'
			   && (a->line)[size] != '\0')
			size++;
		if ((a->op_code = check_op(a->line, size)) == ASM_ERROR)
		{
			return (ASM_ERROR);
		}
		else
		{
			if ((tmp = arguments_analysis(a)) == NULL)
			  	return (ASM_ERROR);
			champ_pushfront(&(a->champ), tmp);
			if (*lab == 1 && a->champ)
			{
				*lab = 0;
				lab_add_ptr(&(a->lab), &(a->champ));
			}
		}
	}
	return (ASM_SUCCESS);
}

int8_t				get_code(t_asm *a)
{
	int			flg;
	int			lab;

	flg = 1;
	lab = 0;
	while (a->line != NULL && flg == 1)
	{
		skip_empty(a);
		skip_start(a->line);
		if (is_label(a, a->line) == ASM_TRUE)
			lab = 1;
		if (check_line(a, &lab) == ASM_ERROR)
			return (ASM_ERROR);
		ft_memdel((void**)&(a->line));
		flg = get_next_line(a->fd, &(a->line));
		a->line_nb += 1;
	}
	ft_memdel((void**)&(a->line));
	return (ASM_SUCCESS);
}

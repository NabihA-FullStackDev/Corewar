/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 22:11:11 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/21 17:43:43 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**  {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
*/

static t_bool		st_p2_valid(t_params *prm)
{
	return (prm->p2_type == TYPE_IND ||  is_reg_type(prm->p2_type, prm->p2));
}

void				op_st(t_vm *vm, t_cursor *c)
{
	t_params	prm;
	int	address;
	int			value;

	fill_params(&prm, vm->arena, c);
	if (is_reg_type(prm.p1_type, prm.p1) && st_p2_valid(&prm)
		&& is_absent_type(prm.p3_type) && is_absent_type(prm.p4_type))
	{
		value = c->regs[prm.p1];
		if (prm.p2_type == TYPE_IND)
		{
			address = prm.p2 % IDX_MOD + c->pc;
			write_4_bytes(vm->arena + pos(address), value);
		}
		else
		{
			c->regs[prm.p2] = value;
		}
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | st r%d(%d) => %d\n", c->c_id, prm.p1, value, prm.p2);
	}
	if (vm->flags & P_FLAG)
		ft_printf("ADV  %d (%#06x -> %#06x)\n", prm.newpc - c->pc, c->pc, prm.newpc);
	c->pc = prm.newpc;
}


/*
** 	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
**	"store index", 1, 1}.
**
** sti r2,%4,%5 sti copies REG_SIZE bytes of r2 at address (4 + 5)
** Parameters 2 and 3 are indexes. If they are, in fact, registers,
** we’ll use their contents as indexes.
**
** if ocp invalid, jump the size indicated with the wrong ocp
** and not execute operation.
*/

void				op_sti(t_vm *vm, t_cursor *c)
{
	t_params	prm;
	int			address;
	int32_t		value;

	fill_params(&prm, vm->arena, c);
	if (is_reg_type(prm.p1_type, prm.p1) && is_3_types(prm.p2_type, prm.p2)
		&& is_dir_or_reg(prm.p3_type, prm.p3) && is_absent_type(prm.p4_type))
	{
		prm.p2 = get_reg_size_value(vm, c, prm.p2_type, prm.p2);
		prm.p3 = get_reg_size_value(vm, c, prm.p3_type, prm.p3);
		address = c->pc + (prm.p2 + prm.p3) % IDX_MOD;
		value = c->regs[prm.p1];
		write_4_bytes(vm->arena + pos(address), value);
		if (vm->flags & V_FLAG)
			ft_printf("P    %d | sti r%d(%d) => %d + %d\n", c->c_id, prm.p1, value, prm.p2, prm.p3);
	}
	if (vm->flags & P_FLAG)
		ft_printf("ADV  %d (%#06x -> %#06x)\n", prm.newpc - c->pc, c->pc, prm.newpc);
	c->pc = prm.newpc;
}

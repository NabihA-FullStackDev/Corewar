/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <jleblond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:49:21 by jleblond          #+#    #+#             */
/*   Updated: 2020/02/18 18:15:49 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void 				usage(void)
{
	ft_putstr_fd("usage:./corewar [-dump <nb> -n <nb>] \
file1.cor file2.cor ...\n\
    -dump <nb> : dump memory in hexadecimal after <nb> cycles then quit\n\
    -n : set id of next player. Player_id must > 0 and <= player_nb\n\
    -v : show operations and cycle\n\
    -p : show movement of cursor\n", 2);
}

static void			player_to_arena(t_vm *vm)
{
	int 		i;
	int 		size;

	i = 0;
	size = MEM_SIZE / vm->player_nb;
	ft_printf("Introducing contestants...\n");
	while (i < vm->player_nb)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			vm->players[i].player_id,
			vm->players[i].file_size - sizeof(t_header),
			vm->players[i].prog_name, vm->players[i].comment);
		ft_memcpy(vm->arena + (size * i),
			vm->players[i].prog_data, vm->players[i].prog_size);
		vm->winner = vm->players[i].player_id;
		i++;
	}
}

int 				main(int argc, char const **argv)
{
	t_vm	vm;

	if (argc < 2)
	{
		usage();
		return (0);
	}
	ft_bzero(&vm, sizeof(t_vm));
	vm.cycle_to_die = CYCLE_TO_DIE;
	if (parse(&vm, argc, argv) && init_cursor_lst(&vm))
	{
		player_to_arena(&vm);
		run_vm(&vm);
	}
	free_vm(&vm);
	return (0);
}

int 				main_c_for_python(int argc, char const **argv)
{
	t_vm	vm;

	if (argc < 2)
	{
		usage();
		return (0);
	}
	ft_bzero(&vm, sizeof(t_vm));
	vm.cycle_to_die = CYCLE_TO_DIE;
	if (parse(&vm, argc, argv) && init_cursor_lst(&vm))
	{
		player_to_arena(&vm);
		run_vm(&vm);
	}
	free_vm(&vm);
	return (0);
}
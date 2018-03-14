/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrillef <cyrillef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 15:23:20 by cyrillef          #+#    #+#             */
/*   Updated: 2018/03/12 16:38:59 by dwald            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdbool.h>

# include <stdio.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft.h"
# include "op_corewar.h"

extern char				g_hex_tab[];
extern t_op				g_op_tab[];

typedef struct			s_node
{
	int					id;
	int					player;
	char				content[3];
	short				contentn;

	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct			s_champion
{
	bool				carry;
	int					lastLive; //number of the cycle where he called live
	int					liveNbr; //capitals in variable name not allowed by Norme
	int					previousLive; // number of live in the previous cycles
	t_node				*pc;
	int					ipc;
	char				name[PROG_NAME_LENGTH + 1];
	int					wait;
	bool				alive;
	unsigned int		number;
	int					nextOp; //capitals in variable name not allowed by Norme
	t_op				op;
	char				*filename;
	unsigned int		size;
	unsigned char		code[MEM_SIZE];
	char				comment[COMMENT_LENGTH + 1];
	int					reg[REG_NUMBER + 2];
	char				argsType[3];//capitals in variable name not allowed by Norme
	int					args[3];

	struct s_champion	*prev;
	struct s_champion	*next;
}						t_champion;

typedef struct			s_data
{
	int					dump;
	int					graph;
	t_champion			*champions;
	int					nb_champion;
	t_node				*map;
	unsigned int		live; //total of live processus starting from last CTDie
	unsigned int		cycle; //total of cycles from the start
	unsigned int		cyclec; //total starting from last cycleToDie
	unsigned int		cycletodie; //same as the define - used to decrement
	unsigned int		lastlive; //id of the vinner
	bool				pause;
	int					speed;
}						t_data;

/*
** dump.c
** Manage the -dump arg
*/

void					dump(t_data *data);


/*
** args.c
** Manage different arguments
*/

t_data					*init_data(int ac, char **av);
int						verbose_operations(t_data *data);

/*
** read_champion.c
** Read champions files and create each player
*/

int						read_champions(t_data *data);
int						prepare_champion(t_data *data, char *filename,
						int number, bool isfork);

/*
** init_map.c
** Initialize map and print the code in memory
*/

int						init_map(t_data *data);

/*
** init_processes.c
** Initialize each player's process
*/

int						init_processes(t_data *data);

/*
** error.c
** Throw error and free data
*/

void					free_data(t_data *data);
void					corewar_error(t_data *data, char *str);

/*
** number_to_hex_str.c
** Hexadecimal conversion stuff
*/

int						str_hex_to_number(char str[3]);
void					number_to_hex_str(int n,
											unsigned char (*str)[]);

/*
** do_next_op.c
*/

int						do_next_op(t_data *data);

/*
** prepare_next_op.c
*/

int						prepare_next_op(t_data *data);

/*
** vm.c
** Start the VM after everything has been initialized
*/

int						vm_start(t_data *data);

/*
** vm_check_live.c
** Check if champions executed "live" since last checkup and
** kill them if it is needed
*/

int						vm_check_live(t_data *data);

/*
** display_vm.c
** display_vm_2.c
** Display nodes and stats of the vm
*/

void					display_map(t_data *data);
void					update_legend(t_data *data);

/*
** tty.c
** Change settings of tty and get keys
*/

void					key_hub(t_data *data);

/*
** Commands
*/

int						corewar_add(t_data *data, t_champion *champ);
int						corewar_aff(t_data *data, t_champion *champ);
int						corewar_and(t_data *data, t_champion *champ);
int						corewar_fork(t_data *data, t_champion *champ);
int						corewar_ld(t_data *data, t_champion *champ);
int						corewar_ldi(t_data *data, t_champion *champ);
int						corewar_lfork(t_data *data, t_champion *champ);
int						corewar_live(t_data *data, t_champion *champ);
int						corewar_lld(t_data *data, t_champion *champ);
int						corewar_lldi(t_data *data, t_champion *champ);
int						corewar_or(t_data *data, t_champion *champ);
int						corewar_st(t_data *data, t_champion *champ);
int						corewar_sti(t_data *data, t_champion *champ);
int						corewar_sub(t_data *data, t_champion *champ);
int						corewar_xor(t_data *data, t_champion *champ);
int						corewar_zjmp(t_data *data, t_champion *champ);
t_node					*find_pc_node(t_champion *champ, short pc_dest);
int						write_in_ram(t_champion*champ, short pc_dest);
int						find_indirect_value(t_champion *champ, int index);
int						mem_mod(int n);
#endif

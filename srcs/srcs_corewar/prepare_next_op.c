/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_next_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrillef <cyrillef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 13:31:15 by cyrillef          #+#    #+#             */
/*   Updated: 2018/01/15 11:42:17 by cyrillefrouin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				get_next_op(t_champion *champion)
{
	int			opn;
	int			i;

	i = 0;
	opn = champion->pc->contentn;
	while (i < 16)
	{
		if (g_op_tab[i].opcode == opn)
		{
			champion->op = g_op_tab[i];
			return (champion->op.nb_cycles);
		}
	}
	return (-1);
}

int				prepare_next_op(t_data *data)
{
	t_champion	*champion;

	champion = data->champions;
	while (champion->next != NULL)
		champion = champion->next;
	while (champion != NULL)
	{
		if (champion->nextOp <= 0)
			champion->nextOp = get_next_op(champion);
		else
			champion->nextOp--;
		champion = champion->prev;
	}
	return (1);
}

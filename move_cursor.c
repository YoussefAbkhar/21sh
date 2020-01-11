/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:19:30 by yabakhar          #+#    #+#             */
/*   Updated: 2020/01/11 16:19:34 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void       move_left(t_line *line,int *cursor)
{
    if ((*cursor) > get_oc(line))
	{
		(*cursor)--;
		cur_goto(line, (*cursor));
	}
}

void       move_right(t_line *line,int *cursor)
{
    if ((*cursor) < (get_oc(line) + line->len))
	{
		(*cursor)++;
		cur_goto(line, (*cursor));
	}
}

void        home_deep(t_line *line,t_init *init,int *cursor)
{
    if (init->r == HOME)
	{
		(*cursor) = get_oc(line);
		cur_goto(line, (*cursor));
	}
	else if (init->r == DEEP)
	{
		(*cursor) = get_oc(line) + line->len;
		cur_goto(line, (*cursor));
	}
}

void        esc(void)
{
    struct termios config;
	config.c_lflag |= (ECHO | ICANON);
	tputs(tgetstr("me", 0), 0, ft_output);
	exit(1);
}
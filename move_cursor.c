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

void		ft_allocate_table(t_line *line,char *str)
{
	int i=0;
	if (str)
	{
		while (str[i] && str)
		{
			if (str[i] == '\n')
				line->index++;		
			i++;
		}
	}
	line->tabl = ft_memalloc(sizeof(int) * (line->index + 1));
}

void		ft_stock_totable(t_line *line,char *str)
{
	int k = 0;   
    int i = 0;
    int j = 0;
    while (str[i] && str)
    {
        if (str[i] != '\n' && str[i + 1] != '\0')
            j++;
        else
        {
			if (str[i + 1] == '\0')
				line->tabl[k] = j;
			else
            	line->tabl[k] = j - 1 ;
            j = 0;
			k++;
        }
        i++;
    }
}

void 		print_multi(char *str,t_line *line,int *cursor)
{
	if (line->index == *cursor)
		str = NULL;
	if (line->tabl)
		free(line->tabl);
	ft_allocate_table(line,str);
	ft_stock_totable(line,str);
	line->len = line->tabl[0];
	ft_putstr(str);
	cur_goto(line, get_oc(line));
	line->index = 0;
}
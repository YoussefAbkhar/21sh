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

void move_cursor_v(t_line *line)
{
	t_point point;
	int i;
	point = line->c_o;
	i = line->i;
	while (i > 0)
	{
		i--;
		point.y += line->tabl[i] / line->col;
		if (line->tabl[line->i] % line->col > 0)
			point.y += 1;
		point.x = 0;
	}
	line->c_v = point;
}

void       move_left(t_line *line,int *cursor)
{
    if ((*cursor) > 0 && line->len > 0)
	{
		(*cursor)--;
		cur_goto(line, (*cursor));
	}
	else if ((*cursor) == 0 && line->index > 0 && line->i > 0)
	{
		line->i--;
		line->len = line->tabl[line->i];
		(*cursor) = line->len;
		move_cursor_v(line);
		if (line->i == 0)
			tputs(tgoto(tgetstr("cm", 0), line->c_o.x + (*cursor),line->c_v.y), 0, ft_output);
		else
			tputs(tgoto(tgetstr("cm", 0), (*cursor) ,line->c_v.y), 0, ft_output);
	}
}

void       move_right(t_line *line,int *cursor)
{
 	if ((*cursor) < line->len)
	{
		(*cursor)++;
		cur_goto(line, (*cursor));
	}
	else if ((*cursor) == line->len  && line->index > 0 && line->index > line->i)
	{
		line->i++;
		line->len = line->tabl[line->i];
		move_cursor_v(line);
		tputs(tgoto(tgetstr("cm", 0), line->c_v.x, line->c_v.y), 0, ft_output);
		(*cursor) = 0;
	}
}

void        home_deep(t_line *line,t_init *init,int *cursor)
{
    if (init->r == HOME)
	{
		line->c_v = line->c_o;
		line->i = 0;
		(*cursor) = 0;
		line->len = line->tabl[line->i];
		tputs(tgoto(tgetstr("cm", 0), line->c_v.x, line->c_v.y), 0, ft_output);
	}
	else if (init->r == DEEP)
	{
		line->i = line->index;
		line->len = line->tabl[line->i];
		(*cursor) = line->len;
		move_cursor_v(line);
		tputs(tgoto(tgetstr("cm", 0), line->c_v.x + 1, line->c_v.y), 0, ft_output);
	}
}

void        esc(void)
{
    struct termios config;
	config.c_lflag |= (ECHO | ICANON);
	tputs(tgetstr("me", 0), 0, ft_output);
	exit(1);
}

void		ft_stock_totable(t_line *line,char *str)
{
	int k = 0;   
    int i = 0;
    int j = 0;
    while (str && str[i])
    {
        if (str[i] != '\n' && str[i + 1] != '\0')
            j++;
        else
        {
			if (str[i + 1] == '\0')
				line->tabl[k] = j + 1;
			else
            	line->tabl[k] = j;
            j = 0;
			k++;
        }
        i++;
    }
}

void		ft_allocate_table(t_line *line,char *str)
{
	int i = 0;
	while (str[i] && str)
	{
		if (str[i] == '\n')
			line->index++;		
		i++;
	}
	line->tabl = ft_memalloc(sizeof(int) * (line->index + 1));
	ft_stock_totable(line,str);
}

void 		print_multi(char *str,t_line *line)
{
	if (line->tabl)
		free(line->tabl);
	ft_putstr(str);
	ft_allocate_table(line,str);
	line->len = line->tabl[line->i];
	cur_goto(line, 0);
}
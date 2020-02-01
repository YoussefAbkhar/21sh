/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:19:30 by yabakhar          #+#    #+#             */
/*   Updated: 2020/01/15 14:32:01 by yabakhar         ###   ########.fr       */
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
		if (line->tabl[i] % line->col >= 0)
			point.y += 1;
		point.x = 0;
	}
	line->c_v = point;
}

int count_len(t_line *line)
{
	int i;
	int k;

	k = 0;
	i = line->i;
	while (i > 0)
	{
		i--;
		k += line->tabl[i];
	}
	return(k);
}


void       move_right(t_line *line, int *cursor)
{
 	if ((*cursor) < line->len - (line->i != line->index))
	{
		(*cursor)++;
		cur_goto(line, (*cursor));
		line->c_len++;
	}
	else if ((*cursor) == line->len - 1  && line->index > 0 && line->index > line->i)
	{
		line->i++;
		line->len = line->tabl[line->i];
		move_cursor_v(line);
		(*cursor) = 0;
		cur_goto(line, (*cursor));
		line->c_len++;
	}
}

void       move_left(t_line *line,int *cursor)
{
    if ((*cursor) > 0)
	{
		(*cursor)--;
		cur_goto(line, (*cursor));
		line->c_len--;
	}
	else if ((*cursor) == 0 && line->index > 0 && line->i > 0)
	{
		line->i--;
		line->len = line->tabl[line->i];
		(*cursor) = line->len - 1;
		move_cursor_v(line);
		cur_goto(line, (*cursor));
		line->c_len--;
	}
}

void       move_up(t_line *line,int *cursor)
{

	if (line->i > 0)
	{
		line->i--;
		line->len = line->tabl[line->i];
		move_cursor_v(line);
		if ((*cursor) > line->len - 1)
			(*cursor) = line->len - 1;
		if (line->i == 0)
			tputs(tgoto(tgetstr("cm", 0), line->c_o.x + (*cursor),line->c_v.y), 0, ft_output);
		else
			tputs(tgoto(tgetstr("cm", 0), (*cursor) ,line->c_v.y), 0, ft_output);
		line->c_len = (count_len(line) + (*cursor));
	}
}

void       move_down(t_line *line,int *cursor)
{
	if (line->i < line->index)
	{
		line->i++;
		line->len = line->tabl[line->i];
		move_cursor_v(line);
		if ((*cursor) > line->len - 1)
			(*cursor) = line->len - 1;
		tputs(tgoto(tgetstr("cm", 0), (*cursor) ,line->c_v.y), 0, ft_output);
		line->c_len = (count_len(line) + (*cursor));
	}
}

void        home_deep(t_line *line,t_init *init,int *cursor, char *str)
{
    if (init->r == HOME)
	{
		line->c_v = line->c_o;
		line->i = 0;
		line->c_len = 0;
		(*cursor) = 0;
		line->len = line->tabl[line->i];
		tputs(tgoto(tgetstr("cm", 0), line->c_v.x, line->c_v.y), 0, ft_output);
	}
	else if (init->r == DEEP)
	{
		line->b_line = ft_strlen(str);
		line->i = line->index;
		line->c_len = line->b_line;
		line->len = line->tabl[line->i];
		(*cursor) = line->len;
		move_cursor_v(line);
		tputs(tgoto(tgetstr("cm", 0), (line->c_v.x + *cursor) % line->col, (line->c_v.y + (line->c_v.x + *cursor) / line->col)), 0, ft_output);
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
	
    while (str && str[i])
    {
		line->tabl[k]++;
		if(str[i] == '\n')
			k++;
        i++;
    }
}

void		ft_allocate_table(t_line *line,char *str)
{
	int i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				line->index++;		
			i++;
		}
	}
	line->tabl = ft_memalloc(sizeof(int) * (line->index + 1));
	ft_stock_totable(line,str);
}

void 		multilne(char *str,t_line *line)
{
	// if (line->tabl)
	// 	ft_memdel((void **)&line->tabl);
	line->len = 0;
	line->index = 0;
	ft_allocate_table(line, str);
	line->len = line->tabl[line->i];
}

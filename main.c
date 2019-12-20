/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2019/11/19 12:09:00 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "ft_select.h"

int ft_output(int str)
{
	ft_putchar(str);
	return (0);
}

void cur_goto(t_line *line, int cursor)
{
    int co;
    int li;

    li = cursor / line->col;
    co = cursor % line->col;
    line->cursor = cursor;
    tputs(tgoto(tgetstr("cm", 0), co, li), 0, ft_output);
}

void get_cursor_position(t_line *line)
{
    char *buff;
    int col;
    int row;

    buff = (char[20]){0};
    ft_putstr_fd("\e[6n", 0);
    read(0, buff, 20);
    row = ft_atoi(buff + 2);
    buff = (char *)ft_strchr(buff, ';');
    col = ft_atoi(buff + 1);
    line->cursor_origne = (row - 1) * line->col + col - 1;
    line->cursor = line->cursor_origne;
}

void	ft_init(t_line *line)
{
	char buf[1024];
	struct winsize w;
	struct termios config;
	if (tcgetattr(0, &config) < 0)
		ft_putstr_fd("error", 0);
	config.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(0, 0, &config) < 0)
		ft_putstr_fd("error", 0);
	tgetent(buf, getenv("TERM"));
    ioctl(0, TIOCGWINSZ, &w);
	line->col = w.ws_col;
	line->row = w.ws_row;
}


// void ft_kdel(char **str, int cursor)
// {
// 	char *aff = ft_strsub(*str,0,cursor - 1);
//     char *pp = ft_strsub(*str,cursor,ft_strlen(*str) - cursor + 1);
// 	ft_strdel(str);
//     *str = ft_strjoin(aff,pp);
// }

int main()
{
	t_init init;
	t_line line;
	struct termios config;
	t_node *list;
	if (!(list = ft_memalloc(sizeof(t_node))))
            return (0);
	int cursor;
	line.len = 0;
	cursor = 0;
	init.k = 1;
	char *str;
	str = NULL;
	ft_init(&line);
	while (1)
	{
		if (init.k == 1)
		{
			ft_putstr("->");
			get_cursor_position(&line);
			cur_goto(&line,line.cursor);
			cursor = line.cursor;
			init.k = -1;
		}
		init.r = 0;
		if (read(0, &init.r, sizeof(int)) > 0)
		{
			if (init.r == ESC)
			{
				config.c_lflag |= (ECHO | ICANON);
				tputs(tgetstr("me", 0), 0, ft_output);
				exit(1);
			}
			else if (init.r == LEFT)
			{
				if (cursor > line.cursor_origne)
				{
					cursor--;
					cur_goto(&line,cursor);
				}
			}
			else if (init.r == RIGHT)
			{
				if (cursor < (line.cursor_origne + line.len))
				{
					cursor++;
					cur_goto(&line,cursor);
				}
			}
			else if (init.r == DEL)
				ft_delet(&str,&line, &cursor);
			else if (init.r == HOME)
			{
				cursor = line.cursor_origne;
				cur_goto(&line,cursor);
			}
			else if (init.r == DEEP)
			{
				cursor = line.cursor_origne + line.len;
				cur_goto(&line,cursor);
			}
			else if (init.r == END)
			{
				ft_stock(str, &list);
				line.col +=1;
				get_cursor_position(&line);
			}
			else if (init.r == UP)
			{
				if (list->next)
				{
					list = list->next;
					ft_putendl(list->content);
				}
			}
			else if (init.r == DOWN)
			{
				if (list->prev)
				{
					list = list->prev;
					ft_putendl(list->content);
				}
			}
			else if (init.r == ALTRTH)
				ft_alt_rth(str, &line, &cursor);
			else if (init.r == ALTLFT)
				ft_alt_lft(str, &line, &cursor);
			else
				ft_printnbl(&str,&line,&init,&cursor);
		}
	}
	return (0);
}

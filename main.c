/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2019/12/23 01:33:23 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int ft_output(int str)
{
	ft_putchar(str);
	return (0);
}

int get_oc(t_line *line)
{
	return(line->cursor_origne.y * line->col + line->cursor_origne.x - 1);
}

void cur_goto(t_line *line, int cursor)
{
	int co;
	int li;

	li = cursor / line->col;
	co = cursor % line->col;
	tputs(tgoto(tgetstr("cm", 0), co, li), 0, ft_output);
}

void get_cursor_position(t_line *line)
{
	char *buff;

	buff = (char[20]){0};
	ft_putstr_fd("\e[6n", 0);
	read(0, buff, 20);
	line->cursor_origne.y = ft_atoi(buff + 2) - 1;
	if ((buff = (char *)ft_strchr(buff, ';')))
		line->cursor_origne.x = ft_atoi(buff + 1);
	else
		line->cursor_origne.x = 0;
}

void ft_putstr4(char *s, char *s1, char *s2, char *s3)
{
	ft_putstr(s);
	ft_putstr(s1);
	ft_putstr(s2);
	ft_putstr(s3);
}
void ft_porompte(void)
{
	char cwd[256];
	char *cwd1;
	char *str1;

	if (getcwd(cwd, sizeof(cwd)))
		cwd1 = getcwd(cwd, sizeof(cwd));
	else
	{
		ft_putstr4("\033[1;33m", " 😡 permission denied ", "\n", "\033[0m");
		exit(1);
	}
	if (ft_strcmp(cwd1, "/") == 0)
	{
		ft_putstr4("\033[1;33m", "😜 ", cwd1, " $> \033[0m");
		return;
	}
	str1 = ft_strrchr(cwd1, '/');
	ft_putstr4("\033[1;32m➜", "  \033[1;36m", str1 + 1, " $> \033[0m");
}

void ft_init(t_line *line)
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
	line->index = 0;
	line->tabl = NULL;
}

void print_porompte(int *cursor, t_line *line)
{
	write(1, "\n", 1);
	ft_porompte();
	get_cursor_position(line);
	cur_goto(line, get_oc(line));
	*cursor = get_oc(line);
}

int main()
{
	t_init init;
	t_line line;
	t_node *list, *head;
	list = NULL;
	int cursor;
	line.len = 0;
	cursor = 0;
	init.k = 1;
	char *str;
	str = NULL;
	ft_init(&line);
	head = list;
	while (1)
	{
		if (init.k == 1)
		{
			ft_porompte();
			get_cursor_position(&line);
			cur_goto(&line, get_oc(&line));
			cursor = get_oc(&line);
			init.k = -1;
		}
		init.r = 0;
		if (read(0, &init.r, sizeof(int)) > 0)
		{
			if (init.r == ESC)
				print_multi(str,&line);
			else if (init.r == LEFT)
				move_left(&line,&cursor);
			else if (init.r == RIGHT)
				move_right(&line,&cursor);
			else if (init.r == DEL)
				ft_delet(&str, &line, &cursor);
			else if (init.r == HOME || init.r == DEEP)
				home_deep(&line,&init,&cursor);
			else if (init.r == END && str)
				ft_end(&list, &head, &line, &str, &cursor);
			else if (init.r == END && !str)
				print_porompte(&cursor, &line);
			else if (init.r == UP)
				ft_next(&head, &list, &cursor, &str, &line);
			else if (init.r == DOWN)
				ft_prev(&head, &list, &cursor, &str, &line);
			else if (init.r == ALTRTH)
				ft_alt_rth(str, &line, &cursor);
			else if (init.r == ALTLFT)
				ft_alt_lft(str, &line, &cursor);
			else
				ft_printnbl(&str, &line, &init, &cursor);
		}
	}
	return (0);
}

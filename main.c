/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2020/01/15 14:41:49 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int ft_output(int str)
{
	ft_putchar(str);
	return (0);
}

void cur_goto(t_line *line, int cursor)
{
	int x;
	int y;

	y = (line->c_v.y + (line->c_v.x + cursor) / line->col);
	x = ((line->c_v.x + cursor) % line->col);
	tputs(tgoto(tgetstr("cm", 0), x, y), 0, ft_output);
}

void get_cursor_position(t_line *line)
{
	char *buff;
	int i = 0;
	buff = (char[20]){0};
	while (1)
	{
		ft_putstr_fd("\e[6n", 0);
		i = read(0, buff, 20);
		buff[i] = 0;
		if (ft_strchr(buff,'['))
			break;
	}
	line->c_o.y = ft_atoi(buff + 2) - 1;
	if ((buff = (char *)ft_strchr(buff, ';')))
		line->c_o.x = ft_atoi(buff + 1);
	else
		line->c_o.x = 0;
	line->c_v = line->c_o;
}

void ft_put_multistring(char **strings)
{
	while(*strings)
		ft_putstr(*strings++);
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
		ft_put_multistring((char *[]){"\033[1;33m", " 😡 permission denied ", "\n", "\033[0m",0});
		exit(1);
	}
	if (ft_strcmp(cwd1, "/") == 0)
	{
		ft_put_multistring((char *[]){"\033[1;33m", "😜 ", cwd1, " $> \033[0m",0});
		return;
	}
	str1 = ft_strrchr(cwd1, '/');
	ft_put_multistring((char *[]){"\033[1;32m➜ ","\033[1;36m ", str1 + 1, " $>\033[0m",0});
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
	line->i = 0;
	line->tabl = 0;
}

void print_porompte(int *cursor, t_line *line)
{
	int i = line->index - line->i;
	while (i-- > 0)
		write(1, "\n", 1);
	line->index = 0;
	line->i = 0;
	write(1, "\n", 1);
	ft_porompte();
	get_cursor_position(line);
	*cursor = 0;
	tputs(tgoto(tgetstr("cm", 0), line->c_o.x, line->c_o.y), 0, ft_output);
}

void print_line(char *str)
{
	while(*str)
	{
		ft_putchar(*str);
		if(str[1] == '\n' || str[1] == '\0')
			ft_putchar(' ');
		str++;
	}
}

int main()
{
	t_init init;
	t_line line;
	t_node *list, *head;
	char buff[1024];
	list = NULL;
	int cursor;
	line.len = 0;
	cursor = 0;
	init.k = 1;
	int i;
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
			cur_goto(&line, 0);
			cursor = 0;
			init.k = -1;
			line.c_len = 0;
			line.b_line = 0;
		}
		init.r = 0;
		ft_bzero(buff, 1024);
		if (read(0, buff, 1023) > 0)
		{
			init.r = (int)*((int *)buff);
			if (init.r == LEFT)
				move_left(&line,&cursor);
			else if (init.r == RIGHT)
				move_right(&line,&cursor);
			else if (init.r == DEL)
				ft_delet(&str, &line, &cursor);
			else if (init.r == page_down)
				move_down(&line,&cursor);
			else if (init.r == page_up)
				move_up(&line,&cursor);
			else if (init.r == HOME || init.r == DEEP)
				home_deep(&line,&init,&cursor,str);
			else if (init.r == END && str)
				ft_end(&list, &head, &line, &str, &cursor);
			else if (init.r == END && !str)
				print_porompte(&cursor, &line);
			else if (init.r == UP)
				ft_next(&head, &list, &cursor, &str, &line);
			else if (init.r == DOWN)
				ft_prev(&head, &list, &cursor, &str, &line);
			else if (init.r == alt_rth)
				ft_alt_rth(str, &line, &cursor);
			else if (init.r == alt_lft)
				ft_alt_lft(str, &line, &cursor);
			else
			{
				i = -1;
				while (buff[++i])
					if (ft_isprint(buff[i]) || buff[i] == '\n')
						ft_printnbl(&str, &line, &init, &cursor,buff[i]);
				tputs(tgoto(tgetstr("cm", 0), line.c_o.x, line.c_o.y), 0, ft_output);
				tputs(tgetstr("cd", 0), 0, ft_output);
				print_line(str);
				ft_update_cursor_o(&line);
				cur_goto(&line, cursor);
				i = 0;
			}
		}
	}
	return (0);
}

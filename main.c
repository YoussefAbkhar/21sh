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

int output(int str)
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
    tputs(tgoto(tgetstr("cm", 0), co, li), 0, output);
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
	tputs(tgetstr("ti", 0), 0, output);
    ioctl(0, TIOCGWINSZ, &w);
	line->col = w.ws_col;
	line->row = w.ws_row;
}

void ft_print(char **str,char *c,int cursor)
{
	char *aff;
	char *pp;
	char *dd;

	aff = ft_strsub(*str,0,cursor);
	pp = ft_strsub(*str,cursor,ft_strlen(*str) - cursor);
	ft_strdel(str);
	dd = ft_strjoin(aff,c);
	*str = ft_strjoin(dd,pp);
	ft_strdel(&dd);
	ft_strdel(&pp);
	ft_strdel(&aff);
}

void ft_kdel(char **str, int cursor)
{
	char *aff = ft_strsub(*str,0,cursor - 1);
    char *pp = ft_strsub(*str,cursor,ft_strlen(*str) - cursor + 1);
	ft_strdel(str);
    *str = ft_strjoin(aff,pp);  
}

int main()
{
	t_init init;
	t_line line;
	struct termios config;
	int cursor;
	line.len = 0;
	cursor = 0;
	init.k = 1;
	char *str;
	str = NULL;
	char c[2];
	ft_init(&line);
	while (1)
	{
		if (init.k == 1)
		{
			// tputs(tgoto(tgetstr("cm", 0), 0, 0), 0, output);
			// ft_putstr_fd("->",2);
			tputs(tgoto(tgetstr("cm", 0), 0, 0), 0, output);
			init.k = -1;
		}
		init.r = 0;
		if (read(0, &init.r, sizeof(int)) > 0)
		{
			if (init.r == ESC)
			{
				config.c_lflag |= (ECHO | ICANON);
				tputs(tgetstr("te", 0), 0, output);
				tputs(tgetstr("me", 0), 0, output);
				exit(1);
			}
			else if (init.r == LEFT)
			{
				if (cursor > 0)
				{
					cursor--;
					cur_goto(&line,cursor);
				}
			}
			else if (init.r == RIGHT)
			{
				if (cursor < line.len)
				{
					cursor++;
					cur_goto(&line,cursor);
				}
			}
			else if (init.r == DEL)
			{
				if (cursor > 0 && line.len > 0)
				{
					ft_kdel(&str, cursor);
					tputs(tgoto(tgetstr("cm", 0), 0, 0), 0, output);
					tputs(tgetstr("cd", 0), 0, output);
					ft_putstr(str);
					cursor--;
					line.len--;
					cur_goto(&line,cursor);
				}
			}
			else if (init.r == ALTRTH && cursor < line.len)
			{
					while (str[cursor])
					{
							if (!ft_isalnum(str[cursor]))
									break;
							cursor++;
					}
					while (str[cursor])
					{
							if (ft_isalnum(str[cursor]))
									break;
							cursor++;
					}
					tputs(tgoto(tgetstr("cm", 0), 0, 0), 0, output);
					tputs(tgetstr("cd", 0), 0, output);
					ft_putstr(str);
					cur_goto(&line,cursor); 
			}
			else
			{
				if (ft_isprint(init.r))
				{
					c[1] ='\0';
					c[0] = init.r;
					if (!str)
						str = ft_strdup("\0");
					ft_print(&str,c,cursor);
					cursor++;
					line.len++;
					tputs(tgoto(tgetstr("cm", 0), 0, 0), 0, output);
					tputs(tgetstr("cd", 0), 0, output);
					ft_putstr(str);
					cur_goto(&line,cursor);
				}
			}
		}
	}
	return (0);
}

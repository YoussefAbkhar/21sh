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

void		ft_putstr4(char *s, char *s1, char *s2, char *s3)
{
	ft_putstr(s);
	ft_putstr(s1);
	ft_putstr(s2);
	ft_putstr(s3);
}
void                    ft_porompte(void)
{
        char            cwd[256];
        char            *cwd1;
        char            *str1;

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
            return ;
        }
        str1 = ft_strrchr(cwd1, '/');
        ft_putstr4("\033[1;32m➜", "  \033[1;36m", str1 + 1, " $> \033[0m");

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

int main()
{
	t_init init;
	t_line line;
	struct termios config;
	t_node *list,*head;
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
			else if (init.r == END && str)
			{
				if (list && list->prev)
				{
					head = head->next;
					ft_strdel(&head->prev->content);
					ft_memdel((void**)&head->prev);
				}
				ft_stock(str, &head,line.len);
				list = NULL;
				cur_goto(&line,line.cursor_origne);
				tputs(tgetstr("cd", 0), 0, ft_output);
				ft_strdel(&str);
				line.len = 0;
				get_cursor_position(&line);
				cur_goto(&line,line.cursor);
				cursor = line.cursor;
				line.first = 0;
			}
			else if (init.r == UP)
				ft_next(&head, &list, &cursor, &str,&line);
			else if (init.r == DOWN)
				ft_prev(&head, &list, &cursor, &str,&line);
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

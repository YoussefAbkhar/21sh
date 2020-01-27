/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_alt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 23:33:30 by yabakhar          #+#    #+#             */
/*   Updated: 2019/12/18 23:37:25 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void    ft_clearline(char *str,int cursor,t_line *line)
{
	cur_goto(line,0);
	tputs(tgetstr("cd", 0), 0, ft_output);
	ft_putstr(str);
	cur_goto(line,cursor);
}

void    ft_alt_rth(char *str,t_line *line, int *cursor)
{
	if ((*cursor) < line->len)
	{
		while (str[(*cursor)])
		{
			if (!ft_isalnum(str[(*cursor)]))
				break;
			(*cursor)++;
		}
		while (str[(*cursor)])
		{
			if (ft_isalnum(str[(*cursor)]))
				break;
			(*cursor)++;
		}
        ft_clearline(str,*cursor,line);
	}
}

void    ft_alt_lft(char *str,t_line *line, int *cursor)
{
	int k;
	k = *cursor;
	if ((*cursor) > 0)
	{
		while (str[--(k)])
		{
			--(*cursor);
			if (ft_isalnum(str[(k)]))
				break;
		}
			while (str[--(k)] )
		{
			--(*cursor);
			if (!ft_isalnum(str[(k)]))
				break;
		}
		if (k > 0)
			(*cursor)++;
        ft_clearline(str,*cursor,line);
    }
}

void	ft_delet(char **str,t_line *line, int *cursor)
{
	char *tmp;
	char *tmp1;
	if (line->c_len > 0)
	{
		if ((*str)[line->c_len - 1] == '\n')
		{
			line->i--;
			(*cursor) = line->tabl[line->i];
		}
		(*cursor)--;
		tmp = ft_strsub(*str,0,line->c_len - 1);
    	tmp1 = ft_strsub(*str, line->c_len, line->b_line - line->c_len + 1);
		ft_strdel(str);
    	*str = ft_strjoin(tmp,tmp1);
		ft_strdel(&tmp);
		ft_strdel(&tmp1);
		tputs(tgoto(tgetstr("cm", 0), line->c_o.x, line->c_o.y), 0, ft_output);
		tputs(tgetstr("cd", 0), 0, ft_output);
		ft_putstr(*str);
		line->b_line--;
		line->len--;
		line->c_len--;
		multilne(*str,line);
		move_cursor_v(line);
		cur_goto(line, (*cursor));
	}
}

void ft_print(char **str,char *c, int cursor,t_line *line)
{
	char *tmp;
	char *tmp1;
	char *tmp2;

	tmp = ft_strsub(*str,0,cursor);
	tmp1 = ft_strsub(*str,cursor,line->b_line - cursor);
	ft_strdel(str);
	tmp2 = ft_strjoin(tmp, c);
	*str = ft_strjoin(tmp2, tmp1);
	ft_strdel(&tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp);
}

void    ft_printnbl(char **str,t_line *line, t_init *init,int *cursor,char c)
{
	init->c[1] ='\0';
	init->c[0] = c;
	if (!(*str))
		(*str) = ft_strdup("\0");
	ft_print(str,init->c, line->c_len,line);
	line->len++;
	if (c == '\n')
	{
		line->i++;
		(*cursor) = 0;
	}
	else
		(*cursor)++;
	multilne(*str,line);
	line->c_len++;
	line->b_line++;
	tputs(tgoto(tgetstr("cm", 0), line->c_o.x, line->c_o.y), 0, ft_output);
	tputs(tgetstr("cd", 0), 0, ft_output);
	ft_putstr(*str);
}

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
	cur_goto(line,get_oc(line));
	tputs(tgetstr("cd", 0), 0, ft_output);
	ft_putstr(str);
	cur_goto(line,cursor);
}

void    ft_alt_rth(char *str,t_line *line, int *cursor)
{
	int k;
	k = *cursor - get_oc(line);
	if ((*cursor) < get_oc(line) + line->len)
	{
		while (str[(k)])
		{
			if (!ft_isalnum(str[(k)]))
				break;
			(*cursor)++;
			k++;
		}
		while (str[(k)])
		{
			if (ft_isalnum(str[(k)]))
				break;
			(*cursor)++;
			k++;
		}
        ft_clearline(str,*cursor,line);
	}
}

void    ft_alt_lft(char *str,t_line *line, int *cursor)
{
	int k;
	k = *cursor - get_oc(line);
	if ((*cursor) > get_oc(line))
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

void ft_print(char **str,char *c, int cursor)
{
	char *tmp;
	char *tmp1;
	char *tmp2;

	tmp = ft_strsub(*str,0,cursor);
	tmp1 = ft_strsub(*str,cursor,ft_strlen(*str) - cursor);
	ft_strdel(str);
	tmp2 = ft_strjoin(tmp, c);
	*str = ft_strjoin(tmp2, tmp1);
	ft_strdel(&tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp);
}

void	ft_delet(char **str,t_line *line, int *cursor)
{
	char *tmp;
	char *tmp1;
	int k;
	k = *cursor - get_oc(line);
	if (k > 0 && line->len > 0)
	{
		tmp = ft_strsub(*str,0,(k) - 1);
    	tmp1 = ft_strsub(*str, (k), ft_strlen(*str) - (k) + 1);
		ft_strdel(str);
    	*str = ft_strjoin(tmp,tmp1);
		ft_strdel(&tmp);
		ft_strdel(&tmp1);
		cur_goto(line,get_oc(line));
		tputs(tgetstr("cd", 0), 0, ft_output);
		ft_putstr(*str);
		(*cursor)--;
		line->len--;
		cur_goto(line,*cursor);
	}
}

void    ft_printnbl(char **str,t_line *line, t_init *init,int *cursor)
{
	if (ft_isprint(init->r))
	{
		init->c[1] ='\0';
		init->c[0] = init->r;
		if (!(*str))
			(*str) = ft_strdup("\0");
		ft_print(str,init->c, *cursor - get_oc(line));
		(*cursor)++;
		line->len++;
		ft_clearline(*str,*cursor,line);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 23:59:46 by yabakhar          #+#    #+#             */
/*   Updated: 2019/12/21 23:59:48 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_select.h"

void    ft_next(t_node **list, int *cursor, char **str, t_line *line)
{
    if ((*list)->next)
    {
    	(*list) = (*list)->next;
    	cur_goto(line,line->cursor_origne);
    	tputs(tgetstr("cd", 0), 0, ft_output);
    	ft_putstr((*list)->content);
    	line->len = (*list)->len;
		if (*str)
			ft_strdel(str);
		*cursor = (line->cursor_origne + (*list)->len);
    	*str = ft_strdup((*list)->content);
		cur_goto(line, *cursor);
    }
}

void    ft_prev(t_node **list, int *cursor, char **str, t_line *line)
{
    if ((*list)->prev)
    {
    	(*list) = (*list)->prev;
    	cur_goto(line,line->cursor_origne);
    	tputs(tgetstr("cd", 0), 0, ft_output);
    	ft_putstr((*list)->content);
    	line->len = (*list)->len;
		if (*str)
			ft_strdel(str);
		*cursor = (line->cursor_origne + (*list)->len);
    	*str = ft_strdup((*list)->content);
		cur_goto(line, *cursor);
    }
}

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

void    ft_next(t_node **head,t_node **list, int *cursor, char **str, t_line *line)
{
	if (!(*list) && (*head))
	{
		*list = *head;
		ft_stock(*str, head, ft_strlen(*str));
	}
	else if ((*list) && (*list)->next)
	{
		if (!(*list)->prev)
		{
			ft_stock(*str, list, (*list)->len);
			(*list) = (*list)->next;
		}
		(*list) = (*list)->next;
	}
	else
		ft_putstr(tgetstr("bl", NULL));
	if (list && (*list))
	{
		cur_goto(line, line->cursor_origne);
	 	tputs(tgetstr("cd", 0), 0, ft_output);
	 	ft_putstr((*list)->content);
	 	line->len = (*list)->len;
		ft_strdel(str);
		*cursor = line->cursor_origne + (*list)->len;
		*str = ft_strdup((*list)->content);
		cur_goto(line, *cursor);
	}
}

void		ft_prev(t_node **head, t_node **list, int *cursor, char **str, t_line *line)
{
	if ((*list))
		(*list) = (*list)->prev;
	if ((*list))
    {
    	cur_goto(line,line->cursor_origne);
    	tputs(tgetstr("cd", 0), 0, ft_output);
    	ft_putstr((*list)->content);
    	line->len = (*list)->len;
		ft_strdel(str);
		*cursor = line->cursor_origne + (*list)->len;
		*str = ft_strdup((*list)->content);
		cur_goto(line, *cursor);
    }
	else
		ft_putstr(tgetstr("bl", NULL));
	if ((*list) && !(*list)->prev)
	{
		(*list) = NULL;
		(*head) = (*head)->next;
		ft_strdel(&(*head)->prev->content);
		ft_memdel((void**)&(*head)->prev);
		(*list) = NULL;
	}
}
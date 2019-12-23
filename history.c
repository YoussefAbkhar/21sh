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

void	ft_end(t_node **head,t_node **list, int *cursor, char **str, t_line *line)
{
	ft_stock(*str, head,line->len);
	list = head;
	cur_goto(line,line->cursor_origne);
	tputs(tgetstr("cd", 0), 0, ft_output);
	ft_strdel(str);
	line->len = 0;
	get_cursor_position(line);
	cur_goto(line,line->cursor);
	*cursor = line->cursor;
	line->first = 0;
}

void    ft_next(t_node *head,t_node **list, int *cursor, char **str, t_line *line)
{
	if ((*list) == NULL)
		*list = head;
	else if  (line->first && list &&  (*list) && (*list)->next)
		(*list) = (*list)->next;
    if (list  && (*list))
    {
    	cur_goto(line,line->cursor_origne);
    	tputs(tgetstr("cd", 0), 0, ft_output);
    	ft_putstr((*list)->content);
    	line->len = (*list)->len;
		ft_strdel(str);
		*cursor = line->cursor_origne + (*list)->len;
    	*str = ft_strdup((*list)->content);
		cur_goto(line, *cursor);
		line->first = 1;
    }
}

t_node    *ft_prev(t_node **list, int *cursor, char **str, t_line *line)
{
	if (line->first && list && (*list))
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
		line->first = 1;
    }
	return(*list);
}
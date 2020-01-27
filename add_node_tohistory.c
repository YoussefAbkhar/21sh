/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kk.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:24:22 by yabakhar          #+#    #+#             */
/*   Updated: 2019/12/16 17:24:25 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void ft_lsttoadd(t_node **alst, t_node *new)
{
    if (*alst == NULL)
    {
        *alst = new;
        return;
    }
    (*alst)->prev = new;
    new->next = *alst;
    *alst = new;
}

void ft_stock(char *str, t_node **list, t_line *line)
{
    t_node *new;

    new = (t_node *)ft_memalloc(sizeof(t_node));
    new->b_line = line->b_line;
    new->content = ft_strdup(str);
    new->len = line->len;
    new->tabl = line->tabl;
    new->index = line->index;
    new->t_len = line->c_len;
    ft_lsttoadd(list, new);
}
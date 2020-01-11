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

void ft_stock(char *str, t_node **list, int len)
{
    t_node *new;

    new = (t_node *)ft_memalloc(sizeof(t_node));
    new->content = ft_strdup(str);
    new->len = len;
    ft_lsttoadd(list, new);
}
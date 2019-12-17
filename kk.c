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

#include "ft_select.h"

int     main(int ac,char **av)
{
        char *str;
        int i = 0;
        str = "012   3456 567 89";
           
        while (str[i])
        {
                if (!ft_isalnum(str[i]))
                        break;
                i++;
        }
        while (str[i])
        {
                if (ft_isalnum(str[i]))
                        break;
                i++;
        }
        ft_putnbr(i);                                                                                                                      
}

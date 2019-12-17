/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:55:33 by yabakhar          #+#    #+#             */
/*   Updated: 2019/12/02 12:55:46 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

# define UP 4283163
# define DOWN 4348699
# define LEFT 4479771
# define RIGHT 4414235
# define SPACE 32
# define DEL 127
# define END 10
# define ESC 27
# define ALTRTH 26139
# define ALTLFT 25115

typedef struct		s_init
{
	int				k;
	int				r;
	char			*str;
	char			*tmp;
}					t_init;


typedef struct		s_line
{
	int				col;
	int				row;
	int				len;
	int				cursor;
	int				cursor_origne;
}					t_line;
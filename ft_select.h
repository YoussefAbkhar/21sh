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
# define HOME 4741915
# define DEEP 4610843

typedef struct		s_init
{
	int				k;
	int				r;
	char			*str;
	char			c[2];
	char			*tmp;
}					t_init;

typedef struct		s_node
{
	int				len;
	char			*content;
	struct s_node   *next;
	struct s_node   *prev;
}					t_node;

typedef struct		s_line
{
	int				col;
	int				row;
	int				len;
	int				cursor;
	char			*tmp;
	int				intmp;
	int 			tmp_len;
	int				cursor_origne;
	int				first;
}					t_line;

void        ft_stock(char *str,t_node **list, int len);
int			ft_output(int str);
void		cur_goto(t_line *line, int cursor);
void		ft_alt_rth(char *str,t_line *line, int *cursor);
void		ft_alt_lft(char *str,t_line *line, int *cursor);
void    	ft_clearline(char *str,int cursor,t_line *line);
void    	ft_printnbl(char **str,t_line *line, t_init *init,int *cursor);
void		ft_delet(char **str,t_line *line, int *cursor);
void    	ft_next(t_node **head,t_node **list, int *cursor, char **str, t_line *line);
void		ft_prev(t_node **head, t_node **list, int *cursor, char **str, t_line *line);
void		get_cursor_position(t_line *line);
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/04 16:23:24 by lterrail          #+#    #+#              #
#    Updated: 2018/06/01 16:06:20 by lterrail         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

CFLAGS	+= -Werror -Wextra -Wall

CFLAGS	+=	-Iincludes

SRCS	=	utils.c							\
			utils_printf.c					\
			utils_llitoa.c					\
			ft_printf.c						\
			ft_conversions.c				\
			ft_specifiers.c					\
			ft_modificateurs.c				\
			ft_print_resultat.c				\
			ft_print_color.c				\
			specifiers/ft_printf_s.c		\
			specifiers/ft_printf_smaj.c		\
			specifiers/ft_printf_d.c		\
			specifiers/ft_printf_c.c		\
			specifiers/ft_printf_x_p.c		\
			specifiers/ft_printf_o.c		\
			specifiers/ft_printf_u.c		\
			specifiers/ft_printf_pourcent.c

OBJS	=	$(addprefix srcs/, $(SRCS:.c=.o))

$(NAME):	 $(OBJS)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

all:		$(NAME)

clean:
		rm -rf $(OBJS)

fclean:	clean
		rm -rf $(NAME)

re:		fclean all

.PHONY: all clean fclean re

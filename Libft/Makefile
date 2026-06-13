# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ifreire <ifreire@student.42sp.org.br>    +#+  +:+       +#+           #
#                                                 +#+#+#+#+#+   +#+             #
#    Created: 2026/05/29 00:00:00 by ifreire           #+#    #+#               #
#    Updated: 2026/06/13 00:00:00 by ifreire          ###   ########.fr         #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_strlen.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I ./ -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

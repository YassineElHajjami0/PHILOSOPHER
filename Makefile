# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 14:54:35 by yel-hajj          #+#    #+#              #
#    Updated: 2023/04/06 14:47:50 by yel-hajj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCMAN = philo.c \
		parsing.c \
		lst.c \
		routine.c \
		print_it.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar cr
FRM = rm -rf

NAME = philosopher 
BN = philo_bonus
HEADER = philosophers.h

all: $(NAME)

$(NAME): $(SRCMAN) $(HEADER)
	$(CC) $(CFLAGS) $(SRCMAN) -o $(NAME)

clean:
	$(FRM) $(NAME)

fclean: clean
	$(FRM) $(BN)

re: fclean all
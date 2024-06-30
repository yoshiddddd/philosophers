# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 13:10:54 by yoshidakazu       #+#    #+#              #
#    Updated: 2024/06/30 13:35:53 by yoshidakazu      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
SRC = main.c routine.c init.c threads.c ft_atoi.c check.c utils.c message.c observer.c
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

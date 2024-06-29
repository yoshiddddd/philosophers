# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 13:10:54 by yoshidakazu       #+#    #+#              #
#    Updated: 2024/06/29 16:37:19 by kyoshida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
SRC = src/main.c src/routine.c src/init.c src/threads.c src/ft_atoi.c src/check.c src/utils.c src/message.c src/observer.c
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -pthread -g

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

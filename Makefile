# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 13:10:54 by yoshidakazu       #+#    #+#              #
#    Updated: 2024/06/16 15:18:57 by yoshidakazu      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRC = main.c routine.c init.c threads.c ft_atoi.c  destroy_mutex.c

MANPATH = $(addprefix ./src/, $(SRC))

FLAGS = -O3 -pthread -fsanitize=address

# -Wall -Wextra -Werror 




HEADER = ./src/philo.h

# SANITIZER = -fsanitize=thread

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME): $(MANPATH) $(HEADER)
	@cc $(FLAGS) -o $(NAME) $(MANPATH) $(SANITIZER)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all
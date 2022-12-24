# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/27 06:00:36 by mcesar-d          #+#    #+#              #
#    Updated: 2022/12/23 09:19:17 by mcesar-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = auxs.c init_control.c philo.c utils.c

FLAGS = -g -pthread -Werror -Wextra -Wall 

OBJS = ${SRCS:.c=.o}

$(NAME) : $(OBJS)
	gcc $(FLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all make clean

.PHONY: clean fclean re

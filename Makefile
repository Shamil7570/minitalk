# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: medeana <medeana@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 18:55:18 by medeana           #+#    #+#              #
#    Updated: 2021/11/19 18:55:35 by medeana          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server
NAME2 = client
SRC = ft_server.c 
SRC2 = ft_client.c

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME) $(NAME2)

$(NAME):
	${CC} ${FLAGS} $(SRC) -o $(NAME)
$(NAME2):
	${CC} ${FLAGS} $(SRC2) -o $(NAME2)
clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME2)

re: fclean all

.PHONY : all clean fclean re 
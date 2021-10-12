# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/02 20:18:35 by jwon              #+#    #+#              #
#    Updated: 2021/10/12 16:38:29 by jwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_container

SRCS	= test/main.cpp \
				test/Map.cpp \
				test/Stack.cpp \
				test/Vector.cpp \

OBJS	= $(SRCS:.cpp=.o)

HEADER = -I ./includes

CC		= clang++

FLAGS	= -std=c++98 -Wall -Wextra -Werror -fsanitize=address -g3

$(NAME):
	$(CC) $(FLAGS) $(SRCS) -o $(NAME) $(HEADER)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
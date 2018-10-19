# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ihuang <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/02 13:35:39 by ihuang            #+#    #+#              #
#    Updated: 2018/10/07 15:33:55 by ihuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = b_ls
SRCS = main.c ft_string.c mkll.c sortll.c printll.c params.c ls.c
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):

	@gcc $(FLAGS) -o $(NAME) $(SRCS)

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all

norm:
	norminette $(SRCS) b_ls.h

sanitize:
	clang -fsanitize=address $(FLAGS) -o $(NAME) $(SRCS)

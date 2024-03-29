# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfrank <lfrank@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/27 15:59:06 by lfrank            #+#    #+#              #
#    Updated: 2023/06/27 16:48:10 by lfrank           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo

CC			= gcc

#CFLAGS		=	-Wall -Werror -Wextra -g -pthread
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g

RM			= rm -f 

SRC			= ./src/main.c ./src/ft_initialization.c ./src/ft_parsing.c \
				./src/ft_philosophers.c ./src/ft_routine.c ./src/ft_utils.c \
				./src/ft_print.c 

OBJS = ${SRC:%.c=%.o}

all		: $(NAME)

$(NAME)	: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean	: 
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)


re		: fclean all
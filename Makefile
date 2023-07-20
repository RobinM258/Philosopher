# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romartin <romartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 15:07:15 by romartin          #+#    #+#              #
#    Updated: 2023/06/02 15:55:48 by romartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

SRCS = main.c ft_atoi.c 
FLAG    = -Wall -Werror -Wextra
OBJS	=  ${SRCS:.c=.o}

.c.o	:
		@gcc -Wall -Wextra -Werror -c $^
${NAME} : ${OBJS}
		@gcc -o ${NAME} ${OBJS}

all : ${NAME}

clean :
		@rm -f ${OBJS}

fclean : clean
		@rm -f ${NAME}

re : fclean all
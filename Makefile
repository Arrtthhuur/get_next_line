# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abeznik <abeznik@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/17 13:58:28 by abeznik       #+#    #+#                  #
#    Updated: 2020/11/21 10:04:27 by abeznik       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRCS	=	get_next_line.c $\
			get_next_line_utils.c $\
			gnl_test.c

MAINS	=	main.c $\
			main_test.c

OBJS	=	$(SRCS:.c=.o)

MAIN	=	$(MAINS:.c=.o)

CC		=	gcc
RM		=	rm -f
CFLAGS	=	-I. -Werror -Wextra -Wall -D BUFFER_SIZE=32

NAME	=	get_next_line.a

all:		$(NAME)

$(NAME): 	$(OBJS)
	ar cr $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)
	@echo "[INFO] Objects removed!"
	
fclean:		clean
	$(RM) $(NAME)
	@echo "[INFO] Library [$(NAME)] removed!"

mclean:
	$(RM) $(MAIN)

oclean:
	$(RM) *.out

test:		gnl_test.o main_test.o
	$(CC) -o test.out gnl_test.o main_test.o

gnl:		get_next_line.o main.o get_next_line_utils.o
	$(CC) -o gnl.out get_next_line.o main.o get_next_line_utils.o
	@echo "[INFO] Executable [$(NAME)] created!"

del:		mclean oclean fclean

re:			fclean all

.PHONY:		all clean fclean mclean re

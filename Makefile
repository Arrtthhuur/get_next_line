# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abeznik <abeznik@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/17 13:58:28 by abeznik       #+#    #+#                  #
#    Updated: 2020/12/04 11:19:47 by abeznik       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRCS	=	get_next_line.c $\
			get_next_line_utils.c $\
			gnl.c $\
			gnl_test.c $\
			gnl_two.c

MAINS	=	main.c $\
			main_test.c

OBJS	=	$(SRCS:.c=.o)

MAIN	=	$(MAINS:.c=.o)

CC		=	gcc
RM		=	rm -f
CFLAGS	=	-D BUFFER_SIZE=5

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

test:		gnl.o main.o get_next_line_utils.o
	$(CC) -o test gnl.o main.o get_next_line_utils.o

test2:		gnl_test.o main.o get_next_line_utils.o
	$(CC) -o gnl_test gnl_test.o main.o get_next_line_utils.o

two:		gnl_two.o main.o get_next_line_utils.o
	$(CC) -o two gnl_two.o main.o get_next_line_utils.o

gnl:		get_next_line.o main.o get_next_line_utils.o
	$(CC) -o gnl get_next_line.o main.o get_next_line_utils.o
	@echo "[INFO] Executable [$(NAME)] created!"

del:		mclean oclean fclean
	@echo "[INFO] .out removed!"

re:			fclean all

.PHONY:		all clean fclean mclean re

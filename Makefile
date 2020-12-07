# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abeznik <abeznik@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/17 13:58:28 by abeznik       #+#    #+#                  #
#    Updated: 2020/12/07 15:42:09 by abeznik       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRCS	=	get_next_line.c $\
			get_next_line_utils.c $\
			gnl._comc $\

MAINS	=	main.c $\

OBJS	=	$(SRCS:.c=.o)

MAIN	=	$(MAINS:.c=.o)

CC		=	gcc
RM		=	rm -f
CFLAGS	=	-D BUFFER_SIZE=0

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

com:		gnl_com.o main.o get_next_line_utils.o
	$(CC) -o com.out gnl_com.o main.o get_next_line_utils.o

gnl:		get_next_line.o main.o get_next_line_utils.o
	$(CC) -o gnl.out get_next_line.o main.o get_next_line_utils.o
	@echo "[INFO] Executable [$(NAME)] created!"

del:		mclean oclean fclean
	@echo "[INFO] .out removed!"

re:			fclean all

.PHONY:		all clean fclean mclean re

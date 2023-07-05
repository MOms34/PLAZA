##
## EPITECH PROJECT, 2023
## eitech
## File description:
## momo
##

CC 		= 	g++

MAIN	=	SRC/main/main.cpp

FILES	=	$(wildcard ./SRC/*.cpp)

SRC 	=	$(MAIN)		\
			$(FILES)

RM 		= 	rm -f

NAME 	= 	plazza

CFLAGS 	= 	-Wall -Werror -pthread -I include/

OBJ		=	$(SRC:.cpp=.o)



all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ)
	find . -name '*~' -delete -o -name '#*#' -delete -o -name '*.gcno' \
		-delete -o -name -'*.gcdo' -delete -o -name '*.gcda' -delete

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re

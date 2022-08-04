# ################################## #
#               COMMAND              #
# ################################## #
CC			=	clang++
MKDIR		=	mkdir -p
RM			=	rm -rf

# ################################## #
#              EXEC NAME             #
# ################################## #
NAME		=	containers

# ################################## #
#               SOURCES              #
# ################################## #
# SRC_DIR		= 	./
SRC			=	main.cpp
SRC_MAP		=	main_map.cpp

# ################################## #
#               OBJECTS              #
# ################################## #
OBJ			:=	${SRC:.cpp=.o}
OBJ_MAP		:=	${SRC_MAP:.cpp=.o}

# ################################## #
#                FLAGS               #
# ################################## #
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -I.

# ################################## #
#                RULES               #
# ################################## #

${NAME}: ${OBJ}
	$(CC) ${CFLAGS} ${OBJ} -o $@ 

all:	${NAME}

ft_map: ${OBJ_MAP}
		$(CC) ${CFLAGS} -o ft_map ${SRC_MAP}

std_map: ${OBJ_MAP}
		$(CC) ${CFLAGS} -D STD -o std_map ${SRC_MAP}

ft:	${OBJ}
	$(CC) ${CFLAGS} -o $(NAME) ${SRC}

std:	${OBJ}
	$(CC) ${CFLAGS} -D STD -o $(NAME) ${SRC}

clean:
	${RM} ${OBJ} ${OBJ_MAP}

fclean: clean
	${RM} ${NAME}
	${RM} ft_map std_map

re: clean all

reft_map: fclean ft_map

restd_map: fclean std_map

reft: fclean ft

restd: fclean std

fre: fclean all

%.o: %.cpp
		$(CC) $(CFLAGS) -o $@ -c $<

-include ${DEP}

.PHONY: all clean fclean re fre
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
SRC_VECTOR	=	vector/main_vector.cpp
SRC_STACK	=	stack/main_stack.cpp
SRC_MAP		=	map/main_map.cpp

# ################################## #
#               OBJECTS              #
# ################################## #
OBJ_VECTOR	:=	${SRC_VECTOR:.cpp=.o}
OBJ_MAP		:=	${SRC_MAP:.cpp=.o}
OBJ_STACK	:=	${SRC_STACK:.cpp=.o}

# ################################## #
#                FLAGS               #
# ################################## #
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -I.

# ################################## #
#                RULES               #
# ################################## #

${NAME}: vector map stack

all:	${NAME}

vector: ft_vector std_vector

stack: ft_stack std_stack

map: ft_map std_map

ft_map: ${OBJ_MAP}
		$(CC) ${CFLAGS} -o ft_map ${SRC_MAP}

std_map: ${OBJ_MAP}
		$(CC) ${CFLAGS} -D STD -o std_map ${SRC_MAP}

ft_vector:	${OBJ_VECTOR}
	$(CC) ${CFLAGS} -o ft_vector ${SRC_VECTOR}

std_vector:	${OBJ_VECTOR}
	$(CC) ${CFLAGS} -D STD -o std_vector ${SRC_VECTOR}

ft_stack:	${OBJ_STACK}
	$(CC) ${CFLAGS} -o ft_stack ${SRC_STACK}

std_stack:	${OBJ_STACK}
	$(CC) ${CFLAGS} -D STD -o std_stack ${SRC_STACK}

clean:
	${RM} ${OBJ_VECTOR} ${OBJ_STACK} ${OBJ_MAP}

fclean: clean
	${RM} ${NAME}
	${RM} ft_map std_map ft_vector std_vector ft_stack std_stack ft_set std_set

re: clean all

reft_vector: fclean ft_vector

restd_vector: fclean std_vector

revector: fclean ft_vector std_vector

reft_stack: fclean ft_stack

restd_stack: fclean std_stack

restack: fclean ft_stack std_stack

reft_map: fclean ft_map

restd_map: fclean std_map

remap: fclean ft_map std_map

fre: fclean all

%.o: %.cpp
		$(CC) $(CFLAGS) -o $@ -c $<

-include ${DEP}

.PHONY: all clean fclean re fre
# ################################## #
#               COMMAND              #
# ################################## #
CXX			=	c++
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
SRC			=	main.cpp \

# ################################## #
#               OBJECTS              #
# ################################## #
OBJ			=	${SRC:.cpp=.o}

# ################################## #
#                FLAGS               #
# ################################## #
CXXFLAGS		=	-Wall -Wextra -Werror 
CXXFLAGS		+=	-std=c++98
# CXXFLAGS		+=	-I ./

# ################################## #
#                RULES               #
# ################################## #

${NAME}: ${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -o $@ 

#all:	${NAME}

ft:	${OBJ}
	${CXX} ${CXXFLAGS} -o $(NAME) ${SRC}

std:	${OBJ}
	${CXX} ${CXXFLAGS} -D STD -o $(NAME) ${SRC}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: clean all

reft: fclean ft

restd: fclean std

fre: fclean all

-include ${DEP}

.PHONY: all clean fclean re fre
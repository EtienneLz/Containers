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
OBJ_DIR		=	./
OBJ			=	${SRC:.cpp=.o}
OBJ			:=	${addprefix ${OBJ_DIR}, ${OBJ}}

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

all:	${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: clean all

fre: fclean all

-include ${DEP}

.PHONY: all clean fclean re fre
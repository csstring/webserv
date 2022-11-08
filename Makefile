CXX= c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address
SRCS = main.cpp Parser.cpp
OBJS = ${SRCS:.cpp=.o}
RM = rm -f
INCLUDE = -I./include/
NAME = webserv

all : $(NAME)

$(NAME) : ${OBJS}
		${CXX} ${CXXFLAGS} ${OBJS} -o webserv

%.o : %.cpp
		${CXX} ${CXXFLAGS} -c $< -o ${<:.cpp=.o} ${INCLUDE}

clean :
		${RM} ${OBJS}

fclean : clean
		${RM} $(NAME)
re : 
	${MAKE} fclean 
	${MAKE} all

.PHONY: all clean fclean re
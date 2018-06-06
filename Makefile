NAME	= client

CC	= g++

RM	= rm -f

SRCS	= ./source/main.cpp	\
		  ./source/Network.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -W -Wall -Wextra -g3 -std=c++11

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

NAME		= ft_container

STDNAME	= std_container

CC			= clang++

FLAGS		= -Wall -Wextra -Werror -std=c++98

SRCS		= main.cpp \
					test_map.cpp \
					test_set.cpp \
					test_vector.cpp

STDSRCS	= main_std.cpp \
					test_map_std.cpp \
					test_set_std.cpp \
					test_vector_std.cpp

OBJS		= $(SRCS:.cpp=.o)

STDOBJS	= $(STDSRCS:.cpp=.o)

all					: $(NAME) $(STDNAME)

$(NAME)			:
							$(CC) $(FLAGS) -c $(SRCS)
							$(CC) $(OBJS) -o $(NAME)

$(STDNAME)	:
							$(CC) $(FLAGS) -c $(STDSRCS)
							$(CC) $(STDOBJS) -o $(STDNAME)

clean				:
							rm -rf $(OBJS) $(STDOBJS)

fclean			: clean
							rm -rf $(NAME) $(STDNAME)

re					: fclean all

NAME	= pipex

SRCS	= srcs/pipex.c srcs/utils.c srcs/getpath.c
OBJS	= $(SRCS:%.c=%.o)

CC		= gcc
LIBFT	= ./libft
CFLAGS	= -Wall -Werror -Wextra -I./srcs -I$(LIBFT)
RM		= rm -f

all		: $(NAME)

%.o		: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -o $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT)

clean	:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT) clean

fclean	: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT) clean

re		: fclean all

.PHONY	: all clean fclean re

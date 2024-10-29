# Standard
NAME			= libft.a

# Directories
INC				= inc/
SRCS			= srcs/
OBJS			= objs/

# Compiler and Flags
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -I
RM				= rm -f
AR				= ar rcs

# Source Files
CTYPE_DIR		=	$(SRCS)ctype/ft_isalnum.c \
					$(SRCS)ctype/ft_isalpha.c \
					$(SRCS)ctype/ft_isascii.c \
					$(SRCS)ctype/ft_isdigit.c \
					$(SRCS)ctype/ft_isprint.c \
					$(SRCS)ctype/ft_tolower.c \
					$(SRCS)ctype/ft_toupper.c

MEM_DIR			=	$(SRCS)mem/ft_bzero.c \
					$(SRCS)mem/ft_calloc.c \
					$(SRCS)mem/ft_memchr.c \
					$(SRCS)mem/ft_memcmp.c \
					$(SRCS)mem/ft_memcpy.c \
					$(SRCS)mem/ft_memmove.c \
					$(SRCS)mem/ft_memset.c


STRING_DIR		=	$(SRCS)string/ft_atoi.c \
					$(SRCS)string/ft_itoa.c \
					$(SRCS)string/ft_putchar_fd.c \
					$(SRCS)string/ft_putendl_fd.c \
					$(SRCS)string/ft_putnbr_fd.c \
					$(SRCS)string/ft_putstr_fd.c \
					$(SRCS)string/ft_split.c \
					$(SRCS)string/ft_strchr.c \
					$(SRCS)string/ft_strdup.c \
					$(SRCS)string/ft_striteri.c \
					$(SRCS)string/ft_strjoin.c \
					$(SRCS)string/ft_strlcat.c \
					$(SRCS)string/ft_strlcpy.c \
					$(SRCS)string/ft_strlen.c \
					$(SRCS)string/ft_strmapi.c \
					$(SRCS)string/ft_strncmp.c \
					$(SRCS)string/ft_strnstr.c \
					$(SRCS)string/ft_strrchr.c \
					$(SRCS)string/ft_strtrim.c \
					$(SRCS)string/ft_substr.c

LIST_DIR		=	$(SRCS)list/ft_lstadd_back.c \
					$(SRCS)list/ft_lstadd_front.c \
					$(SRCS)list/ft_lstclear.c \
					$(SRCS)list/ft_lstdelone.c \
					$(SRCS)list/ft_lstiter.c \
					$(SRCS)list/ft_lstlast.c \
					$(SRCS)list/ft_lstmap.c \
					$(SRCS)list/ft_lstnew.c \
					$(SRCS)list/ft_lstsize.c

FTPRINTF_DIR	=	$(SRCS)ft_printf/ft_printf.c \
					$(SRCS)ft_printf/ft_printwords.c \
					$(SRCS)ft_printf/ft_printnums.c

GNL_DIR			=	$(SRCS)get_next_line/get_next_line.c

# Concatenate all source files
SRC 			= $(CTYPE_DIR) $(MEM_DIR) $(STRING_DIR) $(LIST_DIR) $(FTPRINTF_DIR) $(GNL_DIR)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJS
OBJ 			= $(patsubst $(SRCS)%.c,$(OBJS)%.o,$(SRC))

# Build rules
all: 			$(NAME)

$(NAME): 		$(OBJ)
				@$(AR) $(NAME) $(OBJ)

$(OBJS)%.o:	$(SRCS)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
				@$(RM) -r $(OBJS)

fclean: 		clean
				@$(RM) $(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re

#sources files
SRC = ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_memset.c ft_bzero.c ft_memcpy.c \
ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c \
ft_memchr.c ft_memcmp.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strtrim.c ft_strmapi.c ft_striteri.c \
ft_strjoin.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_printf/ft_printf.c ft_printf/ft_count.c ft_printf/ft_count_unsigned.c ft_printf/ft_count_hex.c \
ft_printf/ft_putnbr_unsigned_fd.c ft_printf/ft_putnbr_hex_fd.c ft_printf/ft_display_c.c ft_printf/ft_display_s.c \
ft_printf/ft_display_i.c ft_printf/ft_display_psign.c ft_printf/ft_display_u.c ft_printf/ft_display_x.c \
ft_printf/ft_display_p.c get_next_line/get_next_line.c
#append .o to each .c files in the SRC
#OBJS := $(SRC:%.c=%.o)
OBJS = ${SRC:.c=.o}
#build target name
NAME = libft.a
#compiler
CC = gcc
#compiler flags
CCFLAGS = -Wall -Wextra -Werror
#include directory == dossier includes
INC_DIR = .
#preprocessor flag
CPPFLAGS = -I $(INC_DIR)
#rm
RM = rm -f
#archive
ARNAME = ar rcs $(NAME)
#first rull is always "all" she is calling $(NAME)
all: $(NAME)
#NAME  "@"hide in command in terminal
$(NAME): $(OBJS)
	@$(ARNAME) $(OBJS)
# "%.o" rule compie .c file into corresponding .o file
# "%" is a wildcard for "name of the files without extension"
# $@ = target, here target = .o "$<" = first dependencies here = .c
%.o: %.c
	$(CC) $(CPPFLAGS) $(CCFLAGS) -o $@ -c $<
#clean delete all .o files
clean:
	$(RM) $(OBJS)
#after executing clean delete the lib
fclean: clean
	$(RM) $(NAME)
#delete everything then re create it
re: fclean all
#phony targets
.PHONY: all clean fclean re

SRC = ./src/ft_abs.c \
	  ./src/ft_bzero.c \
	  ./src/ft_atoi.c \
	  ./src/ft_atoi2.c \
	  ./src/ft_isalnum.c \
	  ./src/ft_isalpha.c \
	  ./src/ft_isascii.c \
	  ./src/ft_isdigit.c \
	  ./src/ft_isprint.c \
	  ./src/ft_itoa.c \
	  ./src/ft_lstadd.c \
	  ./src/ft_lstdel.c \
	  ./src/ft_lstdelone.c \
	  ./src/ft_lstiter.c \
	  ./src/ft_lstlen.c \
	  ./src/ft_lstmap.c \
	  ./src/ft_lstnew.c \
	  ./src/ft_memalloc.c \
	  ./src/ft_memccpy.c \
	  ./src/ft_memchr.c \
	  ./src/ft_memcmp.c \
	  ./src/ft_memcpy.c \
	  ./src/ft_memdel.c \
	  ./src/ft_memmove.c \
	  ./src/ft_memset.c \
	  ./src/ft_putchar.c \
	  ./src/ft_putchar_fd.c \
	  ./src/ft_putendl.c \
	  ./src/ft_putendl_fd.c \
	  ./src/ft_putnbr.c \
	  ./src/ft_putnbr_fd.c \
	  ./src/ft_putstr.c \
	  ./src/ft_putstr_fd.c \
	  ./src/ft_strcat.c \
	  ./src/ft_strchr.c \
	  ./src/ft_strclr.c \
	  ./src/ft_strcmp.c \
	  ./src/ft_strcpy.c \
	  ./src/ft_strdel.c \
	  ./src/ft_strdup.c \
	  ./src/ft_strequ.c \
	  ./src/ft_striter.c \
	  ./src/ft_striteri.c \
	  ./src/ft_strjoin.c \
	  ./src/ft_strlcat.c \
	  ./src/ft_strlen.c \
	  ./src/ft_strmap.c \
	  ./src/ft_strmapi.c \
	  ./src/ft_strncat.c \
	  ./src/ft_strncmp.c \
	  ./src/ft_strncpy.c \
	  ./src/ft_strnequ.c \
	  ./src/ft_strnew.c \
	  ./src/ft_strnstr.c \
	  ./src/ft_strrchr.c \
	  ./src/ft_strsplit.c \
	  ./src/ft_strstr.c \
	  ./src/ft_strsub.c \
	  ./src/ft_strtoi.c \
	  ./src/ft_strtou.c \
	  ./src/ft_strtrim.c \
	  ./src/ft_swap.c \
	  ./src/ft_tolower.c \
	  ./src/ft_toupper.c \
	  ./src/ft_putptr.c \
	  ./src/ft_itoa_base.c \
	  ./src/ft_putnbr_base.c \
	  ./src/ft_max.c \
	  ./src/ft_min.c \
	  ./src/ft_writeendl.c \
	  ./src/ft_get_line.c \
	  ./src/ft_strcnt.c \
	  ./src/ft_putwchar.c \
	  ./src/ft_putwstr.c \
	  ./src/ft_putwchar_fd.c \
	  ./src/ft_putwstr_fd.c \
	  ./src/ft_printf_core.c \
	  ./src/ft_printf_fd.c \
	  ./src/ft_printf.c \
	  ./src/ft_printf_char.c \
	  ./src/ft_printf_handlings.c \
	  ./src/ft_printf_noconv.c \
	  ./src/ft_printf_parser.c \
	  ./src/ft_printf_signed_decimal.c \
	  ./src/ft_printf_signedtostr.c \
	  ./src/ft_printf_string.c \
	  ./src/ft_printf_unsigned_decimal.c \
	  ./src/ft_printf_unsigned_hex.c \
	  ./src/ft_printf_unsigned_octal.c \
	  ./src/ft_printf_unsignedtostr_base.c \
	  ./src/ft_printf_utils.c \
	  ./src/ft_printf_wchar.c \
	  ./src/ft_printf_wstring.c \
	  ./src/ft_vecnew.c \
	  ./src/ft_vecadd.c \
	  ./src/ft_vecreserve.c \
	  ./src/ft_vecresize.c \
	  ./src/ft_vecat.c \
	  ./src/ft_vecdel.c \
	  ./src/ft_options.c \
	  ./src/ft_options_utils.c

OBJ=$(addprefix obj/,$(notdir $(SRC:.c=.o)))
DEP=$(addprefix .d/,$(notdir $(SRC:.c=.d)))

CC=gcc
CFLAGS=-Wall -Werror -Wextra -O2
COMPILE.c=$(CC) $(CFLAGS) -c
OUTPUT_OPTION= -MMD -MP -MF $(patsubst %.o,.d/%.d,$(notdir $@)) -o $@

obj/%.o: src/%.c
	@mkdir -p obj/
	@mkdir -p .d/
	$(COMPILE.c) $(OUTPUT_OPTION) $< -I./include

NAME=libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@ /bin/echo -n "Creating library => "
	@ if ar rc $(NAME) $(OBJ) ; \
		then /bin/echo ✅; \
		else /bin/echo ❌ ; fi
	@ ranlib $(NAME)
	@ echo "Finished"

clean:
	rm -rf .d/
	rm -rf obj/

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP)

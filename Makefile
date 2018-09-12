SRC = src/file_mapper.c \
	  src/utils.c \
	  src/archive_reader.c \
	  src/fat.c

NM_SRC = src/nm.c \
		 src/nm_symbol_table_32.c \
		 src/nm_symbol_table_64.c \
		 src/nm_sections_32.c \
		 src/nm_sections_64.c \
		 src/nm_sorted_print.c

OTOOL_SRC = src/otool.c	\
			src/otool_print_text_section_32.c \
			src/otool_print_text_section_64.c

OBJ=$(addprefix obj/,$(notdir $(SRC:.c=.o)))
DEP=$(addprefix .d/,$(notdir $(SRC:.c=.d)))

NM_OBJ=$(addprefix obj/,$(notdir $(NM_SRC:.c=.o)))
NM_DEP=$(addprefix .d/,$(notdir $(NM_SRC:.c=.d)))

OTOOL_OBJ=$(addprefix obj/,$(notdir $(OTOOL_SRC:.c=.o)))
OTOOL_DEP=$(addprefix .d/,$(notdir $(OTOOL_SRC:.c=.d)))


CC=gcc
CFLAGS=-Wall -Werror -Wextra -O2
LDFLAGS=
COMPILE.c=$(CC) $(CFLAGS) -c
LINK.o=$(CC) $(LDFLAGS)
OUTPUT_OPTION= -MMD -MP -MF $(patsubst %.o,.d/%.d,$(notdir $@)) -o $@

obj/%.o: src/%.c
	@mkdir -p obj/
	@mkdir -p .d/
	$(COMPILE.c) $(OUTPUT_OPTION) $< -Iinclude -Ilibft/include/

NM = nm
OTOOL = otool

.PHONY: all clean fclean re

all: $(NM) $(OTOOL)

$(NM): libft/libft.a $(OBJ) $(NM_OBJ)
	$(LINK.o) -o $@ $(OBJ) $(NM_OBJ) -Llibft -lft

$(OTOOL): libft/libft.a $(OBJ) $(OTOOL_OBJ)
	$(LINK.o) -o $@ $(OBJ) $(OTOOL_OBJ) -Llibft -lft

clean:
	make -C libft clean
	rm -rf .d/
	rm -rf obj/

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

libft/libft.a:
	make -C libft

-include $(DEP)
-include $(NM_DEP)
-include $(OTOOL_DEP)

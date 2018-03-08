SOURCE_FILES = file_mapper.c

SOURCE_DIR = src/
SOURCES = $(addprefix $(SOURCE_DIR), $(SOURCE_FILES))


OBJECT_FILES = $(SOURCE_FILES:.c=.o)
OBJECT_DIR = obj/
OBJECTS = $(addprefix $(OBJECT_DIR), $(OBJECT_FILES))

INCLUDE_FILES = header.h\
				internal.h
INCLUDE_DIR = include/
INCLUDES = $(addprefix $(INCLUDE_DIR), $(INCLUDE_FILES))

LIBFT_PATH = ./libft/
LIBFT_HEADER = $(LIBFT_PATH)includes/

TEST_PATH = ./test/

vpath %.c $(SOURCE_DIR)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
OFLAGS = -O2

NM = nm
OTOOL = otool

.PHONY: all clean fclean re link test

all: $(OTOOL)

$(NM): $(OBJECTS) $(OBJECT_DIR)$(NM).o
	make -C $(LIBFT_PATH)
	$(CC) $(DEBUG) -o $(NM) $(OBJECT_DIR)$(NM).o $(OBJECTS) $(LIBFT_PATH)libft.a

$(OTOOL): $(OBJECTS) $(OBJECT_DIR)$(OTOOL).o
	make -C $(LIBFT_PATH)
	$(CC) $(DEBUG) -o $(OTOOL) $(OBJECT_DIR)$(OTOOL).o $(OBJECTS) $(LIBFT_PATH)libft.a
	
$(OBJECT_DIR)%.o: %.c $(INCLUDES)
	mkdir -p $(OBJECT_DIR)
	$(CC) $(DEBUG) -c -fPIC -o $@ $(OFLAGS) $(CFLAGS) $< -I$(INCLUDE_DIR) -I$(LIBFT_HEADER)

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJECTS)
	rm -rf $(OBJECT_DIR)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NM)
	rm -f $(OTOOL)

re: fclean all

test: $(LINK)
	make -C $(TEST_PATH)

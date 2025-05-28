# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/10 00:34:01 by smamalig          #+#    #+#              #
#    Updated: 2025/05/25 14:06:06 by smamalig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       = libmlx.a
CC         = cc
CFLAGS     = -Wall -Wextra -MMD -MP
SRC_FILES  = init.c get_visual.c new_window.c loop.c pixel_put.c \
	glx_check_version.c init_opengl.c init_display.c prevent_resize.c \
	destroy_display.c destroy_window.c xpm_file_to_image.c mouse_hide.c \
	mouse_show.c mouse_move.c
TEST_FILES = triangle.test.c
SRC_DIR    = src
OBJ_DIR    = obj
TEST_DIR   = test
SRCS      := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS      := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS      := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRCS))
TESTS     := $(addprefix $(TEST_DIR)/, $(TESTS))
TEST_OBJS := $(TESTS:%.c=%.o)
INCLUDES   = -Iinclude
LDFLAGS    = -lX11 -lGL -L. -lmlx

ifeq ($(DEBUG), 1)
	CFLAGS += -Wpedantic -O0 -g3
else
	CFLAGS += -Werror -O3
endif

all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: $(TEST_OBJS)

%.test: %.test.c $(NAME)
	$(CC) $(CFLAGS) $(INCLUDES) $< $(LDFLAGS) -o $@
	./$@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	@make all
	
.PHONY: all clean fclean re

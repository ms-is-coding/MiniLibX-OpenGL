# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/10 00:34:01 by smamalig          #+#    #+#              #
#    Updated: 2025/12/12 17:26:16 by rel-qoqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project
NAME		:= libmlx.a
DEBUG_NAME	:= libmlx_debug.a

TEST_NAME	:= mlx_tests

# Directories
SRC_DIR		= src
BUILD_DIR	= build
PROJ_B_DIR	= $(BUILD_DIR)/mlx
TEST_DIR	= test
TEST_B_DIR	= $(BUILD_DIR)/test

# Compiler
CC			= cc
LDFLAGS		= -L. -lmlx -lX11 -lGL
CFLAGS		= -Wall -Wextra -Wpadded -MMD -MP -Iinclude

# Project files
SRC_FILES 	= autorepeat.c clear_window.c destroy_display.c destroy_image.c \
				destroy_window.c do_sync.c get_data_addr.c get_screen_size.c \
				get_visual.c glx_check_version.c hook.c init.c init_display.c \
				init_opengl.c loop.c loop_end.c mouse_get_pos.c mouse_hide.c \
				mouse_show.c new_image.c new_window.c pixel_put.c prevent_resize.c \
				put_image_to_window.c xpm_file_to_image.c
TEST_FILES	= image.test.c

SRCS      	:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS      	:= $(patsubst $(SRC_DIR)/%.c, $(PROJ_B_DIR)/%.o, $(SRCS))
DEPS      	:= $(OBJS:.o=.d)
TESTS     	:= $(addprefix $(TEST_DIR)/, $(TEST_FILES))
TEST_OBJS 	:= $(patsubst $(TEST_DIR)/%.c, $(TEST_B_DIR)/%.o, $(TESTS))
TEST_DEPS 	:= $(TEST_OBJS:.o=.d)

ifeq ($(DEBUG), 1)
	CFLAGS += -Wpedantic -O0 -g3
else
	CFLAGS += -Werror -O3
endif

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(PROJ_B_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_NAME)

$(TEST_NAME): $(TEST_OBJS) $(NAME)
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

$(TEST_B_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	@make all
	
.PHONY: all test clean fclean re

-include $(DEPS) $(TEST_DEPS)
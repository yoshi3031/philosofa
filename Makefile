# プログラム名
NAME = philo

# コンパイラとフラグ
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3
# -g3: デバッグ情報を付与（Valgrindで行番号を表示するために必要）

# ソースファイル (アップロードされたファイル名に合わせています)
SRCS = main.c \
       utils.c \
       write.c \
       synchro_utils.c \
       dinner.c \
       safe_functions.c \
       getter_setter.c \
       init.c \
       parse.c \
       monitor.c

OBJS = $(SRCS:.c=.o)

# ルール定義
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- テスト用コマンド ---

# 1. メモリリークチェック (make val)
val: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 5 800 200 200 7

# 2. データ競合チェック (make hell) - Helgrind
hell: re
	valgrind --tool=helgrind ./$(NAME) 5 800 200 200 7

# 4. 「1人＝死ぬ」テスト (make die)
die: re
	./$(NAME) 1 800 200 200

# 5. 「4人＝生きる」テスト (make even)
even: re
	./$(NAME) 4 410 200 200

# 6. 「5人＝生きる」テスト (make odd) - さっき修正したやつ
odd: re
	./$(NAME) 5 800 200 200

# --- 標準ルール ---

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re val hell die even odd
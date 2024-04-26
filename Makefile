PHEVAL_DIR = PokerHandEvaluator/cpp
HEADERS = -I$(PHEVAL_DIR)/include
LIBS = -L$(PHEVAL_DIR) -lpheval
FLAGS = -std=c++11 -O3
NAME = sim

all: pheval_build $(NAME)

pheval_build:
	$(MAKE) -C $(PHEVAL_DIR)

$(NAME): test.cpp
	c++ test.cpp $(FLAGS) $(HEADERS) $(LIBS) -o $(NAME)

clean:
	rm -rf sim

deepclean: clean
	$(MAKE) -C $(PHEVAL_DIR) clean

.PHONY: all pheval_build clean
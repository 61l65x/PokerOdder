PHEVAL_DIR = dependencies/PokerHandEvaluator/cpp
IMGUI_DIR = dependencies/imgui

CXX = c++
FLAGS = -std=c++11 -O3
HEADERS = -I$(PHEVAL_DIR)/include -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
LIBS = -L$(PHEVAL_DIR) -lpheval `pkg-config --cflags --libs glfw3` -lGL -ldl -lX11 -lpthread

NAME = texu-helper

SOURCES = $(shell find srcs -name "*.cpp")
IMGUI_SOURCES = $(IMGUI_DIR)/imgui.cpp \
                $(IMGUI_DIR)/imgui_draw.cpp \
                $(IMGUI_DIR)/imgui_widgets.cpp \
                $(IMGUI_DIR)/imgui_tables.cpp \
                $(IMGUI_DIR)/imgui_demo.cpp \
                $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \
                $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

all: $(NAME)

$(NAME): $(SOURCES) $(IMGUI_SOURCES)
	$(CXX) $(SOURCES) $(IMGUI_SOURCES) $(FLAGS) $(HEADERS) $(LIBS) -o $(NAME)

install_deps:
	sudo apt-get update
	sudo apt-get install -y build-essential libglfw3-dev \
                            libgl1-mesa-dev libx11-dev libglu1-mesa-dev \
                            libgl1-mesa-glx libglew-dev libglm-dev
	git submodule update --init --recursive

pheval_build: install_deps
	$(MAKE) -C $(PHEVAL_DIR)

clean:
	rm -f $(NAME)

deepclean: clean
	$(MAKE) -C $(PHEVAL_DIR) clean

.PHONY: all pheval_build install_deps clean deepclean

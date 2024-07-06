PHEVAL_DIR = dependencies/PokerHandEvaluator/cpp
IMGUI_DIR = dependencies/imgui
BUILD_DIR = build

CXX = c++
FLAGS = -std=c++11 -O3
HEADERS = -I$(PHEVAL_DIR)/include -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I./srcs/PokerOdder
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

OBJECTS = $(SOURCES:srcs/%.cpp=$(BUILD_DIR)/srcs/%.o) \
          $(IMGUI_SOURCES:$(IMGUI_DIR)/%.cpp=$(BUILD_DIR)/imgui/%.o)

DEPS = $(OBJECTS:.o=.d)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(OBJECTS) $(FLAGS) $(HEADERS) $(LIBS) -o $(NAME)

$(BUILD_DIR)/srcs/%.o: srcs/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(FLAGS) $(HEADERS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/imgui/%.o: $(IMGUI_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(FLAGS) $(HEADERS) -MMD -MP -c $< -o $@

install_deps:
	sudo apt-get update
	sudo apt-get install -y build-essential libglfw3-dev \
                            libgl1-mesa-dev libx11-dev libglu1-mesa-dev \
                            libgl1-mesa-glx libglew-dev libglm-dev
	git submodule update --init --recursive

pheval_build: install_deps
	$(MAKE) -C $(PHEVAL_DIR)

fclean:
	rm -f $(NAME)
	rm -rf $(BUILD_DIR)

deepclean: clean
	$(MAKE) -C $(PHEVAL_DIR) clean

re: clean all

-include $(DEPS)

.PHONY: re all pheval_build install_deps clean deepclean

CC=g++
CLAGS=-Wall

LIB :=-L./lib -lglew32 -lopengl32 -lSDL2

#LIB=-L./lib -lglew32 -lopengl32 -static -lSDL2 -lmingw32 -lSDL2main -lSDL2 -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid
INC=-I./include

SRC_DIR=src
BUILD_DIR = build

TARGET = $(BUILD_DIR)/main.exe

SOURCES     := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS     := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.cpp=.o))

dir_guard=@mkdir -p $(@D)

.phony: all clean

all: $(TARGET)
	
$(TARGET): $(OBJECTS)
	$(dir_guard)
	$(CC) $(CFLAGS) $^ -o $@ $(LIB) 

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(dir_guard)
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@ 

clean:
	rm -rf $(BUILD_DIR)
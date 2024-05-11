APP_NAME = Asteroids
BUILD_DIR = ./bin
C_FILES = ./src/*.c ./src/vendors/raylib/lib/libraylib.a
CFLAGS = -Wall -g

APP_DEFINES:=
APP_INCLUDES:= -I./src/vendors/raylib -framework CoreVideo -framework GLUT -framework Cocoa -framework OpenGL -framework IOKit

build:
	clang $(CFLAGS) $(C_FILES) -o $(BUILD_DIR)/$(APP_NAME) $(APP_INCLUDES)


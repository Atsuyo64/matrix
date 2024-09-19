CC = @g++
FLAGS = -DGLEW_NO_GLU -lGL -lglfw -Iglew-2.1.0/include -Iinclude -g
EXE = matrix
SRC_DIR = src
OBJ_DIR = obj

SRCS = $(shell find $(SRC_DIR) -name "*.cc")
OBJS = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.cc=.o))

#$(info $(SRCS))
#$(info $(OBJS))

all: $(OBJS) $(OBJ_DIR)/glew.o $(EXE)

$(EXE): $(OBJS) | $(OBJ_DIR)
	@echo "------- Make $(EXE) -------"
	$(CC) $(FLAGS) -o $(EXE) $(OBJS) $(OBJ_DIR)/glew.o

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc | $(OBJ_DIR)
	@echo "------- Make $@ -------"
	$(CC) $(FLAGS) -c -o $@ $<
$(OBJ_DIR):
	mkdir -p $@

#exception rule for glew
$(OBJ_DIR)/glew.o: glew-2.1.0/src/glew.c
	@echo "------- Make $@ -------"
	$(CC) $(FLAGS) -c $^ -o $@

clean:
	rm -r obj

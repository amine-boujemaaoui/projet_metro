CC=gcc
CFLAGS= -Wall -c
BUILD_DIR=build

ALL : $(BUILD_DIR) $(BUILD_DIR)/main

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/main: $(BUILD_DIR)/main.o $(BUILD_DIR)/Functions.o $(BUILD_DIR)/Liste.o $(BUILD_DIR)/Malloc.o $(BUILD_DIR)/Set.o
	$(CC) -Wall $^ -o $@

$(BUILD_DIR)/main.o: src/main.c include/includes.h include/Functions.h include/Struct.h include/Liste.h include/Malloc.h include/Set.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/Functions.o: src/files/Functions.c include/Functions.h include/Struct.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/Liste.o: src/files/Liste.c include/Liste.h include/Struct.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/Malloc.o: src/files/Malloc.c include/Malloc.h include/Struct.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/Set.o: src/files/Set.c include/Set.h include/Struct.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean
clean :
ifeq ($(OS),Windows_NT)
	del /Q $(BUILD_DIR)\*.o $(BUILD_DIR)\main.exe
else
	rm -f $(BUILD_DIR)/main $(BUILD_DIR)/main.exe $(BUILD_DIR)/*.o
endif

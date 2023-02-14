CC := gcc
CPPFLAGS := -Wall -g -MMD -c
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)
DEPENDENCIES = $(OBJECTS:%.o=%.d)
PROJECT := compiler.exe

run: $(PROJECT) clean
	./$(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CPPFLAGS) -o $@ $<

.PHONY: clean
clean:
	$(shell rm -f $(OBJECTS) $(DEPENDENCIES))

-include $(OBJECTS:%.o=%.d)
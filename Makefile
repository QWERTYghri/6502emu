#
# Makefile
#
# Makefile to compile or install programs
#

include conf.mk

.PHONY: all clean
all: $(NAME)

# Compile program
$(NAME): ./src/private/*.c ./src/public/*.h ./src/main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OFLAG) -o $@ $^

# Install executable to local path
install: ./$(NAME)
	cp -f $^ $(BINPATH)

# Uninstall executable from local path
uninstall:
	-rm -fv $(BINPATH)/$(NAME)

# Clean compiled files
clean:
	-rm -fv *.out

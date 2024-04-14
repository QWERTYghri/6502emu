#
# Compilation Options
#
# Used to specify what flags are used for compilation
#


# Compile Flags
CC	 := gcc
CFLAGS	 := -std=gnu99 -Wpedantic -Wall -Wextra -pipe
CPPFLAGS := -D_POSIX_C_SOURCE=200809L

# Optimization Flags
#OFLAG	 := -Os
OFLAG	 := -O0 -g

# Other
NAME	 := "6502emu"
BINPATH	 := /usr/local/bin

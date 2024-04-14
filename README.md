6502 Emulator
=============


About
-------------
Basic original 6502 emulator that can run
at variable frequency. It performs all the functions
of the 6502 architecture. However, all data operations
are done from an array and cannot support any devices
or mappings to other inputs.

Essentially, all it does it read/write data and do operations.
It's simple because I just wanted to do make something honestly.

Making a 6502 emulator is a right of passage...

Compilation
-------------
It uses makefile as a build system, here are the following options:

```bash
# Compiles program and outputs executable
~$ make

# Installs executable to $PATH
~$ make install

# Uninstalls executable from $PATH
~$ make uninstall

# Cleans compiled files in directory
~$ make clean
```

How to Use
----------
Emulator has no assembler tool and runs by providing a file for the program
to run.

**Note**: All file data is stored at the beginning of address `$0200` unless specified

#### Execute a File
```
~$ 6502emu --open <filename>
```

#### Specify Starting Address
```
~$ 6502emu --address <$0000 - $FFFF>
```

#### Specify Clock Rate
```
~$ 6502emu --clock <integer in hertz>
```

#### Show Status Each Cycle
**Note**: Use this if needed to make a log of execution
```
~$ 6502emu --status
```

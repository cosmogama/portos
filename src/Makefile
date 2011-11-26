##################################
# AUTO GENERATED KERNEL MAKEFILE #
##################################

CC=i586-elf-gcc

# CFLAGS USING OR POSSIBLY GOING TO USE
CFLAGS_BASIC=-Werror -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -ffreestanding 
CFLAGS_EXTRA=-Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wredundant-decls \
	-Wnested-externs -Winline -Wstrict-prototypes -Wfloat-equal \
	-Wswitch-default -Wnonnull -Wbad-function-cast -Wunused -Waggregate-return
CFLAGS_SOMETIMES_USEFUL=-pedantic -Wmissing-prototypes -Wno-long-long -Wconversion -Wcast-align
CFLAGS_TRY=-Wno-multichar

# CFLAGS NOT USING
CFLAGS_NIU=-nobuiltin -Wmissing-declarations -Wdouble-promotion -Wjump-misses-init \
	-Wsign-conversion -Wlogical-op 
CFLAGS_NEVER_USE=-Wuninitialized # never use flags which involve optimizations
CFLAGS_NOT_UNDERSTOOD_BY_COMPILER_BUT_DESIRED=-Wstack-usage=2000 

# CFLAGS 
CFLAGS=$(CFLAGS_BASIC) $(CFLAGS_EXTRA)
#CFLAGS=$(CFLAGS_BASIC) $(CFLAGS_EXTRA) $(CFLAGS_SOMETIMES_USEFUL)

IDIR=-I kernel -I test -I fs

all: obj/kernel.o

clean:
	$(RM) rules.mk obj/* *.o kernel.bin pad2 floppy.img

-include rules.mk


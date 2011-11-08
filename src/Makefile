###################
# KERNEL MAKEFILE #
###################

# Makefile taken from http://wiki.osdev.org/Makefile#Project_Directories

CC=i586-elf-gcc

CFLAGS_BASIC=-Werror -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
CFLAGS_EXTRA=-Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wredundant-decls -Wnested-externs -Winline -Wstrict-prototypes
CFLAGS_SOMETIMES_USEFUL=-pedantic -Wmissing-prototypes -Wno-long-long -Wconversion 
# CFLAGS_TRY=
CFLAGS_NIU=-nobuiltin -Wmissing-declarations 
CFLAGS_NEVER_USE=-Wuninitialized
CFLAGS=$(CFLAGS_BASIC) $(CFLAGS_EXTRA)
#CFLAGS=$(CFLAGS_BASIC) $(CFLAGS_EXTRA) $(CFLAGS_SOMETIMES_USEFUL)

# This is a list of all non-source files that are part of the distribution.
AUXFILES := Makefile

PROJDIRS := kernel fs test
IDIR_CC := $(patsubst %,-I %,$(PROJDIRS))
ODIR := obj

SRCFILES_C := $(shell find $(PROJDIRS) -type f -name "*.c")
SRCFILES_S := $(shell find $(PROJDIRS) -type f -name "*.s")
SRCFILES := $(SRCFILES_C) $(SRCFILES_S)
SRCFILES_FNAME_ONLY := $(notdir $(SRCFILES))

HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.h")

OBJFILES_C := $(patsubst %.c,$(ODIR)/%.o,$(SRCFILES_FNAME_ONLY))
OBJFILES_S := $(patsubst %.s,$(ODIR)/%.o,$(SRCFILES_FNAME_ONLY))
OBJFILES := $(OBJFILES_C) $(OBJFILES_S)
#TSTFILES := $(patsubst %.c,t_%,$(SRCFILES))

#DEPFILES_C    := $(patsubst %.c,%.d,$(SRCFILES))
#DEPFILES_S    := $(patsubst %.s,%.d,$(SRCFILES))
#DEPFILES := $(DEPFILES_C) $(DEPFILES_S)
#TSTDEPFILES := $(patsubst %,%.d,$(TSTFILES))

ALLFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)

vpath %.c $(PROJDIRS)
vpath %.s $(PROJDIRS)

#-include $(DEPFILES)
#-include $(DEPFILES) $(TSTDEPFILES)

all: $(OBJFILES)

$(ODIR)/%.o : %.c
	@$(CC) $(CFLAGS) -MMD -MP $(IDIR_CC) -c $< -o $@

$(ODIR)/%.o : %.s
	@$(CC) $(CFLAGS) -MMD -MP $(IDIR_CC) -c $< -o $@

.PHONY: all clean dist check testdrivers todolist

clean:
	-@$(RM) $(wildcard $(OBJFILES)) kernel.bin *.o pad2 floppy.img
#	-@$(RM) $(wildcard $(OBJFILES) $(DEPFILES) $(TSTFILES) pdclib.a pdclib.tgz)

dist:
	@tar czf pdclib.tgz $(ALLFILES)

check: testdrivers
	-@rc=0; count=0; \
	for file in $(TSTFILES); do \
		echo " TST     $$file"; ./$$file; \
		rc=`expr $$rc + $$?`; count=`expr $$count + 1`; \
	done; \
	echo; echo "Tests executed: $$count  Tests failed: $$rc"

testdrivers: $(TSTFILES)

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO -e FIXME $$file; done; true

# Standard things

.SUFFIXES:
.SUFFIXES:	.c .o

all:		targets


# Subdirectories, in random order

dir		:= src
include		$(dir)/rules.mk
dir		:= model
include		$(dir)/rules.mk
dir		:= viewer
include		$(dir)/rules.mk
dir		:= mvc
include		$(dir)/rules.mk
dir		:= test
include		$(dir)/rules.mk
dir		:= lua
include		$(dir)/rules.mk

# General directory independent rules

%.o:		%.c
		$(COMP)

%.o:		%.cc
		$(COMP)

%:		%.o
		$(LINK)

%:		%.c
		$(COMPLINK)


# The variables TGT_*, CLEAN and CMD_INST* may be added to by the Makefile
# fragments in the various subdirectories.

.PHONY:		targets
targets:	$(TGT_BIN) $(TGT_SBIN) $(TGT_ETC) $(TGT_LIB)

# .PHONY:		x
# x:		$(TGT_LIB)
# 		rlwrap /usr/local/gostai/bin/urbi-launch --start urbi/gadget_urbi.so --port 3000 -- --interactive

.PHONY:		distsrc
distsrc:        
		$(TAR) cjvf $(PROJET)_src.tbz -h -C .. --exclude=".svn" --exclude="*~" $(TAR_SRC) $(DIR_PROJET)/Makefile $(DIR_PROJET)/rules.mk $(DIR_PROJET)/build

.PHONY:		clean
clean:
		rm -f $(CLEAN)

.PHONY:		veryclean
veryclean:	clean
		rm -rf $(VERYCLEAN) 

.PHONY:		tag
tag:
		$(ETAGS) $(TAG_FILES)

.PHONY:		doc
doc:		$(TGT_DOC)

.PHONY:		clean_doc
clean_doc:
		rm -rf $(CLEAN_DOC)

.PHONY:		install
install:	targets 
		$(INST) $(TGT_BIN) -m 755 -d $(DIR_BIN)
		$(CMD_INSTBIN)
		$(INST) $(TGT_SBIN) -m 750 -d $(DIR_SBIN)
		$(CMD_INSTSBIN)
ifeq ($(wildcard $(DIR_ETC)/*),)
		$(INST) $(TGT_ETC) -m 644 -d $(DIR_ETC)
		$(CMD_INSTETC)
else
		@echo Configuration directory $(DIR_ETC) already present -- skipping
endif
		$(INST) $(TGT_LIB) -m 750 -d $(DIR_LIB)
		$(CMD_INSTLIB)


# Prevent make from removing any build targets, including intermediate ones

.SECONDARY:	$(CLEAN)

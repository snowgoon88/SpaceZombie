# Makefile 
# Make according to Peter Miller's "Recursive Make Considered Harmful"
#                http://www.canb.auug.org.au/~millerp
# and to Emile van Bergen, http://www.xs4all.nl/~evbergen/nonrecursive-make.html
#

PLATFORM	:= $(shell uname)

VERYCLEAN	:= *~

PROJET		:= sz
DIR_PROJET	:= SpaceZombie

SCIGL_ROOT	:= ../Scigl
SZ_ROOT	:= .
ifeq ($(PLATFORM), Darwin) 
GLFW_HOME       := /Users/dutech/Work/SVN_loriakhep/glfw-2.7
EIGEN_ROOT	:= /Users/dutech/Work/SVN_loriakhep/NeuralNetwork/DSOM/eigen-eigen-65ee2328342f
else
GLFW_HOME       := /usr
EIGEN_ROOT      := /usr/include/eigen2
endif
ANTTW_HOME	:= ../Inertia/AntTweakBar

### Build flags for all targets
#
CF_ALL          = -g -Wall \
                  -I$(EIGEN_ROOT) -I$(ANTTW_HOME)/include
#CF_ALL          = -O3
LF_ALL          = 
LL_ALL          =
MK_DYN_LIB	= -fPIC -shared

### Build tools
# 
CC              = ./build/ccd-g++
INST		= ./build/install
COMP            = $(CC) $(CF_ALL) $(CF_TGT) -o $@ -c $<
LINK            = $(CC) $(LF_ALL) $(LF_TGT) -o $@ $^ $(LL_TGT) $(LL_ALL)
COMPLINK        = $(CC) $(CF_ALL) $(CF_TGT) $(LF_ALL) $(LF_TGT) -o $@ $< $(LL_TGT) $(LL_ALL)
ARCH		= ar rcs $@ $^
DYN_LIB		= $(CC) $(MK_DYN_LIB) $(LF_ALL) $(LF_TGT) -o $@ $^ $(LL_TGT) $(LL_ALL)
GENERATE_DOC	= doxygen $^
TAR		= tar
ETAGS		= etags
### Standard parts
#
include rules.mk


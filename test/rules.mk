# Standard things
# saves the variable $(d) that holds the current directory on the stack,
# and sets it to the current directory given in $(dir), 
# which was passed as a parameter by the parent rules.mk

sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

# Subdirectories, if any, in random order

#dir	:= $(d)/test
#include		$(dir)/Rules.mk

# Next, we create an immediately evaluated variable $(OBJS_common) 
# that holds all the objects in that directory.
# We also create $(DEPS_common), which lists any automatic dependency files 
# generated later on.
# To the global variable $(CLEAN), we add the files that the rules present here 
# may create, i.e. the ones we want deleted by a make clean command.)

# Local variables
#EIGEN_ROOT	:= ../eigen-eigen-65ee2328342f
#EIGEN_FLAGS	:= -I$(EIGEN_ROOT)

#SRC_FLAGS	:= -Isrc

# Local rules and target
CORE_SRC_$(d)	:= $(DIR_PROJET)/$(d)/test_model.cc \
                   $(DIR_PROJET)/$(d)/test_scigl.cc \
                   $(DIR_PROJET)/$(d)/test_physic_scigl.cc \
                   $(DIR_PROJET)/$(d)/test_arrow_scigl.cc \
                   $(DIR_PROJET)/$(d)/test_triangles_scigl.cc \
                   $(DIR_PROJET)/$(d)/test_timer.cc \
                   $(DIR_PROJET)/$(d)/test_format.cc \
                   $(DIR_PROJET)/$(d)/test_vect.cc \
                   $(DIR_PROJET)/$(d)/test_torsor.cc \
                   $(DIR_PROJET)/$(d)/test_torsor_scigl.cc \
                   $(d)/test/test_type.cc \
#                   $(DIR_PROJET)/$(d)/test_cell.cc \

CORE_OBJS_$(d)	:= 

CORE_DEPS_$(d)	:= $(CORE_OBJS_$(d):%=%.d)

TGTS_$(d)	:= $(d)/test_model \
                   $(d)/test_scigl \
                   $(d)/test_physic_scigl \
                   $(d)/test_arrow_scigl \
                   $(d)/test_triangles_scigl \
                   $(d)/test_timer \
                   $(d)/test_format \
                   $(d)/test_vect \
                   $(d)/test_torsor \
                   $(d)/test_torsor_scigl \
                   $(d)/test_type \
#                   $(d)/test_cell \


DEPS_$(d)	:= $(TGTS_$(d):%=%.d)

TGT_BIN		:= $(TGT_BIN) verbose_$(d) $(TGTS_$(d))

TAR_SRC		:= $(TAR_SRC) $(CORE_SRC_$(d)) $(DIR_PROJET)/$(d)/rules.mk

CLEAN		:= $(CLEAN) $(DEPS_$(d))
VERYCLEAN	:= $(VERYCLEAN) $(TGTS_$(d)) $(d)/*~ $(d)/*.dSYM 

TAG_FILES	:= $(TAG_FILES)

# target local
# TGT_LIB		:= $(TGT_LIB) verbose_$(d) $(TGTS_$(d))

# Now we list the dependency relations relevant to the files in this subdirectory.
# Most importantly, while generating the objects listed here, we want to set 
# the target-specific compiler flags $(CF_TGT) to include a flag that adds 
# this directory to the include path, so that local headers may be included 
# using #include <localfile.h>, which is, as said, more portable 
# than local includes when the source directory is not the current directory.)


# Local CFLAGS
# Force remake if rules are changed
#$(CORE_OBJS_$(d)):	$(d)/rules.mk

# $(CORE_OBJS_$(d)): 	CF_TGT := -I$(d) $(EIGEN_FLAGS) -Wno-deprecated

# Local libs
# Force remake if rules are changed
#$(TGTS_$(d)): $(d)/rules.mk
ifeq ($(PLATFORM), Darwin) 
$(TGTS_$(d)):	CF_TGT := -I$(d) -Isrc -I/opt/local/include \
                          -I$(SCIGL_ROOT)/scigl -I$(GLFW_HOME)/include \
                          -I$(ANTTW_HOME)/include \
                          -I$(EIGEN_ROOT) \
                          -I$(SZ_ROOT)/model -I$(SZ_ROOT)/viewer -I$(SZ_ROOT)/mvc\
                          -I$(SZ_ROOT)/shape3D \

$(TGTS_$(d)):	LF_TGT := $(SRC_FLAGS) \
                          -framework OpenGL -framework Cocoa \
                          -L$(ANTTW_HOME)/lib \
                          -L/opt/local/lib \
                          -lGLEW 

# $(TGTS_$(d)):	LL_TGT := $(GDK_LIBS) $(GTK_LIBS) \
# 			  $(UTILS_LIBS) \
# 	                  $(VID_LIBS) $(GST_LIBS) $(OPENCV_LIBS) \
# 	                  -lgthread-2.0 -lboost_thread

$(TGTS_$(d)):	LL_TGT := $(SZ_ROOT)/model/libmodel.a \
                          $(SZ_ROOT)/viewer/libviewer.a \
                          $(SZ_ROOT)/shape3D/libshape.a \
                          $(SZ_ROOT)/mvc/libmvc.a \
                          $(SZ_ROOT)/src/libsrc.a \
                          $(SCIGL_ROOT)/scigl/libscigl.a \
                          $(ANTTW_HOME)/lib/libAntTweakBar.dylib \
                          $(GLFW_HOME)/lib/cocoa/libglfw.a \
                          -lboost_thread-mt
else
$(TGTS_$(d)):	CF_TGT := -I$(d) -Isrc \
                          -I$(SCIGL_ROOT)/scigl -I$(GLFW_HOME)/include \
                          -I$(SZ_ROOT)/model -I$(SZ_ROOT)/viewer -I$(SZ_ROOT)/mvc\
                          -I$(SZ_ROOT)/shape3D \

$(TGTS_$(d)):	LF_TGT := $(SRC_FLAGS) \

# $(TGTS_$(d)):	LL_TGT := $(GDK_LIBS) $(GTK_LIBS) \
# 			  $(UTILS_LIBS) \
# 	                  $(VID_LIBS) $(GST_LIBS) $(OPENCV_LIBS) \
# 	                  -lgthread-2.0 -lboost_thread

# il faut inclures les .a dans le bon ordre !!!!
$(TGTS_$(d)):	LL_TGT := \
                          $(SZ_ROOT)/viewer/libviewer.a \
                          $(SZ_ROOT)/model/libmodel.a \
                          $(SZ_ROOT)/mvc/libmvc.a \
                          $(SZ_ROOT)/shape3D/libshape.a \
                          $(SZ_ROOT)/src/libsrc.a \
                          $(SCIGL_ROOT)/scigl/libscigl.a \
                          $(ANTTW_HOME)/lib/libAntTweakBar.so \
                          -lglfw \
                          -lGL -lGLU -lGLEW \
                          -lboost_thread
#                          $(SZ_ROOT)/model/libmodel.a \
#                          $(SZ_ROOT)/viewer/libviewer.a \
#                          $(SZ_ROOT)/mvc/libmvc.a \

endif

#$(CORE_OBJS_$(d)):	CF_TGT := -I. -I$(d) $(shell pkg-config --cflags gtkmm-2.4)
#$(OBJS_$(d)):	LF_TGT := -lgsl -lgslcblas -lm 
#$(OBJS_$(d)):	LL_TGT := $(S_LL_INET) cpp/core.a dana-cpp/dana.a

$(d)/test_model: 	$(d)/test_model.cc src/libsrc.a model/libmodel.a viewer/libviewer.a mvc/libmvc.a shape3D/libshape.a
			@echo "===== Compiling and Linking $@"
			$(COMPLINK)

$(d)/test_vect: 	$(d)/test_vect.cc 
			@echo "===== Compiling and Linking $@"
			$(COMPLINK)

# $(d)/test_cell: 	$(d)/test_cell.cc src/libsrc.a model/libmodel.a
# 			@echo "===== Compiling and Linking $@"
# 			$(COMPLINK)


$(d)/test_torsor: 	$(d)/test_torsor.cc src/libsrc.a
			@echo "===== Compiling and Linking $@"
			$(COMPLINK)

$(d)/test_torsor_scigl:	$(d)/test_torsor_scigl.cc src/libsrc.a shape3D/libshape.a $(SCIGL_ROOT)/scigl/libscigl.a model/libmodel.a viewer/libviewer.a mvc/libmvc.a
			@echo "===== Compiling and Linking $@"
			$(COMPLINK)


$(d)/test_scigl:	$(d)/test_scigl.cc src/libsrc.a model/libmodel.a viewer/libviewer.a mvc/libmvc.a shape3D/libshape.a $(SCIGL_ROOT)/scigl/libscigl.a
			@echo "===== Compiling and Linking $@"
			$(COMPLINK)

$(d)/test_physic_scigl:	$(d)/test_physic_scigl.cc src/libsrc.a model/libmodel.a viewer/libviewer.a mvc/libmvc.a shape3D/libshape.a $(SCIGL_ROOT)/scigl/libscigl.a
			@echo "===== Compiling and Linking $@"
			$(COMPLINK)

$(d)/test_arrow_scigl:	$(d)/test_arrow_scigl.cc src/libsrc.a shape3D/libshape.a $(SCIGL_ROOT)/scigl/libscigl.a 
#model/libmodel.a viewer/libviewer.a mvc/libmvc.a  
			@echo "===== Compiling and Linking $@"
			$(COMPLINK)

$(d)/test_triangles_scigl:	$(d)/test_triangles_scigl.cc src/libsrc.a model/libmodel.a viewer/libviewer.a shape3D/libshape.a mvc/libmvc.a $(SCIGL_ROOT)/scigl/libscigl.a
			@echo "===== Compiling and Linking $@"
			$(COMPLINK)


$(d)/test_timer:	$(d)/test_timer.cc src/libsrc.a
			@echo "===== Compiling and Linking $@"
			$(COMPLINK)

$(d)/test_format:	$(d)/test_format.cc
			@echo "===== Compiling and Linking $@"
			$(COMPLINK)

$(d)/test_type:		$(d)/test_type.cc
			@echo "===== Compiling and Linking $@"
			$(COMPLINK)



.PHONY : verbose_$(d)
verbose_$(d): $(TGTS_$(d))
	@echo "**** Generating $^"

# As a last step, we restore the value of the current directory variable $(d) 
# by taking it from the current location on the stack, and we "decrement" 
# the stack pointer by stripping away the .x suffix 
# we added at the top of this file.

# Standard things

-include	$(CORE_DEPS_$(d))

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))


#---------------------------DIRECTORY CONFIGURATION-----------------------------
SRC_DIR=src
MAIN_SRC_DIR=src/main
OBJ_DIR=obj
MAIN_OBJ_DIR=obj/main
BIN_DIR=bin
#----------------------COMPILER OPTIONS AND CONFIGURATION ----------------------
COMPILER=g++
LINKER=g++
# Compiler flags
CFLAGS=-c -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code \
    -Wmissing-declarations -Wmissing-include-dirs -Wmain -Wall \
    -Wextra -std=c++11 -pg -g -Wcast-qual -Wdisabled-optimization -Wformat=2 \
    -Wlogical-op -Wsign-conversion -Wno-sign-conversion -Wno-unused
# Compiler ouptut flag
COUTFLAG=-o
# Utilities
RM=rm
RM_FLAGS=-f
ECHO=echo
# Linker flags
LFLAGS=
# Linker output flag
LOUTFLAG=-o
#------------------------------------FILES--------------------------------------
SRC_EXT=cpp
HEAD_EXT=h
OBJ_EXT=o
BIN_EXT=exe

SRC_FILES=$(wildcard $(SRC_DIR)/*.$(SRC_EXT))
MAIN_SRC_FILES=$(wildcard $(MAIN_SRC_DIR)/*.$(SRC_EXT))

OBJ_FILES=$(SRC_FILES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.$(OBJ_EXT))
MAIN_OBJ_FILES=$(MAIN_SRC_FILES:$(MAIN_SRC_DIR)/%.$(SRC_EXT)=$(MAIN_OBJ_DIR)/%.$(OBJ_EXT))

BIN_FILES=$(MAIN_SRC_FILES:$(MAIN_SRC_DIR)/%.$(SRC_EXT)=$(BIN_DIR)/%.$(BIN_EXT))
#---------------------------------LIBRARIES-------------------------------------
SYS_LIBS=
SYS_LIBPATHS=/lib/x86_64-linux-gnu

LIB_FLAG=-l
LIBPATH_FLAG=-I

INCLUDE=$(SYS_LIBPATHS:%=$(LIBPATH_FLAG)%)
LIBS=$(SYS_LIBS:%=$(LIB_FLAG)%)
#------------------------------------RULES--------------------------------------
all : init $(BIN_FILES)

$(BIN_DIR)/%.$(BIN_EXT) : $(OBJ_FILES) $(MAIN_OBJ_DIR)/%.$(OBJ_EXT)
	@$(ECHO) $(LINKER) $@
	@$(LINKER) $(LOUTFLAG) $@ $^ $(INCLUDE) $(LIBS) $(LFLAGS)

$(OBJ_DIR)/%.$(OBJ_EXT) : $(SRC_DIR)/%.$(SRC_EXT) $(SRC_DIR)/%.$(HEAD_EXT)
	@$(ECHO) $(COMPILER) $(COUTFLAG) $@ $<
	@$(COMPILER) $(COUTFLAG) $@ $(CFLAGS) $(DEFINE) $<

$(MAIN_OBJ_DIR)/%.$(OBJ_EXT) : $(MAIN_SRC_DIR)/%.$(SRC_EXT)
	@$(ECHO) $(COMPILER) $@ $<
	@$(COMPILER) $(COUTFLAG) $@ $(CFLAGS) $(DEFINE) -I$(SRC_DIR) $<
#-----------------------------------CLEAN RULES---------------------------------
.PHONY : clean cleanall init
init :
	@test -d $(SRC_DIR) || mkdir $(SRC_DIR)
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	@test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	@test -d $(MAIN_SRC_DIR) || mkdir $(MAIN_SRC_DIR)
	@test -d $(MAIN_OBJ_DIR) || mkdir $(MAIN_OBJ_DIR)

clean :
	$(RM) $(RM_FLAGS) $(OBJ_FILES)
	$(RM) $(RM_FLAGS) $(MAIN_OBJ_FILES)

cleanall : clean
	$(RM) $(RM_FLAGS) $(BIN_FILES)

config :
	@$(ECHO) --SOURCE FILES : $(SRC_FILES)
	@$(ECHO) --COMPILED FILES : $(OBJ_FILES)
	@$(ECHO) --MAIN SOURCE FILES : $(MAIN_SRC_FILES)
	@$(ECHO) --COMPILED MAIN FILES : $(MAIN_OBJ_FILES)
	@$(ECHO) --EXECUTABLES : $(BIN_FILES)

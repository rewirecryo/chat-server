CXX := g++
MAKE := make
LIBS:=
CXXFLAGS:=
BINARY := bin/chat-server

DIR_DEP := deps
DIR_SRC := src
DIR_OBJ := obj

SUBDIRS := Instructions Responses Executors

DIRS_BASE := $(DIR_SRC) $(DIR_OBJ) $(DIR_DEP)
DIRS_ALL := $(DIRS_BASE) $(foreach base_dir, $(DIRS_BASE), $(foreach sub_dir, $(SUBDIRS), $(base_dir)/$(sub_dir)))

FILES_SRC := $(wildcard $(DIR_SRC)/*.cpp) $(wildcard $(patsubst %, $(DIR_SRC)/%/*.cpp, $(SUBDIRS)))
FILES_DEP := $(patsubst $(DIR_SRC)/%.cpp, $(DIR_DEP)/%.d, $(FILES_SRC))
FILES_OBJ := $(patsubst $(DIR_SRC)/%.cpp, $(DIR_OBJ)/%.o, $(FILES_SRC))


$(BINARY) : $(FILES_OBJ)
	$(CXX) -o $(BINARY) $(CXXFLAGS) $(LIBS) $^

$(DIR_SRC)/%.cpp : | $(dir $(DIR_SRC)/%.cpp)

include $(wildcard $(FILES_DEP))

clean :
	rm $(FILES_OBJ)

$(patsubst %,%/,$(DIRS_ALL)) :
	mkdir $@

.SECONDEXPANSION:

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.cpp $(DIR_DEP)/%.d | $$(dir $$@)
	$(CXX) -o $@ $(CXXFLAGS) $(LIBS) -c $<

$(DIR_DEP)/%.d : $(DIR_SRC)/%.cpp | $$(dir $$@)
	$(CXX) -M -MF $@ -MT $(DIR_OBJ)/$*.o -MP $<

.PHONY: clean

.PRECIOUS: $(FILES_DEP)

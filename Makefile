CXX := g++
MAKE := make
LIBS:=
CXXFLAGS:=
BINARY := bin/chat-server
DIR_DEPS:=deps


DIR_SRC := src
DIR_OBJ := obj

FILES_SRC:=$(wildcard $(DIR_SRC)/*.cpp)
FILES_DEP=$(patsubst $(DIR_SRC)/%.cpp, $(DIR_DEPS)/%.d, $(FILES_SRC))
FILES_OBJ=$(patsubst $(DIR_SRC)/%.cpp, $(DIR_OBJ)/%.o, $(FILES_SRC))

$(BINARY) : $(FILES_OBJ)
	$(CXX) -o $(BINARY) $(CXXFLAGS) $(LIBS) $^

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.cpp $(DIR_DEPS)/%.d
	$(CXX) -o $@ $(CXXFLAGS) $(LIBS) -c $<

$(DIR_DEPS)/%.d : $(DIR_SRC)/%.cpp
	$(CXX) -M -MF $@ -MT $(DIR_OBJ)/$*.o -MP $<

include $(wildcard $(DIR_DEPS)/*)

clean :
	rm $(FILES_OBJ)

.PHONY: clean

.PRECIOUS: $(FILES_DEP)

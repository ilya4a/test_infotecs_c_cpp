CXX := g++

CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic
CPPFLAGS := -MMD -MP \
            -Ilib/include \
            -Iapp/include

LDFLAGS := -pthread

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
LIB_DIR := $(BUILD_DIR)/lib

JOURNAL_LIB := $(LIB_DIR)/libjournal.so
APP := $(BIN_DIR)/app
TESTS := $(BIN_DIR)/tests

LIB_SOURCES := \
    lib/src/FileJournal.cpp \
    lib/src/Message.cpp

APP_SOURCES := \
    app/src/main.cpp \
    app/src/App.cpp \
    app/src/Command.cpp

TEST_SOURCES := \
    tests/main.cpp \
    tests/TestThreadSafeQueue.cpp \
    tests/TestFileJournal.cpp \
    tests/TestApp.cpp \
    app/src/App.cpp \
    app/src/Command.cpp

LIB_OBJECTS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(LIB_SOURCES))
APP_OBJECTS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(APP_SOURCES))
TEST_OBJECTS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TEST_SOURCES))

ALL_OBJECTS := $(LIB_OBJECTS) $(APP_OBJECTS) $(TEST_OBJECTS)
DEP_FILES := $(ALL_OBJECTS:.o=.d)


.PHONY: all library app tests test clean

all: library app tests



library: $(JOURNAL_LIB)

$(JOURNAL_LIB): $(LIB_OBJECTS)
	@mkdir -p $(LIB_DIR)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)



app: $(APP)

$(APP): $(APP_OBJECTS) $(JOURNAL_LIB)
	@mkdir -p $(BIN_DIR)
	$(CXX) -o $@ $(APP_OBJECTS) \
		-L$(LIB_DIR) -ljournal \
		-Wl,-rpath,'$$ORIGIN/../lib' \
		$(LDFLAGS)



tests: $(TESTS)

$(TESTS): $(TEST_OBJECTS) $(JOURNAL_LIB)
	@mkdir -p $(BIN_DIR)
	$(CXX) -o $@ $(TEST_OBJECTS) \
		-L$(LIB_DIR) -ljournal \
		-Wl,-rpath,'$$ORIGIN/../lib' \
		$(LDFLAGS)


test: tests
	@echo "Running tests..."
	@$(TESTS)
	@echo "All tests passed."


$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -fPIC -c $< -o $@


clean:
	rm -rf $(BUILD_DIR)


-include $(DEP_FILES)
CXX ?= c++
CPPFLAGS ?=
CXXFLAGS ?= -O2 -g -Wall -Wextra -Wpedantic
LDFLAGS ?=
LDLIBS ?=

TARGET := TinVM
BUILD_DIR := build
VM_OBJECT := $(BUILD_DIR)/src/vm/vm.o
APP_OBJECT := $(BUILD_DIR)/src/main.o
OBJECTS := $(VM_OBJECT) $(APP_OBJECT)

.PHONY: all run clean
all: $(TARGET)

$(TARGET): $(APP_OBJECT) $(VM_OBJECT)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -Isrc $(CXXFLAGS) -std=c++17 -MMD -MP -c $< -o $@

run: $(TARGET)
	"$(abspath $(TARGET))"

clean:
	$(RM) -r $(BUILD_DIR) $(TARGET)

-include $(OBJECTS:.o=.d)

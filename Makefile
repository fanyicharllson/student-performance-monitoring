# ============================================================
#  Makefile — AI-Based Student Performance Monitoring System
#  Supports: Linux, macOS, Windows (with MinGW)
# ============================================================

# Compiler and flags
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Output binary name
TARGET   = student_monitor

# Source and object directories
SRCDIR   = src
OBJDIR   = obj

# Automatically find all .cpp files in src/
SOURCES  = $(wildcard $(SRCDIR)/*.cpp)

# Convert each .cpp path to a .o path in obj/
OBJECTS  = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# ---- DEFAULT TARGET: build the executable ----
all: $(OBJDIR) $(TARGET)

# Create the obj directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Link all object files into the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "✅ Build successful! Run with: ./$(TARGET)"

# Compile each .cpp file into a .o object file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ---- CLEAN: remove build artifacts ----
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "🧹 Cleaned build files."

# ---- RUN: build then run ----
run: all
	./$(TARGET)

# Prevent make from confusing these with file names
.PHONY: all clean run

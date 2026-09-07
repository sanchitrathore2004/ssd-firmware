CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = build/simul_ssd

SOURCES = main.cpp src/flash_page.cpp src/nand_flash.cpp ftl/src/ftl.cpp request_manager.cpp garbage_collector.cpp wear_leveling.cpp metric.cpp

INCLUDES = -Iinclude -Iftl/include -I.

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(SOURCES) $(INCLUDES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build
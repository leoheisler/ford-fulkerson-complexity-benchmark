# Diretórios
SRC_DIR    := own_code
BUILD_DIR  := build
INC_DIR    := $(SRC_DIR)/include

# Procura todos os arquivos .cpp na pasta own_code
SOURCES    := $(wildcard $(SRC_DIR)/*.cpp)
# Define os arquivos objeto na pasta build
OBJECTS    := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Nome do executável final
TARGET     := $(BUILD_DIR)/ford_fulkerson

# Compilador e flags
CXX        := g++
CXXFLAGS   := -Wall -Wextra -std=c++17 -I$(INC_DIR)

# Regra padrão para compilar e gerar o executável
all: $(TARGET)

# Regra para gerar o executável a partir dos objetos, garantindo que a pasta build exista
$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Cria a pasta build caso não exista
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regra para compilar cada arquivo .cpp em seu respectivo objeto (.o) dentro da pasta build
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpeza dos arquivos gerados
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

# Declara targets que não correspondem a arquivos reais
.PHONY: all clean

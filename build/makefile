CXX = clang++
CXX_FLAGS = -std=c++20 -I ../include/

TARGET = cir_sim
OBJS = main.o vector.o matrix.o circuit.o plotter.o fourier.o logic_array.o gates.o

$(TARGET): $(OBJS)
	$(CXX) $(CXX_FLAGS) -o $(TARGET) $(OBJS)

%.o: ../%.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@
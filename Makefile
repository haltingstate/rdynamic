run: main.cpp polygon.hpp triangle.so
	$(CXX) $(CXXFLAGS) -o run main.cpp -ldl

triangle.so: triangle.cpp polygon.hpp
	$(CXX) $(CXXFLAGS) -shared -o triangle.so triangle.cpp

clean:
	rm -f run triangle.so

.PHONY: clean

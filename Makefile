run: main.cpp polygon.hpp triangle.so
	$(CXX) $(CXXFLAGS) -o run main.cpp -ldl -fpic -fvisibility=hidden

#-fPIC -rdynamic -fvisibility=hidden
#fpic

triangle.so: triangle.cpp
	$(CXX) $(CXXFLAGS) -shared -o triangle.so triangle.cpp

#-fPIC -rdynamic 
#-fvisibility=hidden

clean:
	rm -f run triangle.so

.PHONY: clean

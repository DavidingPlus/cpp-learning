target = a.out
allcpp =$(wildcard *.cpp)
src =$(patsubst %.cpp,%.o,$(allcpp))

$(target): $(src)
	$(CXX) $(src) -o $(target)

%.o : %.cpp
	$(CXX) -c $< -o $@

.PHONY:clean
clean : $(src) $(target)
	rm $(src) $(target)

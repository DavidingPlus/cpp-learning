source = WorkerManager.cpp Boss.cpp Employee.cpp Manager.cpp EmployeeManagementSystem.cpp
target = a.out

CXX = g++
CXXFLAG = -Wall -g -std=c++23
EXTRAFLAG =

ifdef windir
ASAN =
RM = del
EXTRAFLAG = -DWIN
target = a.out
else
# 这玩意是内存消毒器，不建议使用
# ASAN = -fsanitize=address
RM = rm
endif

all:
	$(CXX) $(source) $(CXXFLAG) $(ASAN) $(EXTRAFLAG) -o $(target) $(LIB)

clean:
	$(RM) $(target)

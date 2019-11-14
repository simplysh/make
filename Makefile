program = sample

# shell
rm = $(if $(filter $(OS),Windows_NT),del /Q,rm -fv)
cp = $(if $(filter $(OS),Windows_NT),copy,cp)

# compiler
cxx = g++
cxxflags = -std=c++14 -pedantic-errors
out = $(if $(filter $(OS),Windows_NT),.\$(program).exe,./$(program))
dest = $(if $(filter $(OS),Windows_NT),$(shell echo %SYSTEMROOT%),/usr/local/bin)
src = $(wildcard ./*.cpp)
obj = $(src:.cpp=.o)

# windows-only
ifeq ($(filter $(OS),Windows_NT), Windows_NT)
	winflags = -static-libgcc -static-libstdc++
endif


all: $(out)

$(out):	$(obj)
	$(cxx) $^ -o $@

main.o: main.cpp
	$(cxx) -c $(cxxflags) $(winflags) main.cpp -o main.o

./%.o: ./%.cpp ./%.h
	$(cxx) -c $(cxxflags) $(winflags) $< -o $@

clean:
	$(rm) *.o $(out)

install:
	@echo installing to $(dest)
	$(cp) $(out) $(dest)

# target: dependencies
# 	action
program = sample

# config
sdl_prefix = C:\libsdl

# shell
rm = $(if $(filter $(OS),Windows_NT),del /Q,rm -f)
cp = $(if $(filter $(OS),Windows_NT),copy,cp)
cat = $(if $(filter $(OS),Windows_NT),type,cat)

# sdl
ifdef sdl_prefix
	sdlflags = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
endif

# windows-only
ifeq ($(filter $(OS),Windows_NT), Windows_NT)
	winflags = -static-libgcc -static-libstdc++
endif

# compiler
cxx = g++
cxxflags = -std=c++14 -pedantic-errors
out = $(if $(filter $(OS),Windows_NT),.\$(program).exe,./$(program))
dest = $(if $(filter $(OS),Windows_NT),$(shell echo %SYSTEMROOT%),/usr/local/bin)
src = $(wildcard ./*.cpp)
obj = $(src:.cpp=.o)
flags = $(cxxflags) $(winflags) $(sdlflags) -DVERSION="\"$(shell $(cat) VERSION)\""

all: $(out)

$(out):	$(obj)
	$(cxx) $(flags) $^ -o $@

main.o: main.cpp
	$(cxx) -c $(flags) main.cpp -o main.o

./%.o: ./%.cpp ./%.h
	$(cxx) -c $(flags) $< -o $@

clean:
	$(rm) *.o $(out)

install:
	@echo installing to $(dest)
	$(cp) $(out) $(dest)

# target: dependencies
# 	action

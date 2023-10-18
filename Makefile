
# link target.
linkTarget = a

# libs
LIBS = -lSDL2

# Define flags.
# CFLAGS = -std=c++17 -pg
CFLAGS = -std=c++17 -Ofast


#obj needed. each file compiled to obj, then linker combines all
objects = main.o \
		  CApp.o \
		  $(patsubst %.cpp,%.o,$(wildcard ./RayTrace/*.cpp))

# Define the rebuildables.
rebuildables = $(objects) $(linkTarget)

# Rule to automate build. First one run last
$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)

# Rule to create the .o files.
%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

.PHONEY:
clean:
	rm $(rebuildables)

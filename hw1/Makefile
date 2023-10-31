.SUFFIXES : .c .o # macro. -c: compile. -o: object file
	
OBJECTS = main.o read.o write.o # store the list of object files 
SRCS = main.c read.c write.c # store the list of source file 
CC = gcc # store the compiler command : gcc
CFLAGS = -g -c # compiler flag : includes debugging information and compiles but does not link

TARGET = hw1 # store the name of target excutable

# rule specifies how to build the target executable
$(TARGET) : $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)
 
# remove the object files and target executable
clean : 
	rm -f $(OBJECTS) $(TARGET)

# io.h + .c -(build)-> .o
main.o : io.h main.c 
read.o : io.h read.c 
write.o: io.h write.c 


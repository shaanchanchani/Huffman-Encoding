CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFLAGS = -DTEST_BUILDTREE -DTEST_PRINTPATH -DTEST
GCC = gcc $(CFLAGS) $(TESTFLAGS)
EXEC = hw14
OBJS =  hw14.o tree.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) huffman.h
	$(GCC) $(OBJS) -o $(EXEC) 
	

test: $(EXEC)
	./$(EXEC) input sorted huffman header 
 
memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) input sorted huffman header 

%.o : %.c
	$(GCC) -c $< 


clean:
	rm -f $(EXEC)
	rm -f *.o
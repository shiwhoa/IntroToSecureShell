C = gcc
all: myfind_parse
OBJ1 = myfind_parse

$(OBJ1):$(OBJ1).o
	$(CC) -o $@ $^
%.o:%.c
	$(CC) -c -o $@ $^
clean:
	rm -f $(OBJ1)*.o


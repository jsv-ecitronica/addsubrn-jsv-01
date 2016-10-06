# build the executable addsubrn.out for addsubrn.c
#all: addsubrn.c 
all: addsubrn.c addsubrn-func.c
	gcc -g -Wall -o addsubrn.out addsubrn.c addsubrn-func.c

clean: 
	$(RM) addsubrn.out


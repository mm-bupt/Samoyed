objects = main.o event.o message.o 

main : $(objects)
	g++ -g -o main $(objects)

$(objects) : mm_basetype.h

.PHONY : clean
clean :
	-rm main $(objects)

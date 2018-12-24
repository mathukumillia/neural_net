CC=gcc
CFLAGS= -Wall -Werror -g
DEPS=neuron.h activation.h layer.h

neural_net: run.o activation.o layer.o neuron.o
	$(CC) -o $@ $^ -lm

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

clean: 
	rm -f *.o neural_net

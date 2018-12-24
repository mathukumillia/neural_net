CC=gcc
CFLAGS= -Wall -Werror -g
DEPS=neuron.h activation.h

neural_net: run.o neuron.o activation.o
	$(CC) -o $@ $^ -lm

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

clean: 
	rm -f *.o neural_net

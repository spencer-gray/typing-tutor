all: typing-tutor

typing-tutor: typing-tutor.cpp
	g++ typing-tutor.cpp -o typing-tutor -lncurses

clean:
	rm typing-tutor

run:
	./typing-tutor
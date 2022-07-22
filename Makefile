BJ:	main.o player.o card.o  game.o
	@echo "#Building BLACK JACK..."
	@g++ -o BJ main.o card.o player.o game.o

main.o:	main.cc
	@echo "#Compiling main.cc"
	@g++ -c main.cc

card.o:	card.cc
	@echo "#Compiling card.cc"
	@g++ -c card.cc

player.o:	player.cc	
	@echo "#Compiling player.cc"
	@g++ -c player.cc

game.o:	game.cc
	@echo "#Compiling game.cc"
	@g++ -c game.cc

clean:
	@echo "Cleaning..."
	@rm -f *.o BJ
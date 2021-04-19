output:
	g++ -pipe --std=c++17 -g -o PuzzlePlatformer/PuzzlePlatformer -IPuzzlePlatformer/include PuzzlePlatformer/src/*.cpp -ldl -lSDL2
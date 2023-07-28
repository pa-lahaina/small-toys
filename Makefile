CC := clang
CXX := clang++
FLAGS := --std=c++17

fcb:
	$(CXX) findCommonBlobs.cpp cmdlineParser.cpp -o fcb $(FLAGS)
#include <iostream>
#include <fstream>
#include "simulation.h"


int main() {
	
		// Get the text to compress from text file
		std::string line;
		std::string text;
		std::string textForDisplay;
		std::fstream file;
		file.open("input.txt", std::ios::in);
		assert(file);
		
		while(std::getline(file, line)) {
				text += line;
				textForDisplay += line;
				textForDisplay += "\n";
		}
		file.close();

		// std::cout << "\n---------- Initial Text -----------" << std::endl;
		// std::cout << text << std::endl;
		
		/*// Find character and corresponding frequencies
		std::vector<std::pair<char, int>> characterFrequencies =  findCharFrequency(text);

		// Create a min heap
		std::priority_queue<Node*, std::vector<Node*>, compare> queue = buildTree(characterFrequencies, text);	
		Node* root = queue.top();
	
		// print out the binary codes
		std::cout << "\n---------- Binary Codes -----------" << std::endl;
		findBinaryCode(root, "");

		// Compress
		std::string compressedText = compress(text);

		std::cout << "\n---------- Compressed Text ----------" << std::endl;
		std::cout << compressedText << std::endl;

		// Decompress
		std::cout << "\n---------- Decompressed Text ----------" << std::endl;
		std::string decompressedText = decompress(root, compressedText);
		std::cout << decompressedText << std::endl;*/

		simulation sim = simulation(text, textForDisplay);

		while(sim.isOpen()) {
				sim.run();
		}
}

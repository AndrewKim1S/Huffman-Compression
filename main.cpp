#include <iostream>
#include <fstream>
#include "simulation.h"


/*const std::string characters = "1234567890abcdefghijklmnopqrstuvwxyz"\
"ABCDEFGHIJKLMNOPQRSTUVWXYZ =+-_,.<>[]{}!@#$%^&*()~?";

std::map<char, std::string> codes;

// For Priority Queue
class compare {
		public:
				bool operator()(Node *left, Node *right){
						if(left->frequency > right->frequency) {
								return true;
						}
						return false;
				}
};

std::vector<std::pair<char, int>> findCharFrequency(std::string& text) {
		std::vector<std::pair<char, int>> charFrequency;

		for(size_t i = 0; i < characters.length(); i++) {
				int count = 0;
				for(size_t k = 0; k < text.length(); k++) {
						if(characters[i] == text[k]) {
								count ++;
						}
				}
				if(count > 0) {
						charFrequency.emplace_back(std::pair(characters[i], count));
				}
		}

		
		for(std::pair<char, int> n : charFrequency){
				std::cout << n.first << ": " << n.second << std::endl;
		}

		return charFrequency;
} 

std::priority_queue<Node*, std::vector<Node*>, compare> 
buildTree(std::vector<std::pair<char, int>>& characterFrequencies, std::string& text) {
		std::priority_queue<Node*, std::vector<Node*>, compare> queue;

		for(auto s : characterFrequencies) {
				queue.push(new Node(s.first, s.second));
		}
		
		Node *left;
		Node *right;
		Node *internal;
		while(queue.size() > 1) {
				left = queue.top();
				queue.pop();

				right = queue.top();
				queue.pop();

				internal = new Node('/', left->frequency + right->frequency);
				internal->left = left;
				internal->right = right;

				queue.push(internal);
		}

		return queue;
}

std::string compress(std::string& text) {
		std::string compressedText = "";

		for(size_t i = 0; i < text.length(); i++) {
				compressedText += codes[text[i]];
		}
		return compressedText;
}

std::string decompress(Node* root, std::string& compressedText) {
		std::string decompressedText = "";
		Node* traverse = root;
		for(size_t i = 0; i < compressedText.size(); i ++) {
				if(compressedText[i] == '0') {
						traverse = traverse->left;
				} else {
						traverse = traverse->right;
				}
				if(traverse->right == NULL && traverse->left == NULL) {
						decompressedText += traverse->character;
						traverse = root;
				}
		}
		return decompressedText;
}

void findBinaryCode(Node* root, std::string code) {
		if(!root) {
				return;
		}
		if(root->character != '/') {
				std::cout << root->character << ": " << code << std::endl;
				codes.insert(std::pair<char,std::string>(root->character, code));
		}
		findBinaryCode(root->left, code + "0");
		findBinaryCode(root->right, code + "1");
}*/

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

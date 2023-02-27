#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <cassert>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Node.hpp"


class compare {
		public:
				bool operator()(Node *left, Node *right){
						if(left->frequency > right->frequency) {
								return true;
						}
						return false;
				}
};


class simulation {

		enum State {
				START,
				CHARFREQUENCIES,
				BUILDTREE,
				BINARYCODES,
				COMPRESS,
				DECOMPRESS
		};

		public:
				simulation();
				simulation(std::string text, std::string textForDisplay);
				~simulation();

				void pollEvents();
				void run();
				void next();
				void render();
				bool isOpen();

				std::vector<std::pair<char, int>> findCharFrequency(std::string& text);
				
				std::priority_queue<Node*, std::vector<Node*>, compare> buildTree(std::vector<std::pair<char, int>>& characterFrequencies, std::string& text);
				
				std::string compress(std::string& text);
				
				std::string decompress(Node* root, std::string& compressedText);

				void findBinaryCode(Node* root, std::string code);

		private:
				sf::RenderWindow* window;
				sf::Event event;
				sf::Font font;
				sf::Text userText;
				sf::Text charFrequencyText;
				
				bool dragging;
				float zoom;
				sf::View view;
				sf::Vector2f pos;
				int width;
				int length;
				State state;

				// codes 
				std::map<char, std::string> codes;
				// text
				std::string text;
				// character frequencies 
				std::vector<std::pair<char, int>> characterFrequencies;
				// create min heap
				std::priority_queue<Node*, std::vector<Node*>, compare> queue;
				Node* root;
				// compressed text
				std::string compressedText;
				// decompressedText
				std::string decompressed;
				
				const std::string characters = "1234567890abcdefghijklmnopqrstuvwxyz"\
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ =+-_,.<>[]{}!@#$%^&*()~?";

};

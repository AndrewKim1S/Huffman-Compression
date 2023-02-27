#include "simulation.h"


simulation::simulation() {}

simulation::simulation(std::string text, std::string textForDisplay) {
		window = new sf::RenderWindow(sf::VideoMode(1500, 900), "Huffman Compression");
		window->setPosition(sf::Vector2i(200, 75));
		width = 1500;
		length = 900;
		this->text = text;
		view = window->getDefaultView();
		zoom = 1;
		dragging = false;
		binaryCodeString = "";
		state = State::START;
		
		font = sf::Font();
		font.loadFromFile("util/PlatNomor-eZ2dm.otf");
		
		userText = sf::Text();
		userText.setFont(font);
		userText.setString(textForDisplay);
		userText.setFillColor(sf::Color::White);
		userText.setCharacterSize(15);
		userText.setPosition(sf::Vector2f(width/20, length/20));
		
		charFrequencyText = sf::Text();
		charFrequencyText.setFont(font);
		charFrequencyText.setFillColor(sf::Color::White);
		charFrequencyText.setCharacterSize(15);
		charFrequencyText.setPosition(sf::Vector2f(width/2.2, length/20));
		
		binaryCodeText = sf::Text();
		binaryCodeText.setFont(font);
		binaryCodeText.setFillColor(sf::Color::White);
		binaryCodeText.setCharacterSize(15);
		binaryCodeText.setPosition(sf::Vector2f(width/1.9, length/20));

		compressText = sf::Text();
		compressText.setFont(font);
		compressText.setFillColor(sf::Color::White);
		compressText.setCharacterSize(15);
		compressText.setPosition(sf::Vector2f(width/1.62, length/20));
}

simulation::~simulation() {
		delete window;
}

void simulation::pollEvents() {
		sf::Vector2f newPos;
		sf::Vector2f delta;

		while(window->pollEvent(event)) {
				switch(event.type) {
						case sf::Event::Closed:
								window->close();
								break;
						case sf::Event::MouseButtonPressed:
								if(event.mouseButton.button == sf::Mouse::Left) {
										dragging = true;
										pos = window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
								}
								break;
						case sf::Event::MouseButtonReleased:
								if(event.mouseButton.button == sf::Mouse::Left) {
										dragging = false;
								}
								break;
						case sf::Event::MouseMoved:
								if(!dragging) {
										break;
								}
								newPos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
								
								delta = pos - newPos;

								view.setCenter(view.getCenter() + delta);
								window->setView(view);
								pos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
								break;
						case sf::Event::MouseWheelScrolled:
								if(dragging) {
										break;
								}
								if(event.mouseWheelScroll.delta <= -1) {
										zoom = std::min(2.f, zoom + 0.1f);
								} else if(event.mouseWheelScroll.delta >= 1) {
										zoom = std::max(0.5f, zoom - 0.1f);
								}
								view.setSize(window->getDefaultView().getSize());
								view.zoom(zoom);
								window->setView(view);
								break;
						case sf::Event::KeyPressed:
								if(event.key.code == sf::Keyboard::Escape) {
										window->close();
								} else if (event.key.code == sf::Keyboard::Right) {
										next();
								}
						default:
								break;
				}
		}
}

void simulation::run() {
		pollEvents();
		render();
}

void simulation::next() {
		switch(state) {
				case State::START:
						state = State::CHARFREQUENCIES;
						characterFrequencies = findCharFrequency(text);
						std::cout << "Finding Character Frequencies" << std::endl;
						break;
				case State::CHARFREQUENCIES:
						state = State::BUILDTREE;
						queue = buildTree(characterFrequencies, text);
						std::cout << "Building Tree" << std::endl;
						break;
				case State::BUILDTREE:
						state = State::BINARYCODES;
						findBinaryCode(queue.top(), "");
						binaryCodeText.setString(binaryCodeString);
						std::cout << "Binary Codes" << std::endl;
						break;
				case State::BINARYCODES:
						state = State::COMPRESS;
						compress(text);
						std::cout << "Compress" << std::endl;
						break;
				case State::COMPRESS:
						state = State::DECOMPRESS;
						decompress(queue.top(), compressedText);
						std::cout << "Decompress" << std::endl;
						break;
				default:
						std::cout << "You have reached the end of the simulation. Press escape to exit" << std::endl;
						break;
		}
}

void simulation::render() {
		window->clear(sf::Color(32, 32, 32));
		window->draw(userText);
		window->draw(charFrequencyText);
		window->draw(binaryCodeText);
		window->draw(compressText);
		window->display();
}

bool simulation::isOpen() {
		return window->isOpen();
}

std::vector<std::pair<char, int>> 
simulation::findCharFrequency(std::string& text) {
		std::vector<std::pair<char, int>> charFrequency;
		std::string charFrequencyString = "";

		for(size_t i = 0; i < characters.length(); i++) {
				int count = 0;
				for(size_t k = 0; k < text.length(); k++) {
						if(characters[i] == text[k]) {
								count ++;
						}
				}
				if(count > 0) {
						charFrequency.emplace_back(std::pair(characters[i], count));
						charFrequencyString += std::string(1,characters[i]) + ": " + std::to_string(count) + "\n";
				}
		}
		charFrequencyText.setString(charFrequencyString);
		characterFrequencies = charFrequency;
		return charFrequency;
}
				

std::priority_queue<Node*, std::vector<Node*>, compare> 
simulation::buildTree(std::vector<std::pair<char, int>>& characterFrequencies, std::string& text) {
		std::priority_queue<Node*, std::vector<Node*>, compare> pq;

		for(auto s : characterFrequencies) {
				pq.push(new Node(s.first, s.second));
		}
		
		Node *left;
		Node *right;
		Node *internal;
		while(pq.size() > 1) {
				left = pq.top();
				pq.pop();

				right = pq.top();
				pq.pop();

				internal = new Node('/', left->frequency + right->frequency);
				internal->left = left;
				internal->right = right;

				pq.push(internal);
		}
		queue = pq;
		return pq;
}
				

std::string simulation::compress(std::string& text) {
		std::string compressed = "";
		std::string forDisplay = "";
		size_t count = 0;
	
		size_t t = 0;
		for(size_t i = 0; i < text.length(); i++) {
				compressed += codes[text[i]];
				
				t += codes[text[i]].length();
				forDisplay += codes[text[i]];
				
				if((t / 80) > count) {
						count ++;
						forDisplay += "\n";
				}
		}
		compressedText = compressed;
		compressText.setString(forDisplay);
		return compressedText;
}
				

std::string simulation::decompress(Node* root, std::string& compressedText) {
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
		decompressed = decompressedText;
		return decompressedText;
}

void simulation::findBinaryCode(Node* root, std::string code) {
		if(!root) {
				return;
		}
		if(root->character != '/') {
				binaryCodeString += std::string(1,root->character) + ": "  + code + "\n";
				codes.insert(std::pair<char,std::string>(root->character, code));
		}
		findBinaryCode(root->left, code + "0");
		findBinaryCode(root->right, code + "1");
}

#include <iostream>


class Node {
		public:
				char character;
				size_t frequency;
				Node *left;
				Node *right;

				Node(char c, size_t f) {
						character = c;
						frequency = f;
						left = NULL;
						right = NULL;
				}

				Node() {}
};

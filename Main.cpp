#include <iostream>
#include <vector>
#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree<int> firstTree;

	std::vector<int> keysForFirstTree = { 10,6, 15, 3, 20, 12, 12, 13, 9, 5, 2, 11, 10 };
	for (int i : keysForFirstTree)
	{
		firstTree.insert(i);
	}

	std::cout << "How much elements are there in this tree?" << ' ' << firstTree.getCount() << "\n\n";
	
	std::cout << "What is the height of the tree" << ' ' << firstTree.getHeight() << "\n\n";

	std::cout << "Tree structure:" << ' ';
	firstTree.print(std::cout);
	std::cout << '\n';

	std::cout << "Other ways to print the tree:\n";
	firstTree.inorderWalk();
	firstTree.iterativeInorderWalk();
	firstTree.walkByLevels();
	std::cout << '\n';
	
	std::cout << "Is there '25' in the structure?" << ' ' << firstTree.iterativeSearch(25) << '\n';
	std::cout << "Is there '6' in the structure?" << ' ' << firstTree.iterativeSearch(6) << "\n\n";


	BinarySearchTree<int> secondTree;

	std::vector<int> keysForSecondTree = { 10,6, 15, 3, 20, 12, 12, 13, 9, 5, 2, 11, 10 };
	for (int i : keysForSecondTree)
	{
		secondTree.insert(i);
	}

	std::cout << "Structure of the second tree:" << ' ';
	firstTree.print(std::cout);
	std::cout << '\n';

	if (firstTree.isIdenticalKey(secondTree) && firstTree.isSimilar(secondTree))
		std::cout << "These trees are similar!\n\n";
	else std::cout << "These trees are not similar!\n\n";
	
	secondTree.deleteKey(3);
	std::cout << "Structure of the second tree after deletion '3':" << ' ';
	secondTree.print(std::cout);
	std::cout << '\n';

	secondTree.deleteKey(10);
	std::cout << "Structure of the second tree after deletion '10':" << ' ';
	secondTree.print(std::cout);
	std::cout << '\n';

	if (firstTree.isIdenticalKey(secondTree) && firstTree.isSimilar(secondTree))
		std::cout << "These trees are similar!\n";
	else std::cout << "These trees are not similar!\n";

	return 0;
}

	
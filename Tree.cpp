/*************************************************
 * ADS Praktikum 2.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;

vector<TreeNode*> vec;


// the following are the private methods, which we will use in order to 
// add in red-black tree correctly
void Tree::balance(TreeNode* node)
{
	TreeNode* ptr = node;
	TreeNode* parent;
	TreeNode* grandpa;
	while (ptr != anker) {
		parent = ptr->getParent();
		grandpa = parent->getParent();
		// parent and kid are red
		if (ptr->getRed() == true && parent->getRed() == true) {
			// parent is right from grandpa
			if (grandpa->getRight() == parent) {
				// current node is right from parent
				if (parent->getRight() == ptr) {
					rotateTreeLeft(grandpa, parent);
					parent->setRed(false);
					grandpa->setRed(true);
				} // current node is left from parent
				else if (parent->getLeft() == ptr) {
					rotateTreeRight(parent, ptr);
					rotateTreeLeft(grandpa, ptr);
					ptr->setRed(false);
					grandpa->setRed(true);
				}
			} // parent is left from grandpa
			else if (grandpa->getLeft() == parent) {
				// current node is left from parent
				if (parent->getLeft() == ptr) {
					rotateTreeRight(grandpa, parent);
					parent->setRed(false);
					grandpa->setRed(true);
				} // current node is right from parent
				else if (parent->getRight() == ptr) {
					rotateTreeLeft(parent, ptr);
					rotateTreeRight(grandpa, ptr);
					ptr->setRed(false);
					grandpa->setRed(true);
				}
			}
		} // after getting to the root stop the iterations
		if (ptr == anker) {
			break;
		}
		ptr = ptr->getParent();
	} // color the root to black
	ptr->setRed(false);
}

bool Tree::split4Node(TreeNode* ptr)
{     // node has both left and right children
	if (ptr->getLeft() != nullptr && ptr->getRight() != nullptr) {
		// if root is black and children are red, change color
		if (ptr->getRed() == false && ptr->getLeft()->getRed() == true && ptr->getRight()->getRed() == true) {
			ptr->getLeft()->setRed(false);
			ptr->getRight()->setRed(false);
			ptr->setRed(true);
			return true;
		}
	}
	return false;
}

int Tree::proofRBCriterion(TreeNode* anker)
{
	int height;
	if (anker == nullptr) return -1;
	
	int leftH = proofRBCriterion(anker->getLeft());
	int rightH = proofRBCriterion(anker->getRight());
	
	// blattknoten
	if (anker->getLeft() == nullptr && anker->getRight() == nullptr) {
		return 0;
	}
	// left empty, right is not
	if (anker->getLeft() == nullptr && anker->getRight() != nullptr) {
		if (anker->getRight()->getRed()) {
			height = rightH;
			return height;
		}
		else if (!anker->getRight()->getRed()) {
			height = rightH + 1;
			return height;
		}
	} // right empty, left is not
	else if (anker->getRight() == nullptr && anker->getLeft() != nullptr) {
		if (anker->getLeft()->getRed()) {
			height = leftH;
			return height;
		}
		else if (!anker->getLeft()->getRed()) {
			height = leftH + 1;
			return height;
		}
	} // node has both children
	else if (anker->getRight() != nullptr && anker->getLeft() != nullptr) {
		// both red
		if (anker->getLeft()->getRed() && anker->getRight()->getRed()) {
			height = rightH;
			return height;
		}
		// both black
		else if (!anker->getLeft()->getRed() && !anker->getRight()->getRed()) {
			if (leftH != rightH) return -1;

			height = rightH + 1;
			return height;
		}
		// left black, right red
		else if (!anker->getLeft()->getRed() && anker->getRight()->getRed()) {
			height = leftH + 1;
			return height;
		}
		// left red, right black
		else if (anker->getLeft()->getRed() && !anker->getRight()->getRed()) {
			height = rightH + 1;
			return height;
		}
	}
}

bool Tree::rotateTreeRight(TreeNode* p, TreeNode* n)
{
	// p's parent is root
	if (p->getParent() == nullptr) {
		anker = n;
		p->setLeft(n->getRight());
		n->setRight(p);
		if (p->getLeft() != nullptr) {
			p->getLeft()->setParent(p);
		}
		p->setParent(n);
		n->setParent(nullptr);
		return true;
	} // p has an ancestor
	else {
		TreeNode* grandpa = p->getParent();
		if (grandpa->getRight() == p) {
			grandpa->setRight(n);
		}
		else if (grandpa->getLeft() == p) {
			grandpa->setLeft(n);
		}
		n->setParent(grandpa);
		p->setLeft(n->getRight());
		if (p->getLeft() != nullptr) {
			p->getLeft()->setParent(p);
		}
		n->setRight(p);
		p->setParent(n);
		return true;
	}
	return false;
}

bool Tree::rotateTreeLeft(TreeNode* p, TreeNode* n)
{
	// p's parent is root
	if (p->getParent() == nullptr) {
		anker = n;
		p->setRight(n->getLeft());
		n->setLeft(p);
		if (p->getRight() != nullptr) {
			p->getRight()->setParent(p);
		}
		p->setParent(n);
		n->setParent(nullptr);
		return true;
	} // p has an ancestor
	else {
		TreeNode* grandpa = p->getParent();
		if (grandpa->getRight() == p) {
			grandpa->setRight(n);
		}
		else if (grandpa->getLeft() == p) {
			grandpa->setLeft(n);
		}
		n->setParent(grandpa);
		p->setRight(n->getLeft());
		if (p->getRight() != nullptr) {
			p->getRight()->setParent(p);
		}
		n->setLeft(p);
		p->setParent(n);
		return true;
	}
	return false;
}

Tree::Tree()
{
	anker = nullptr;
	currentNodeChronologicalID = 0;
}

Tree::~Tree()
{
	if (anker != nullptr) {
		deleteBST(anker);
	}
}

void Tree::addNode(string name, int age, double income, int postCode)
{
	TreeNode* node = new TreeNode(currentNodeChronologicalID++, name, age, income, postCode);
	TreeNode* ptr = anker;
	// if the root, then it's black
	if (anker == nullptr) {
		node->setRed(false);
		anker = node;
		return;
	}

	TreeNode* prev = anker;
	while (ptr != nullptr) {
		prev = ptr;
		// recolor the 4er node, if needed
		split4Node(ptr);
		if (ptr->getNodeOrderID() > node->getNodeOrderID()) {
			ptr = ptr->getLeft();
		}
		else {
			ptr = ptr->getRight();
		}
	}
	if (prev->getNodeOrderID() > node->getNodeOrderID())
	{
		prev->setLeft(node);
	}
	else
	{
		prev->setRight(node);
	}
	node->setParent(prev);
	balance(node);
	return;
}

bool Tree::deleteNode(int nodeOrderID)
{
	if (anker == nullptr) return false;

	// Tree has only one node
	if (anker->getLeft() == nullptr && anker->getRight() == nullptr) {
		if (anker->getNodeOrderID() != nodeOrderID) return false;
		delete anker;
		anker = nullptr;
		return true;
	}
	TreeNode* prev = anker;
	TreeNode* tmp = anker;

	// Search for the node to be deleted
	while (tmp != nullptr && tmp->getNodeOrderID() != nodeOrderID) {
		prev = tmp;
		if (tmp->getNodeOrderID() > nodeOrderID) {
			tmp = tmp->getLeft();
		}
		else {
			tmp = tmp->getRight();
		}
	}

	// Node with this id is not found
	if (tmp == nullptr) return false;

	// bool vars to help to identify, if prev->left or prev->right is equal to tmp
	bool left = false;
	if (prev->getLeft() == nullptr) {
		left = false;
	}
	else if (prev->getRight() == nullptr) {
		left = true;
	}
	else if (prev->getLeft()->getNodeOrderID() == nodeOrderID) {
		left = true;
	}

	// found the node
	// case 1 : the node to delete is a leaf(Blatt)
	if (tmp->getLeft() == nullptr && tmp->getRight() == nullptr) {
		if (left) prev->setLeft(nullptr);
		else prev->setRight(nullptr);
		delete tmp;
		return true;
	}
	// case 2 : the node to delete has a follower
	else if (tmp->getLeft() == nullptr) {
		// root
		if (prev == tmp) {
			anker = tmp->getRight();
			delete tmp;
			return true;
		}

		if (left) prev->setLeft(tmp->getRight());
		else prev->setRight(tmp->getRight());
		delete tmp;
		return true;
	}
	else if (tmp->getRight() == nullptr) {
		// root
		if (prev == tmp) {
			anker = tmp->getLeft();
			delete tmp;
			return true;
		}

		if (left) prev->setLeft(tmp->getLeft());
		else prev->setRight(tmp->getLeft());
		delete tmp;
		return true;
	}
	// case 3 : the node to delete has 2 followers
	else {
		TreeNode* prevMin = tmp->getRight();
		TreeNode* min = prevMin->getLeft();

		// search for the min from the right side of the node to delete
		// if the right node is exactly out node to delete
		if (min == nullptr) {
			prevMin->setLeft(tmp->getLeft());

			// if the node to delete is a root
			if (prev == tmp) {
				anker = prevMin;
				delete tmp;
				return true;
			}

			if (left) prev->setLeft(prevMin);
			else prev->setRight(prevMin);
			delete tmp;
			return true;
		}
		// iterate until minimum
		else {
			while (min->getLeft() != nullptr) {
				prevMin = min;
				min = min->getLeft();
			}

			// found a minimum
			// change the pointers of prev
			if (min->getRight() == nullptr) {
				prevMin->setLeft(nullptr);
			}
			else {
				prevMin->setLeft(min->getRight());
			}
			min->setLeft(tmp->getLeft());
			min->setRight(tmp->getRight());

			// if the node to delete is a root
			if (prev == tmp) {
				anker = min;
				delete tmp;
				return true;
			}

			if (left) prev->setLeft(min);
			else prev->setRight(min);
			delete tmp;
			return true;
		}
	}
}

bool Tree::searchNode(string name)
{
	TreeNode* node = anker;
	return searchForName(node, name);
}

void Tree::printFound(string name)
{
	TreeNode* node = anker;
	collectSame(node, name);
	for (TreeNode* n : vec) {
		cout << "NodeID: " << n->getNodeChronologicalID() << ", Name: " << n->getName() << ", Alter : " << n->getAge() << ", Einkommen: " << n->getIncome() << ", PLZ: " << n->getPostCode() << ", PosID: " << n->getNodeOrderID() << endl;
	}
	vec.clear();
}


void Tree::printAll()
{
	cout << "ID  | Name             | Age   | Income    | PostCode  |  OrderID  |" << endl;
	cout << "----+------------------+-------+-----------+-----------+-----------+" << endl;
	preOrder(anker);
}

void Tree::levelOrder()
{
	int maxLevel = 10;
	cout << "ID  | Name             | Age   | Income    | PostCode  |  OrderID  |Level |  Red |" << endl;
	cout << "----+------------------+-------+-----------+-----------+-----------+------+------|" << endl;

	TreeNode* hilfsPtr = anker;

	// 2 Queue initialization
	std::queue<TreeNode*> q;
	std::queue<int> nq;
	if (hilfsPtr == nullptr) {
		cout << "BST IST LEER" << endl;
		return;
	}

	// root node and start level push to queue
	q.push(hilfsPtr);
	nq.push(0);

	int level;

	while (!q.empty()) {
		// take away from queue and delete
		TreeNode* curr = q.front();
		q.pop();
		level = nq.front();
		nq.pop();

		int red = 0;
		if (curr->getRed() == true) {
			red = 1;
		}

		// max level 10
		if (level > maxLevel) return;

		cout << setfill(' ');
		cout << setw(4) << curr->getNodeChronologicalID() << "|" <<
			setw(18) << curr->getName() << "|" <<
			setw(7) << curr->getAge() << "|" <<
			setw(11) << curr->getIncome() << "|" <<
			setw(11) << curr->getPostCode() << "|" <<
			setw(11) << curr->getNodeOrderID() << "|" <<
			setw(6) << level << "|" << setw(6) << red << "|" << endl;

		// push left followers to the queue
		if (curr->getLeft() != nullptr)
		{
			q.push(curr->getLeft());
			nq.push(level + 1);
		}
		// push right followers to the queue
		if (curr->getRight() != nullptr)
		{
			q.push(curr->getRight());
			nq.push(level + 1);
		}
	}
	return;
}

void Tree::preOrder(TreeNode* anker) {

	TreeNode* ptr = anker;
	if (ptr == nullptr) {
		return;
	}

	ptr->print();

	preOrder(ptr->getLeft());

	preOrder(ptr->getRight());

}
// search for the name by the given name
bool Tree::searchForName(TreeNode* begin, string name) {
	if (begin == nullptr) {
		return false;
	}

	if (begin->getName() == name) {
		return true;
	}

	bool res1 = searchForName(begin->getLeft(), name);

	if (res1) {
		return true;
	}

	bool res2 = searchForName(begin->getRight(), name);
	return res2;
}
// collects all nodes found in the tree with the given name
void Tree::collectSame(TreeNode* begin, string name) {
	if (begin->getLeft() != nullptr) {
		collectSame(begin->getLeft(), name);
	}
	if (begin->getRight() != nullptr) {
		collectSame(begin->getRight(), name);
	}
	if (begin->getName() == name) {
		vec.push_back(begin);
	}
}
// deleting nodes as a utility method for destructor
void Tree::deleteBST(TreeNode* p) {
	if (p->getLeft()) {
		deleteBST(p->getLeft());
		p->setLeft(nullptr);
	}
	if (p->getRight()) {
		deleteBST(p->getRight());
		p->setRight(nullptr);
	}
	if (p->getLeft() == nullptr && p->getRight() == nullptr)
	{
		delete p;
		return;
	}

	return;
}

// the following are the public methods to print out red-black tree
void Tree::printLevelOrder()
{
	TreeNode* hilfsPtr = anker;

	// 2 Queue initialization
	std::queue<TreeNode*> q;
	std::queue<int> nq;

	if (hilfsPtr == nullptr) {
		cout << "BST IST LEER" << endl;
		return;
	}

	// table output
	levelOrder();
	cout << endl;
	cout << "Ausgabe in Levelorder als 234-Baum: " << endl;
	// push starting node and its level
	q.push(hilfsPtr);
	nq.push(0);
	// string variable to print out the result
	string output;
	// niv variable to help sort out the levels for 234 tree
	int level = 0, niv = -1;

	while (!q.empty()) {

		// take away from queue and delete
		TreeNode* curr = q.front();
		q.pop();
		level = nq.front();
		nq.pop();
		// integer to identify the color by number (0 - black, 1 - red)
		int red = 0;
		if (curr->getRed() == true) {
			red = 1;
		}

		// Output in 234 form
		if (red == 0 && curr != nullptr) {
			if (niv != level) {
				cout << '\n';
				cout << "Niv. " << level << ": ";
				niv = level;
			}
			// blattknoten
			if (curr->getLeft() == nullptr && curr->getRight() == nullptr) {
				output = "(" + to_string(curr->getNodeOrderID()) + ")";
			} // black parent, left is nullptr, right is black/red
			else if (curr->getLeft() == nullptr && curr->getRight() != nullptr) {
				if (curr->getRight()->getRed() == false) {
					output = "(" + to_string(curr->getNodeOrderID()) + ")";
				}
				else if (curr->getRight()->getRed() == true) {
					output = "(" + to_string(curr->getNodeOrderID()) + ", " +
						to_string(curr->getRight()->getNodeOrderID()) + ")";
				}
			} // black parent, left is black/red, right is nullptr
			else if (curr->getLeft() != nullptr && curr->getRight() == nullptr) {
				if (curr->getLeft()->getRed() == false) {
					output = "(" + to_string(curr->getNodeOrderID()) + ")";
				}
				else if (curr->getLeft()->getRed() == true) {
					output = "(" + to_string(curr->getLeft()->getNodeOrderID()) + ", " +
						to_string(curr->getNodeOrderID()) + ")";
				}
			}
			else if (curr->getLeft() != nullptr && curr->getRight() != nullptr) {
				// both children of black parent are black
				if (curr->getLeft()->getRed() == false && curr->getRight()->getRed() == false) {
					output = "(" + to_string(curr->getNodeOrderID()) + ")";
				} // both children of black parent are red, 4er Knoten
				else if (curr->getLeft()->getRed() == true && curr->getRight()->getRed() == true) {
					output = "(" + to_string(curr->getLeft()->getNodeOrderID()) + ", " +
						to_string(curr->getNodeOrderID()) + ", " +
						to_string(curr->getRight()->getNodeOrderID()) + ")";
				} // left child is black, right child is red, 3er Knoten
				else if (curr->getLeft()->getRed() == false && curr->getRight()->getRed() == true) {
					output = "(" + to_string(curr->getNodeOrderID()) + ", " +
						to_string(curr->getRight()->getNodeOrderID()) + ")";
				} // left child is red, right child is black, 3er Knoten
				else if (curr->getLeft()->getRed() == true && curr->getRight()->getRed() == false) {
					output = "(" + to_string(curr->getLeft()->getNodeOrderID()) + ", " +
						to_string(curr->getNodeOrderID()) + ")";
				}
			}
			cout << output;
			output = "";
		}

		// push left follower nodes in the queue
		if (curr->getLeft() != nullptr)
		{   // if left is black, push increased level
			if (curr->getLeft()->getRed() == false) {
				q.push(curr->getLeft());
				nq.push(level + 1);
			} // if the left is red, check out the children of this red
			else if (curr->getLeft()->getRed() == true) {
				// if a left child is not null, then it's black. So incerase height
				if (curr->getLeft()->getLeft() != nullptr) {
					q.push(curr->getLeft()->getLeft());
					nq.push(level + 1);
				} // if a right child is not null, then it's black. So incerase height
				if (curr->getLeft()->getRight() != nullptr) {
					q.push(curr->getLeft()->getRight());
					nq.push(level + 1);
				}
			}
		}
		// push right follower nodes in the queue
		if (curr->getRight() != nullptr)
		{   // if right is black, push increased level
			if (curr->getRight()->getRed() == false) {
				q.push(curr->getRight());
				nq.push(level + 1);
			}  // if left is red, check out children of this red 
			else if (curr->getRight()->getRed() == true) {
				// if a left child is not null, then it's black. So incerase height
				if (curr->getRight()->getLeft() != nullptr) {
					q.push(curr->getRight()->getLeft());
					nq.push(level + 1);
				} // if a right child is not null, then it's black. So incerase height
				if (curr->getRight()->getRight() != nullptr) {
					q.push(curr->getRight()->getRight());
					nq.push(level + 1);
				}
			}
		}
	}
	cout << endl;
	return;
}

void Tree::printLevelOrder(int niveau)
{
	TreeNode* hilfsPtr = anker;

	// 2 Queue instanzieren
	std::queue<TreeNode*> q;
	std::queue<int> nq;

	if (hilfsPtr == nullptr) {
		cout << "BST IST LEER" << endl;
		return;
	}
	
	cout << endl;
	cout << "Ausgabe der Knoten aufm Niveau: " << niveau << endl;
	
	q.push(hilfsPtr);
	nq.push(0);

	string output;
	int level = 0, niv = -1;

	while (!q.empty()) {

		
		TreeNode* curr = q.front();
		q.pop();
		level = nq.front();
		nq.pop();

		int red = 0;
		if (curr->getRed() == true) {
			red = 1;
		}

		// Output in 234 form
		if (red == 0 && curr != nullptr) {
			if (niv != level) {
				niv = level;
			}
			// blattknoten
			if (curr->getLeft() == nullptr && curr->getRight() == nullptr) {
				output = "(" + to_string(curr->getNodeOrderID()) + ")";
			} // black parent, left is nullptr, right is black/red
			else if (curr->getLeft() == nullptr && curr->getRight() != nullptr) {
				if (curr->getRight()->getRed() == false) {
					output = "(" + to_string(curr->getNodeOrderID()) + ")";
				}
				else if (curr->getRight()->getRed() == true) {
					output = "(" + to_string(curr->getNodeOrderID()) + ", " +
						to_string(curr->getRight()->getNodeOrderID()) + ")";
				}
			} // black parent, left is black/red, right is nullptr
			else if (curr->getLeft() != nullptr && curr->getRight() == nullptr) {
				if (curr->getLeft()->getRed() == false) {
					output = "(" + to_string(curr->getNodeOrderID()) + ")";
				}
				else if (curr->getLeft()->getRed() == true) {
					output = "(" + to_string(curr->getLeft()->getNodeOrderID()) + ", " +
						to_string(curr->getNodeOrderID()) + ")";
				}
			}
			else if (curr->getLeft() != nullptr && curr->getRight() != nullptr) {
				// both children of black parent are black
				if (curr->getLeft()->getRed() == false && curr->getRight()->getRed() == false) {
					output = "(" + to_string(curr->getNodeOrderID()) + ")";
				} // both children of black parent are red, 4er Knoten
				else if (curr->getLeft()->getRed() == true && curr->getRight()->getRed() == true) {
					output = "(" + to_string(curr->getLeft()->getNodeOrderID()) + ", " +
						to_string(curr->getNodeOrderID()) + ", " +
						to_string(curr->getRight()->getNodeOrderID()) + ")";
				} // left child is black, right child is red, 3er Knoten
				else if (curr->getLeft()->getRed() == false && curr->getRight()->getRed() == true) {
					output = "(" + to_string(curr->getNodeOrderID()) + ", " +
						to_string(curr->getRight()->getNodeOrderID()) + ")";
				} // left child is red, right child is black, 3er Knoten
				else if (curr->getLeft()->getRed() == true && curr->getRight()->getRed() == false) {
					output = "(" + to_string(curr->getLeft()->getNodeOrderID()) + ", " +
						to_string(curr->getNodeOrderID()) + ")";
				}
			} // print out only if the level is equals niveau
			if (level == niveau) {
				cout << output;
				output = "";
			}
			
		}

		if (curr->getLeft() != nullptr)
		{
			if (curr->getLeft()->getRed() == false) {
				q.push(curr->getLeft());
				nq.push(level + 1);
			}
			else if (curr->getLeft()->getRed() == true) {
				if (curr->getLeft()->getLeft() != nullptr) {
					q.push(curr->getLeft()->getLeft());
					nq.push(level + 1);
				}
				if (curr->getLeft()->getRight() != nullptr) {
					q.push(curr->getLeft()->getRight());
					nq.push(level + 1);
				}
			}
		}
		// Rechter Nachfolgeknoten in die Queues
		if (curr->getRight() != nullptr)
		{
			if (curr->getRight()->getRed() == false) {
				q.push(curr->getRight());
				nq.push(level + 1);
			}
			else if (curr->getRight()->getRed() == true) {
				if (curr->getRight()->getLeft() != nullptr) {
					q.push(curr->getRight()->getLeft());
					nq.push(level + 1);
				}
				if (curr->getRight()->getRight() != nullptr) {
					q.push(curr->getRight()->getRight());
					nq.push(level + 1);
				}
			}
		}
	}
	cout << endl;
	return;
}

void Tree::criterionStarter()
{
	if (anker == nullptr) {
		cout << "The tree is empty" << endl;
		return;
	}
	cout << "Proof RB Criterion: " << proofRBCriterion(anker) << endl;
}

/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "TreeNode.h"
#include <iostream>
#include <iomanip>
#include <string>

TreeNode::TreeNode(int nodeChronologicalID, string name, int age, double income, int postCode)
{
	this->nodeOrderID = age + income + postCode;
	this->nodeChronologicalID = nodeChronologicalID;
	this->name = name;
	this->age = age;
	this->income = income;
	this->postCode = postCode;
	this->left = nullptr;
	this->right = nullptr;
	// added parent and red attribute
	this->parent = nullptr;
	this->red = true;
}
// the following are getter and setters for the private attributes
int TreeNode::getNodeOrderID()
{
	return nodeOrderID;
}

void TreeNode::setNodeOrderID(int nodeOrderID)
{
	this->nodeOrderID = nodeOrderID;
}

int TreeNode::getNodeChronologicalID()
{
	return nodeChronologicalID;
}

void TreeNode::setNodeChronologicalID(int nodeChronologicalID)
{
	this->nodeChronologicalID = nodeChronologicalID;
}

string TreeNode::getName()
{
	return name;
}

void TreeNode::setName(string name)
{
	this->name = name;
}

int TreeNode::getAge()
{
	return age;
}

void TreeNode::setAge(int age)
{
	this->age = age;
}

double TreeNode::getIncome()
{
	return income;
}

void TreeNode::setIncome(double income)
{
	this->income = income;
}

int TreeNode::getPostCode()
{
	return postCode;
}

void TreeNode::setPostCode(int postCode)
{
	this->postCode = postCode;
}

TreeNode* TreeNode::getLeft()
{
	return left;
}

void TreeNode::setLeft(TreeNode* left)
{
	this->left = left;
}

TreeNode* TreeNode::getRight()
{
	return right;
}

void TreeNode::setRight(TreeNode* right)
{
	this->right = right;
}
// print out as a table row
void TreeNode::print()
{
	cout << setfill(' ');
	cout << setw(4) << getNodeChronologicalID() << "|" <<
		setw(18) << getName() << "|" <<
		setw(7) << getAge() << "|" <<
		setw(11) << getIncome() << "|" <<
		setw(11) << getPostCode() << "|" <<
		setw(11) << getNodeOrderID() << "|" << endl;
}

// here are the modifications after 2. Praktikum: getter and setters fot parent and red attributes
TreeNode* TreeNode::getParent()
{
	return parent;
}

void TreeNode::setParent(TreeNode* parent)
{
	this->parent = parent;
}

bool TreeNode::getRed()
{
	return red;
}

void TreeNode::setRed(bool red)
{
	this->red = red;
}

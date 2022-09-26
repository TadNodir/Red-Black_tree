/*************************************************
 * ADS Praktikum 2.2
 * Tree.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include "TreeNode.h"
#include "catch.h"
#include <string>

class Tree
{
private:
    TreeNode* anker;
    int currentNodeChronologicalID;
    // the following are the functions added after the 2. Praktikum
    // method to balance nodes with bottom up approach after adding a node
    void balance(TreeNode* anker);
    // recolouring nodes if there is a 4er Node with black parent and red kids
    bool split4Node(TreeNode* anker);
    // method to return the amount of black edges
    int proofRBCriterion(TreeNode* anker);
    // method to carry out a rotation to right
    bool rotateTreeRight(TreeNode* p, TreeNode* n);
    // method to carry out a rotation to lefts
    bool rotateTreeLeft(TreeNode* p, TreeNode* n);

public:
    //Constructor of Tree class
    Tree();
    // Deconstructor of Tree class
    ~Tree();
    // method to add node with corresp. params
    void addNode(string name, int age, double income, int postCode);
    // method to delete node from the tree
    bool deleteNode(int nodeOrderID);
    // method to search for the node by name
    bool searchNode(string name);
    // method to print all nodes in pre order style
    void printAll();
    // method to print all nodes in level order style
    void levelOrder();
    // utility method to print in preorder style
    void preOrder(TreeNode* anker);
    // utility method to search recursively
    bool searchForName(TreeNode* anker, string name);
    // utility method to delete nodes with deconstructor
    void deleteBST(TreeNode* p);
    // print found nodes
    void printFound(string name);
    // search and collect the data
    void collectSame(TreeNode* begin, string name);

    // the following are the new additions after 2. Praktikum
    // print all elements in level order and in 234 form
    void printLevelOrder();
    // print all elements from the level given in parameter in 234 form
    void printLevelOrder(int niveau);
    // public starter for the private method proofRBCriterion
    void criterionStarter();

    ////////////////////////////////////
    // friend-Funktionen sind für die Tests erforderlich und müssen unangetastet
    // bleiben!
    friend TreeNode* get_anker(Tree& TN);
};

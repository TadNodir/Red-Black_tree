/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include <string>

using namespace std;

class TreeNode
{

private:
    int nodeOrderID;
    int nodeChronologicalID;
    string name;
    int age;
    double income;
    int postCode;
    TreeNode* left;
    TreeNode* right;
    // added parent and red private attributes
    TreeNode* parent;
    bool red;

public:
    // Constructor of TreeNode
    TreeNode(int nodeChronologicalID, string name, int age, double income, int postCode);

    // getters and setters for attributes
    int getNodeOrderID();
    void setNodeOrderID(int nodeOrderID);
    int getNodeChronologicalID();
    void setNodeChronologicalID(int nodeChronologicalID);
    string getName();
    void setName(string name);
    int getAge();
    void setAge(int age);
    double getIncome();
    void setIncome(double income);
    int getPostCode();
    void setPostCode(int postCode);
    TreeNode* getLeft();
    void setLeft(TreeNode* left);
    TreeNode* getRight();
    void setRight(TreeNode* right);
    void print();
    // added parent getter and setters
    TreeNode* getParent();
    void setParent(TreeNode* parent);
    // added red attribute getter and setters
    bool getRed();
    void setRed(bool red);
};

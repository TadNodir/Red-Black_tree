# Red-Black_tree

This is a Project for data management and processing. It is implemented through Red-Black tree
and in order to add data we use Top-Down method. Attributes and methods are implemented based on
UML Diagramm (see repository). 

Red-black tree has following characteristics:
1. Each node is either red or black.
2. Each newly added node is red.
3. Children of red node are black nodes.
4. Two consecutive red nodes are not allowed.
5. Balance criteria:
For each node k: Every path from k to leaf node has the same amount of black nodes. 
6. Root is always a black node.

Based on these characteristics we use methods like split4Node, rotateTreeRight, 
rotateTreeLeft, proofRBCriterion, balance in order to balance the tree and make it 
easier to search for information and structurize data.

//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     David Bujzaš <xbujzad00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author David Bujzaš
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class TreeTesting : public testing::Test {
protected:
    BinaryTree tree;
};

class EmptyTree : public TreeTesting {};

class NonEmptyTree : public TreeTesting {
public:
    // set up function to initialize a non empty tree with nodes from the assignment
    void SetUp() override {
        std::vector<int> keys = {2, 1, 5};
        std::vector<std::pair<bool, Node_t*>> newNodes;
        tree.InsertNodes(keys, newNodes);
    }
};

class TreeAxioms : public TreeTesting {
public:
    // set up function to initialize a tree structure from the assignment
    void SetUp() override {
        tree.InsertNode(2);
        tree.InsertNode(1);
        tree.InsertNode(5);
    }
};


TEST_F(EmptyTree, InsertNode) {
    EXPECT_TRUE(tree.InsertNode(2).first);
    EXPECT_FALSE(tree.InsertNode(2).first);
}

TEST_F(EmptyTree, DeleteNode) {
    EXPECT_FALSE(tree.DeleteNode(2));
}

TEST_F(EmptyTree, FindNode) {
    EXPECT_FALSE(tree.FindNode(2));
}

TEST_F(NonEmptyTree, InsertNode) {
    EXPECT_FALSE(tree.InsertNode(2).first);
    EXPECT_TRUE(tree.InsertNode(100).first);
}

TEST_F(NonEmptyTree, DeleteNode) {
    EXPECT_TRUE(tree.DeleteNode(2));
    EXPECT_FALSE(tree.DeleteNode(100));
}

TEST_F(NonEmptyTree, FindNode) {
    EXPECT_TRUE(tree.FindNode(2));
    EXPECT_FALSE(tree.FindNode(100));
}

TEST_F(TreeAxioms, Axiom1) {
    std::vector<Node_t*> leafNodes;
    tree.GetLeafNodes(leafNodes);

    // iterates through leaf nodes and expects them to be black
    for (auto node : leafNodes) {
        EXPECT_EQ(node->color, BLACK);
    }
}

TEST_F(TreeAxioms, Axiom2) {
    std::vector<Node_t*> nonLeafNodes;
    tree.GetNonLeafNodes(nonLeafNodes);

    // iterates through nodes and if they are red, their children should be black
    for (auto node : nonLeafNodes) {
        if (node->color == RED) {
            EXPECT_EQ(node->pLeft->color, BLACK);
            EXPECT_EQ(node->pRight->color, BLACK);
        }
    }
}

TEST_F(TreeAxioms, Axiom3) {
    auto root = tree.GetRoot();
    std::vector<size_t> leafBlackDepths;
    std::vector<Node_t*> leafNodes;
    tree.GetLeafNodes(leafNodes);

    // iterates through all leaf nodes and calculates the amount of black nodes in the path to the root
    for (auto leafNode : leafNodes) {
        size_t blackNodeCount = 0;
        auto tempNode = leafNode;

        // counts all the black nodes from node to root
        while (tempNode != root) {
            tempNode = tempNode->pParent;
            if (tempNode->color == BLACK) {
                blackNodeCount++;
            }
        }

        // stores the number of black nodes from leaf node to root
        leafBlackDepths.push_back(blackNodeCount);
    }

    // initial reference, takes the first leaf node black node count
    size_t blackDepth = leafBlackDepths[0];

    // iterates through all black node counts and compares with initial reference
    for (size_t depth : leafBlackDepths) {
        // expects all paths to have the same amount of black node as the initial reference
        EXPECT_EQ(blackDepth, depth);
        blackDepth = depth;
    }
}

/*** Konec souboru black_box_tests.cpp ***/

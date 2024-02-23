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

#include "libs/red_black_tree.h"

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

class EmptyTree: public testing::Test {
    
protected:
    BinaryTree tree;
};

class NonEmptyTree: public testing::Test {

    void SetUp() override {
        
        std::vector<int> keys = {2,1,5};
        std::vector<std::pair<bool,Node_t*>> newNodes;
        tree.InsertNodes(keys, newNodes);
    
    }

protected:
    BinaryTree tree;
};

class TreeAxioms: public testing::Test {
    
    void SetUp() override {
        
        tree.InsertNode(2);
        tree.InsertNode(1);
        tree.InsertNode(5);

        tree.FindNode(2)->color = BLACK;
        tree.FindNode(1)->color = RED;
        tree.FindNode(5)->color = RED;

    }

protected:
    BinaryTree tree;
};

TEST_F(EmptyTree, insertNode) {
    
    auto node = tree.InsertNode(2);
    EXPECT_TRUE(node.first);

    node = tree.InsertNode(2);
    EXPECT_FALSE(node.first);

}

TEST_F(EmptyTree, deleteNode) {

    EXPECT_FALSE(tree.DeleteNode(2));

}

TEST_F(EmptyTree, findNode) {

    EXPECT_FALSE(tree.FindNode(2));

}

TEST_F(NonEmptyTree, insertMultipleNodes) {

    auto insertX = tree.InsertNode(2);
    EXPECT_FALSE(insertX.first);

    auto insertY = tree.InsertNode(100);
    EXPECT_TRUE(insertY.first);

}

TEST_F(NonEmptyTree, deleteMultipleNodes) {

    EXPECT_TRUE(tree.DeleteNode(2));
    EXPECT_FALSE(tree.DeleteNode(100));

}

TEST_F(NonEmptyTree, findMultipleNodes) {
    
    EXPECT_TRUE(tree.FindNode(2));
    EXPECT_FALSE(tree.FindNode(100));

}

TEST_F(TreeAxioms, Axiom1) {

    std::vector<Node_t*> leafNodes;
    tree.GetLeafNodes(leafNodes);

    for(auto node: leafNodes) {
        EXPECT_EQ(node->color, BLACK);
    }

}

TEST_F(TreeAxioms, Axiom2) {

    std::vector<Node_t*> leafNodes;
    tree.GetNonLeafNodes(leafNodes);

    for(auto node: leafNodes) {
        if(node->color == RED) {
            EXPECT_EQ(node->pLeft->color, BLACK);
            EXPECT_EQ(node->pRight->color, BLACK);
        }
    }

}

TEST_F(TreeAxioms, Axiom3) {

    auto root = tree.GetRoot();
    std::vector<size_t> leafBlackNodes;
    std::vector<Node_t*> leafNodes;
    tree.GetLeafNodes(leafNodes);

    for (auto i = leafNodes.begin(); i != leafNodes.end(); ++i) {
        auto node = *i;
        size_t blackNodeCount = 0;
        auto tempNode = node;

        while (tempNode != root) {
            tempNode = tempNode->pParent;
            if (tempNode->color == BLACK) {
                blackNodeCount++;
            }
        }
        
        leafBlackNodes.push_back(blackNodeCount);
    }

    size_t blackNodeCount = leafBlackNodes[0];
    
    for (auto i = leafBlackNodes.begin(); i != leafBlackNodes.end(); ++i) {
        EXPECT_EQ(blackNodeCount, *i);
        blackNodeCount = *i;
    }
    
}

/*** Konec souboru black_box_tests.cpp ***/

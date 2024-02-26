//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     David Bujzaš <xbujzad00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author David Bujzaš
 * 
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem 
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v 
//       indexu
//============================================================================//

class HashMapTests : public testing::Test {
protected:
    // pointer to hash map
    hash_map_t *map; 

    // set up function for empty hash map
    void SetUpEmpty() {
        map = hash_map_ctor();
    }

    // set up function for non empty map
    void SetUpNonEmpty() {
        map = hash_map_ctor();
        // key-value pairs from the assignment
        hash_map_put(map, "exotic", 42);
        hash_map_put(map, "commission", 9999);
        hash_map_put(map, "Ruzovy ponik", 85);
    }

    // clean up function
    void TearDown() override {
        hash_map_dtor(map);
    }
};

//EmptyTable tests
TEST_F(HashMapTests, ClearEmptyMap) {
    SetUpEmpty();
    hash_map_clear(map);
    EXPECT_EQ(map->first, nullptr);
    EXPECT_EQ(map->last, nullptr);
    EXPECT_EQ(map->used, 0);
}

TEST_F(HashMapTests, ReserveOnEmptyMap) {
    SetUpEmpty();
    ASSERT_NE(hash_map_reserve(map, 69), MEMORY_ERROR);
    EXPECT_EQ(hash_map_reserve(map, 69), OK);
}

TEST_F(HashMapTests, SizeOfEmptyMap) {
    SetUpEmpty();
    EXPECT_EQ(hash_map_size(map), 0);
}

TEST_F(HashMapTests, CapacityOfEmptyMap) {
    SetUpEmpty();
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE);
}

TEST_F(HashMapTests, ContainsStringInEmptyMap) {
    SetUpEmpty();
    EXPECT_EQ(hash_map_contains(map, "key"), 0);
}

TEST_F(HashMapTests, InsertIntoEmptyMap) {
    SetUpEmpty();
    ASSERT_EQ(hash_map_contains(map, "Ruzovy ponik"), 0);
    EXPECT_EQ(hash_map_put(map, "Ruzovy ponik", 85), OK);
    EXPECT_EQ(hash_map_put(map, "Ruzovy ponik", 85), KEY_ALREADY_EXISTS);
}

TEST_F(HashMapTests, GetFromEmptyMap) {
    SetUpEmpty();
    int val;
    EXPECT_EQ(hash_map_get(map, "Ruzovy ponik", &val), KEY_ERROR);
}

TEST_F(HashMapTests, PopFromEmptyMap) {
    SetUpEmpty();
    int val;
    EXPECT_EQ(hash_map_pop(map, "Ruzovy ponik", &val), KEY_ERROR);
}

TEST_F(HashMapTests, RemoveFromEmptyMap) {
    SetUpEmpty();
    EXPECT_EQ(hash_map_remove(map, "Ruzovy ponik"), KEY_ERROR);
}

//NonEmptyTableTests
TEST_F(HashMapTests, ClearNonEmptyMap) {
    SetUpNonEmpty();
    hash_map_clear(map);
    EXPECT_EQ(map->first, nullptr);
    EXPECT_EQ(map->last, nullptr);
    EXPECT_EQ(map->used, 0);

    for(int i = 0; i < map->allocated; i++) {
        EXPECT_EQ(map->index[i], nullptr);
    }
}

TEST_F(HashMapTests, ReserveOnNonEmptyMap) {
    SetUpNonEmpty();
    ASSERT_NE(hash_map_reserve(map, 1), MEMORY_ERROR);
    EXPECT_EQ(hash_map_reserve(map, 1), VALUE_ERROR);
    ASSERT_NE(hash_map_reserve(map, 69), MEMORY_ERROR);
    EXPECT_EQ(hash_map_reserve(map, 69), OK);
}

TEST_F(HashMapTests, SizeOfNonEmptyMap) {
    SetUpNonEmpty();
    EXPECT_EQ(hash_map_size(map), 3);
}

TEST_F(HashMapTests, CapacityofNonEmptyMap) {
    SetUpNonEmpty();
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE);
}

TEST_F(HashMapTests, ContainsStringInNonEmptyMap) {
    SetUpNonEmpty();
    EXPECT_EQ(hash_map_contains(map, "key"), 0);
    EXPECT_EQ(hash_map_contains(map, "Ruzovy ponik"), 1);
}

TEST_F(HashMapTests, InsertIntoNonEmptyMap) {
    SetUpNonEmpty();
    ASSERT_EQ(hash_map_contains(map, "Ruzovy ponik"), 1);
    ASSERT_NE(hash_map_put(map, "Ruzovy ponik", 85), MEMORY_ERROR);
    EXPECT_EQ(hash_map_put(map, "Ruzovy ponik", 85), KEY_ALREADY_EXISTS);
    EXPECT_EQ(hash_map_put(map, "key", 10), OK);
}

TEST_F(HashMapTests, GetFromNonEmptyMap) {
    SetUpNonEmpty();
    int val;
    EXPECT_EQ(hash_map_get(map, "Ruzovy ponik", &val), OK);
    EXPECT_EQ(hash_map_get(map, "koteseni", &val), KEY_ERROR);
}

TEST_F(HashMapTests, PopFromNonEmptyMap) {
    SetUpNonEmpty();
    int val;
    EXPECT_EQ(hash_map_pop(map, "Ruzovy ponik", &val), OK);
    EXPECT_EQ(hash_map_pop(map, "exotic", &val), OK);
    EXPECT_EQ(hash_map_pop(map, "koteseni", &val), KEY_ERROR);
}

TEST_F(HashMapTests, RemoveFromNonEmptyMap) {
    SetUpNonEmpty();
    EXPECT_EQ(hash_map_remove(map, "Ruzovy ponik"), OK);
    EXPECT_EQ(hash_map_remove(map, "koteseni"), KEY_ERROR);
}

/*** Konec souboru white_box_tests.cpp ***/

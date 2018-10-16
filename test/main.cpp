/**============================================================================
 * @file         main.cpp
 * Author      : Rishabh Choudhary, Akash Atharv
 * Version     : 1.0
 * @Copyright  : MIT License
 * Copyright 2018 Rishabh Choudhary, Akash Atharv
 * @brief        file for unit test cases of googletest
 *============================================================================
 */

#include <gtest/gtest.h>

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

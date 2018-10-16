/**============================================================================
 * @file        : main.cpp
 * @author      : Rishabh Choudhary, Akash Atharv
 * @version     : 1.0
 * @copyright   : MIT License
 * Copyright 2018 Rishabh Choudhary, Akash Atharv
 * @brief       : Runs Test cases for testing and generating code coverage
 *============================================================================
 */

#include <gtest/gtest.h>

/**
 * @brief Unit tests called from main()
 * @param none
 * @return 0 on successful execution and exit
 */

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

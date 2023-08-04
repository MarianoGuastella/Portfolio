#include "gtest-1.8.1/gtest.h"
#include "../src/main.h"

TEST(npm_test, test_bt1){
    vector<pair<int,int>> L = {pair<int,int>(10,5), pair<int,int>(1,2), pair<int,int>(1,3), pair<int,int>(1,4), pair<int,int>(1,5), pair<int,int>(1,6), pair<int,int>(1,7), pair<int,int>(1,8), pair<int,int>(1,9)};
    int M = 5;
    ASSERT_EQ(npm_backtracking(L,M,19), 10);
}
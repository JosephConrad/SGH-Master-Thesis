//
// Created by Konrad Lisiecki on 22/02/16.
//
#include <algorithm>
#include <gtest/gtest.h>
#include <src/main/cpp/tools/config/Config.h>



TEST(cpp_sorter_test, int_arr_sort) {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int eq[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sz = sizeof(arr) / sizeof(arr[0]);


    for (int i = 0; i < sz; i++) {
        EXPECT_EQ(arr[i], eq[i]);
    }
}

TEST(tools_test, config_test) {
    EXPECT_EQ(Config::getInstance().getSettings("Log.logFile"), "logs/log.txt");
}

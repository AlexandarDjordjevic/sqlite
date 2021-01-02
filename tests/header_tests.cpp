#include <gtest/gtest.h>
#include <SQLite/Header.hpp>


TEST(LoadDatabase, NonexistingFile){
    auto header = new SQLite::Header();
    ASSERT_EQ(false, header->LoadFromFile("nonexisting.db"));
}
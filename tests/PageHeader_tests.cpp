#include <gtest/gtest.h>
#include <SQLite/PageHeader.hpp>
#include <iostream>

uint8_t testData[] ={
    0x02,
    0x01, 0x02,
    0x03, 0x04,
    0x05, 0x06,
    0x07, 
    0x08, 0x09, 0x0a, 0x0b
};

TEST(PageHeader, Deserialize){
    SQLite::PageHeader header;
    header.Deserialize(testData);
    ASSERT_NE(3, header.GetFlags());
    ASSERT_EQ(2, header.GetFlags());
}


#include <gtest/gtest.h>
#include <SQLite/Header.hpp>
#include <iostream>

const unsigned char validDatabseData[100] =
{
    0x53, 0x51, 0x4c, 0x69, 0x74, 0x65, 0x20, 0x66, 0x6f, 0x72, 0x6d, 0x61, 0x74, 0x20, 0x33, 0x00, 0x10, 0x00, 0x01, 0x01,
    0x00, 0x40, 0x20, 0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x2e, 0x3f, 0xd9
};

const unsigned char invalidDatabseData[100] =
{
    0x53, 0x00, 0x4c, 0x69, 0x74, 0x65, 0x20, 0x66, 0x6f, 0x72, 0x6d, 0x61, 0x74, 0x20, 0x33, 0x00, 0x10, 0x00, 0x01, 0x01,
    0x00, 0x40, 0x20, 0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x2e, 0x3f, 0xd9
};

class DatabaseFileMock : public testing::Test
{
private:
public:
    FILE* validTestFile;
    FILE* invalidTestFile;
    SQLite::Header header;
public:
    void SetUp() override{
        validTestFile = fopen("ValidTestFile.db", "wb+");
        invalidTestFile = fopen("InvalidTestFile.db", "wb+");
        fwrite(validDatabseData, 1, 100, validTestFile);
        fwrite(invalidDatabseData, 1, 100, invalidTestFile);
        fclose(validTestFile);
        fclose(invalidTestFile);

    }

    void TearDown() override{
        std::remove("ValidTestFile.db");
        std::remove("InvalidTestFile.db");
    }

    ~DatabaseFileMock() = default;
};


TEST_F(DatabaseFileMock, NonexistingFile){
    ASSERT_EQ(false, header.LoadFromFile("nonexisting.db"));
}

TEST_F(DatabaseFileMock, InvalidHeaderFile){
    ASSERT_EQ(false, header.LoadFromFile("InvalidTestFile.db"));
}


TEST_F(DatabaseFileMock, ValidHeaderFile){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
}

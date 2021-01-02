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


TEST_F(DatabaseFileMock, GetHeaderString){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ("SQLite format 3\x0", header.GetHeaderString());
}

TEST_F(DatabaseFileMock, GetDatabasePageSize){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(4096, header.GetDatabasePageSize());
}

TEST_F(DatabaseFileMock, GetWriteVersion){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(SQLite::Header::rw_version::Legacy, header.GetWriteVersion());
}

TEST_F(DatabaseFileMock, GetReadVersion){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(SQLite::Header::rw_version::Legacy, header.GetReadVersion());
}

TEST_F(DatabaseFileMock, GetBytesOfPageUnusedSpace){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(0, header.GetBytesOfPageUnusedSpace());
}

TEST_F(DatabaseFileMock, GetMaximumPayloadFraction){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(64, header.GetMaximumPayloadFraction());
}

TEST_F(DatabaseFileMock, GetMinimumPayloadFraction){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(32, header.GetMinimumPayloadFraction());
}

TEST_F(DatabaseFileMock, GetLeafPayloadFraction){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(32, header.GetLeafPayloadFraction());
}

TEST_F(DatabaseFileMock, GetFileChangeCounter){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(4, header.GetFileChangeCounter());
}

TEST_F(DatabaseFileMock, GetDatabaseSizeInPages){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(4, header.GetDatabaseSizeInPages());
}

TEST_F(DatabaseFileMock, GetFirstFreelistPage){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(0, header.GetFirstFreelistPage());
}

TEST_F(DatabaseFileMock, GetNumberOfFreelistPages){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(0, header.GetNumberOfFreelistPages());
}   

TEST_F(DatabaseFileMock, GetSchemaCookie){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(3, header.GetSchemaCookie());
}   

TEST_F(DatabaseFileMock, GetSchemaFormatNumber){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(4, header.GetSchemaFormatNumber());
}    

TEST_F(DatabaseFileMock, GetDefaultPageCacheSize){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(0, header.GetDefaultPageCacheSize());
}    

TEST_F(DatabaseFileMock, GetRootBTreePage){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(0, header.GetRootBTreePage());
}    

TEST_F(DatabaseFileMock, GetTextEncoding){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(SQLite::Header::encoding::UTF8, header.GetTextEncoding());
}    

TEST_F(DatabaseFileMock, GetUserVersion){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(0, header.GetUserVersion());
}    

TEST_F(DatabaseFileMock, GetIncrementalVacuumMode){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(0, header.GetIncrementalVacuumMode());
}    

TEST_F(DatabaseFileMock, GetApplicationId){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(0, header.GetApplicationId());
}    

TEST_F(DatabaseFileMock, GetVersionValidFor){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(4, header.GetVersionValidFor());
}    

TEST_F(DatabaseFileMock, GetSqliteVersionNumber){
    ASSERT_EQ(true, header.LoadFromFile("ValidTestFile.db"));
    ASSERT_EQ(3031001, header.GetSqliteVersionNumber());
}

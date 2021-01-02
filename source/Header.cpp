#include <string.h>
#include <sstream>
#include <SQLite/Header.hpp>
#include <Helpers.hpp>


#define COLOR_RESET "\u001b[0m"
#define COLOR_GREEN "\u001b[32m"
#define COLOR_RED "\u001b[31m"

namespace SQLite
{
    Header::Header() = default;
    
    Header::~Header(){
        
    }

    bool Header::LoadFromFile(const std::string& file_path) 
    {
        database_file = file_path;
        FILE* db = fopen(file_path.c_str(), "rb");
        if (db == NULL){
            perror("Fail to open database file");
            return false;
        }

        uint8_t data[sizeof(sql_header)];
        size_t fetched = fread(data, 1, sizeof(sql_header), db);
        if (sizeof(sql_header) != fetched){
            fclose(db);
            return false;
        }

        if (ParseHeader(data) == false){
            fclose(db);
            return false;
        }

        fclose(db);
        return true;
    }

    bool Header::ParseHeader(const uint8_t* header_buffer){
        memcpy((void *)&header_ctx, header_buffer, sizeof(header_ctx));
        if (strcmp(Header::HEADER_STRING.c_str(), header_ctx.header_string) != 0)
            return false;

        if ( Helpers::IsLittleEndian() ){ 
            header_ctx.db_page_size = Helpers::ChangeEndian_U16(header_ctx.db_page_size);
            header_ctx.file_change_counter = Helpers::ChangeEndian_U32(header_ctx.file_change_counter);    
            header_ctx.db_size_in_pages = Helpers::ChangeEndian_U32(header_ctx.db_size_in_pages);
            header_ctx.version_valid_for = Helpers::ChangeEndian_U32(header_ctx.version_valid_for);
            header_ctx.sqlite_version_number = Helpers::ChangeEndian_U32(header_ctx.sqlite_version_number);
            SetSQLiteVersion(header_ctx.sqlite_version_number);
        }

        return true;
    }

    void Header::PrintInfo(){
        printf(COLOR_GREEN);
        printf("\n*******************************************************************************\n");
        printf(" Database File:   %s\n", database_file.c_str());
        printf(" SQLite Version:  %s\n", sqlite_version.c_str());
        printf("*******************************************************************************\n");
        printf("Database data: \n");
        printf("-------------------------------------------------------------------------------\n");
        printf("\tHeader String ............... %s\n", header_ctx.header_string);
        printf("\tPage Size ................... %d\n", header_ctx.db_page_size);
        printf("\tWrite Version ............... %d\n", int(header_ctx.write_version));
        printf("\tRead Version ................ %d\n", int(header_ctx.read_version));
        printf("\tDatabase size in pages ...... %d\n", header_ctx.db_size_in_pages);
        printf("\tMaximum Payload Fraction .... %d\n", header_ctx.maximum_payload_fraction);
        printf("\tMinumum Payload Fraction .... %d\n", header_ctx.minimum_payload_fraction);
        printf("\tLeaf payload fraction ....... %d\n", header_ctx.leaf_payload_fraction);
        printf("\tFile change counter ......... %d\n", header_ctx.file_change_counter);
        printf("\tSQLite Version Number ....... %d\n", header_ctx.sqlite_version_number);
        printf("\tVersion Valid ............... %d\n", header_ctx.version_valid_for);
        printf("-------------------------------------------------------------------------------\n");
        printf("*******************************************************************************\n");
        printf(COLOR_RESET);
    }
    
    std::string Header::GetHeaderString() 
    {
        return std::string(header_ctx.header_string);
    }
    
    uint16_t Header::GetDatabasePageSize() 
    {
        return header_ctx.db_page_size;
    }
    
    Header::rw_version Header::GetWriteVersion() 
    {
        return header_ctx.write_version;
    }
    
    Header::rw_version Header::GetReadVersion() 
    {
        return header_ctx.read_version;
    }
    
    uint8_t Header::GetBytesOfPageUnusedSpace() 
    {
        return header_ctx.bytes_of_page_unused_space;
    }
    
    uint8_t Header::GetMaximumPayloadFraction() 
    {
        return header_ctx.maximum_payload_fraction;
    }
    
    uint8_t Header::GetMinimumPayloadFraction() 
    {
        return header_ctx.minimum_payload_fraction;
    }
    
    uint8_t Header::GetLeafPayloadFraction() 
    {
        return header_ctx.leaf_payload_fraction;
    }
    
    uint32_t Header::GetFileChangeCounter() 
    {
        return header_ctx.file_change_counter;
    }
    
    uint32_t Header::GetDatabaseSizeInPages() 
    {
        return header_ctx.db_size_in_pages;
    }
    


    void Header::SetSQLiteVersion(uint32_t numeric_version){
        auto x = numeric_version / 1000000;
        auto y = (numeric_version % 1000000) / 1000;
        auto z = numeric_version % 1000;

        std::stringstream version;
        version << std::to_string(x) << '.' << std::to_string(y) << '.' << std::to_string(z);
        sqlite_version = version.str();
    }


}
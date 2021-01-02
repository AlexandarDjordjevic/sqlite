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
        printf("\tHeader String ............... %s\n", GetHeaderString().c_str());
        printf("\tPage Size ................... %d\n", GetDatabasePageSize());
        printf("\tWrite Version ............... %d\n", int(GetWriteVersion()));
        printf("\tRead Version ................ %d\n", int(GetReadVersion()));
        printf("\tDatabase size in pages ...... %d\n", GetDatabaseSizeInPages());
        printf("\tMaximum Payload Fraction .... %d\n", GetMaximumPayloadFraction());
        printf("\tMinumum Payload Fraction .... %d\n", GetMinimumPayloadFraction());
        printf("\tLeaf payload fraction ....... %d\n", GetLeafPayloadFraction());
        printf("\tFile change counter ......... %d\n", GetFileChangeCounter());
        printf("\tSQLite Version Number ....... %d\n", GetSqliteVersionNumber());
        printf("\tVersion Valid ............... %d\n", GetVersionValidFor());
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
        return Helpers::IsLittleEndian() ? 
               Helpers::ChangeEndian_U16(header_ctx.db_page_size) :
               header_ctx.db_page_size;
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
        return Helpers::IsLittleEndian() ? 
               Helpers::ChangeEndian_U32(header_ctx.file_change_counter) :
               header_ctx.file_change_counter;
    }   
    
    uint32_t Header::GetDatabaseSizeInPages() 
    {
        return Helpers::IsLittleEndian() ? 
               Helpers::ChangeEndian_U32(header_ctx.db_size_in_pages) :
               header_ctx.db_size_in_pages;
    }
    
    uint32_t Header::GetFirstFreelistPage() 
    {
        return Helpers::IsLittleEndian() ? 
               Helpers::ChangeEndian_U32(header_ctx.first_freelist_page) :
               header_ctx.first_freelist_page;
    }
    
    uint32_t Header::GetNumberOfFreelistPages() 
    {
        return Helpers::IsLittleEndian() ? 
               Helpers::ChangeEndian_U32(header_ctx.number_of_freelist_pages) :
               header_ctx.number_of_freelist_pages;
    }
    
    uint32_t Header::GetSchemaCookie() 
    {
        return Helpers::IsLittleEndian() ? 
               Helpers::ChangeEndian_U32(header_ctx.schema_cookie) : 
               header_ctx.schema_cookie;
    }
    
    uint32_t Header::GetSchemaFormatNumber() 
    {
        return Helpers::IsLittleEndian() ? 
               Helpers::ChangeEndian_U32(header_ctx.schema_format_number) :
               header_ctx.schema_format_number;
    }
    
    uint32_t Header::GetDefaultPageCacheSize() 
    {
        return Helpers::IsLittleEndian() ? 
               Helpers::ChangeEndian_U32(header_ctx.default_page_cache_size) :
               header_ctx.default_page_cache_size;
    }
    
    uint32_t Header::GetRootBTreePage() 
    {
        return Helpers::IsLittleEndian() ? 
               Helpers::ChangeEndian_U32(header_ctx.root_b_tree_page) :
               header_ctx.root_b_tree_page;
    }
    
    Header::encoding Header::GetTextEncoding() 
    {
        return Helpers::IsLittleEndian() ? 
               Header::encoding (Helpers::ChangeEndian_U32(uint32_t (header_ctx.text_encoding))) : 
               Header::encoding (header_ctx.text_encoding);
    }
    
    uint32_t Header::GetUserVersion() 
    {
        return Helpers::IsLittleEndian() ?
               Helpers::ChangeEndian_U32(header_ctx.user_version) :
               header_ctx.user_version;
    }
    
    uint32_t Header::GetIncrementalVacuumMode() 
    {
        return Helpers::IsLittleEndian() ?
               Helpers::ChangeEndian_U32(header_ctx.incremental_vacuum_mode) :
               header_ctx.incremental_vacuum_mode;
    }
    
    uint32_t Header::GetApplicationId() 
    {
        return Helpers::IsLittleEndian() ?
               Helpers::ChangeEndian_U32(header_ctx.application_id) :
               header_ctx.application_id;
    }
    
    uint32_t Header::GetVersionValidFor() 
    {
        return Helpers::IsLittleEndian() ?
               Helpers::ChangeEndian_U32(header_ctx.version_valid_for) :
               header_ctx.version_valid_for;
    }
    
    uint32_t Header::GetSqliteVersionNumber() 
    {
        return Helpers::IsLittleEndian() ? 
               Helpers::ChangeEndian_U32(header_ctx.sqlite_version_number) :
               header_ctx.sqlite_version_number;
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
/**
 * @author Aleksandar Djordjevic (alexandar1608@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string>

/**
 * @brief SQL Header
 * 
 * Offset	Size	Description
 * 0	    16	    The header string: "SQLite format 3\000"
 * 16	    2	    The database page size in bytes. Must be a power of two between 512 and 32768 inclusive, or the value 1
 * representing  a page size of 65536.
 * 18	    1	    File format write version. 1 for legacy; 2 for WAL.
 * 19	    1	    File format read version. 1 for legacy; 2 for WAL.
 * 20	    1	    Bytes of unused "reserved" space at the end of each page. Usually 0.
 * 21	    1	    Maximum embedded payload fraction. Must be 64.
 * 22	    1	    Minimum embedded payload fraction. Must be 32.
 * 23	    1	    Leaf payload fraction. Must be 32.
 * 24	    4	    File change counter.
 * 28	    4	    Size of the database file in pages. The "in-header database size".
 * 32	    4	    Page number of the first freelist trunk page.
 * 36	    4	    Total number of freelist pages.
 * 40	    4	    The schema cookie.
 * 44	    4	    The schema format number. Supported schema formats are 1, 2, 3, and 4.
 * 48	    4	    Default page cache size.
 * 52	    4	    The page number of the largest root b-tree page when in auto-vacuum or incremental-vacuum modes, or zero otherwise.
 * 56	    4	    The database text encoding. A value of 1 means UTF-8. A value of 2 means UTF-16le. A value of 3 means UTF-16be.
 * 60	    4	    The "user version" as read and set by the user_version pragma.
 * 64	    4	    True (non-zero) for incremental-vacuum mode. False (zero) otherwise.
 * 68	    4	    The "Application ID" set by PRAGMA application_id.
 * 72	    20  	Reserved for expansion. Must be zero.
 * 92	    4	    The version-valid-for number.
 * 96	    4	    SQLITE_VERSION_NUMBER
 * 
 * TestDB.db
 * sqlite> CREATE TABLE COMPANY(
 *      ID INT PRIMARY KEY     NOT NULL,
 *      NAME           TEXT    NOT NULL,
 *      AGE            INT     NOT NULL,
 *      ADDRESS        CHAR(50),
 *      SALARY         REAL
 *  );
*/

namespace SQLite
{
class Header{
public:
    /* Typedefs */
    enum class rw_version : uint8_t {
        Legacy = 0x01,
        WAL    = 0x02
    };

    enum class encoding : uint32_t { 
        UTF8 = 1,
        UTF16LE = 2, 
        UTF16BE = 3
    };
private:

    struct __attribute__((__packed__)) sql_header{
        char header_string[16];
        uint16_t db_page_size;
        rw_version write_version;
        rw_version read_version;
        uint8_t bytes_of_page_unused_space;
        uint8_t maximum_payload_fraction;   //Must be 64.
        uint8_t minimum_payload_fraction;   //Must be 32.
        uint8_t leaf_payload_fraction;   //Must be 32.
        uint32_t file_change_counter;
        uint32_t db_size_in_pages;
        uint32_t first_freelist_page;
        uint32_t number_of_freelist_pages;
        uint32_t schema_cookie;
        uint32_t schema_format_number;
        uint32_t default_page_cache_size;
        uint32_t root_b_tree_page;
        encoding text_encoding;
        uint32_t user_version;
        uint32_t incremental_vacuum_mode;
        uint32_t application_id;
        uint8_t reserved[20];
        uint32_t version_valid_for;
        uint32_t sqlite_version_number;
    };
public:
    const std::string HEADER_STRING = "SQLite format 3";

    /**
     * @brief Default contstructor
     * 
     */
    Header();

    /**
     * @brief Default destructor
     * 
     */
    ~Header();

    Header(const Header &) = delete;
    Header &operator=(const Header &) = delete;
    Header(Header &&) = delete;
    Header &operator=(const Header &&) = delete;

    /**
     * @brief Load database from file
     * 
     * @param file_path path to database file
     * @return true
     * @return false 
     */
    bool LoadFromFile(const std::string& file_path);

    /**
     * @brief Parse database header 
     * 
     * @param header_buffer 
     * @return true 
     * @return false 
     */
    bool ParseHeader(const uint8_t* header_buffer);

    /**
     * @brief Print database info
     * 
     */
    void PrintInfo();

    /**
     * @brief Get the header string: "SQLite format 3\000"
     * 
     * @return std::string
     */
    std::string GetHeaderString();

    /**
     * @brief Get the database page size in bytes. Must be a power of two between 512 and 32768 inclusive, 
     * or the value 1 representing a page size of 65536.
     * 
     * @return uint16_t 
     */
    uint16_t GetDatabasePageSize();

    /**
     * @brief Get the file format write version. 1 for legacy; 2 for WAL.
     * 
     * @return rw_version 
     */
    rw_version GetWriteVersion();

    /**
     * @brief Get the file format read version. 1 for legacy; 2 for WAL.
     * 
     * @return rw_version 
     */
    rw_version GetReadVersion();

    /**
     * @brief Get number of bytes of unused "reserved" space at the end of each page. Usually 0.
     * 
     * @return uint8_t 
     */
    uint8_t GetBytesOfPageUnusedSpace();

    /**
     * @brief Get the maximum embedded payload fraction. Must be 64.
     * 
     * @return uint8_t 
     */
    uint8_t GetMaximumPayloadFraction();

    /**
     * @brief Get the minimum embedded payload fraction. Must be 32.
     * 
     * @return uint8_t 
     */
    uint8_t GetMinimumPayloadFraction();

    /**
     * @brief Get the leaf payload fraction. Must be 32.
     * 
     * @return uint8_t 
     */
    uint8_t GetLeafPayloadFraction();

    /**
     * @brief Get the file change counter
     * 
     * @return uint32_t 
     */
    uint32_t GetFileChangeCounter();

    /**
     * @brief Get the database file in pages. The "in-header database size".
     * 
     * @return uint32_t 
     */
    uint32_t GetDatabaseSizeInPages();

    /**
     * @brief Get the page number of the first freelist trunk page.
     * 
     * @return uint32_t 
     */
    uint32_t GetFirstFreelistPage();

    /**
     * @brief Get the total number of freelist pages.
     * 
     * @return uint32_t 
     */
    uint32_t GetNumberOfFreelistPages();

    /**
     * @brief Get the schema cookie object
     * 
     * @return uint32_t 
     */
    uint32_t GetSchemaCookie();

    /**
     * @brief Get the schema format number. Supported schema formats are 1, 2, 3, and 4.
     * 
     * @return uint32_t 
     */
    uint32_t GetSchemaFormatNumber();

    /**
     * @brief Get the default page cache size.
     * 
     * @return uint32_t 
     */
    uint32_t GetDefaultPageCacheSize();

    /**
     * @brief Get the page number of the largest root b-tree page when in auto-vacuum or 
     * incremental-vacuum modes, or zero otherwise.
     * 
     * @return uint32_t 
     */
    uint32_t GetRootBTreePage();

    /**
     * @brief Get the database text encoding. A value of 1 means UTF-8. A value of 2 means UTF-16le. A value of 3 means UTF-16be.
     * 
     * @return encoding 
     */
    encoding GetTextEncoding();

    /**
     * @brief Get the "user version" as read and set by the user_version pragma.
     * 
     * @return uint32_t 
     */
    uint32_t GetUserVersion();

    /**
     * @brief  True (non-zero) for incremental-vacuum mode. False (zero) otherwise
     * 
     * @return uint32_t 
     */
    uint32_t GetIncrementalVacuumMode();

    /**
     * @brief Get the "Application ID" set by PRAGMA application_id.
     * 
     * @return uint32_t 
     */
    uint32_t GetApplicationId();

    /**
     * @brief Get the version valid for number.
     * 
     * @return uint32_t 
     */
    uint32_t GetVersionValidFor();

    /**
     * @brief Get the sqlite version number. Convert to format x.y.z with following formula
     * x = numeric_version / 1000000;
     * y = (numeric_version % 1000000) / 1000;
     * z = numeric_version % 1000;
     * example: "3.30.1" = 3030001
     * @return uint32_t 
     */
    uint32_t GetSqliteVersionNumber();

private:
    void SetSQLiteVersion(uint32_t numeric_version);

private:
    sql_header header_ctx;
    std::string database_file;
    std::string sqlite_version;
};

} // namespace SQLite

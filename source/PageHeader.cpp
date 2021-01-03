#include <SQLite/PageHeader.hpp>
#include <Helpers.hpp>
#include <string.h>

namespace SQLite{

    PageHeader::PageHeader(){

    }
    
    PageHeader::~PageHeader(){

    }

    bool PageHeader::Deserialize(uint8_t* data) 
    {
        size_t copySize = sizeof(header_t);
        if (PageHeader::btree_page_t::LeafIndex == *data ||
            PageHeader::btree_page_t::LeafTable == *data)
        {
            copySize -= sizeof(header_ctx.right_child);
        }
        memcpy(&header_ctx, data, copySize);
        return true;
    }
    
    uint8_t PageHeader::GetFlags() 
    {
        return header_ctx.flags;
    }
    
    uint16_t PageHeader::GetOffsetToTheFirstFreeblock() 
    {
        return Helpers::ToBigEndian_U16(header_ctx.offset_to_the_first_freeblock);
    }
}//namespace SQLite
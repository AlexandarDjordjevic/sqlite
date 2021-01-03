#include <SQLite/PageHeader.hpp>
#include <Helpers.hpp>

namespace SQLite{

    PageHeader::PageHeader(){

    }
    
    PageHeader::~PageHeader(){

    }

    bool PageHeader::Deserialize(uint8_t* data) 
    {
        header_ctx.flags = *data;
        header_ctx.number_of_cells_on_page = Helpers::ToBigEndian_U16(*(uint16_t *) (data + 1));
        header_ctx.offset_to_the_first_freeblock = Helpers::ToBigEndian_U16(*(uint16_t *) (data + 3));
        header_ctx.first_byte_of_content_area = Helpers::ToBigEndian_U16(*(uint16_t *) (data + 5));
        header_ctx.number_of_fragmented_free_bytes = *(data + 7);
        if (PageHeader::btree_page_t::InteriorIndex == header_ctx.flags ||
            PageHeader::btree_page_t::InteriorTable == header_ctx.flags)
        {
            header_ctx.right_child = Helpers::ToBigEndian_U32(*(uint32_t *) (data + 8));
        }
        return true;
    }
}//namespace SQLite
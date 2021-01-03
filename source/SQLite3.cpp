/**
**      |----------------|
**      | file header    |   100 bytes.  Page 1 only.
**      |----------------|
**      | page header    |   8 bytes for leaves.  12 bytes for interior nodes
**      |----------------|
**      | cell pointer   |   |  2 bytes per cell.  Sorted order.
**      | array          |   |  Grows downward
**      |                |   v
**      |----------------|
**      | unallocated    |
**      | space          |
**      |----------------|   ^  Grows upwards
**      | cell content   |   |  Arbitrary order interspersed with freeblocks.
**      | area           |   |  and free space fragments.
**      |----------------|
**
*/
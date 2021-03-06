#define ZPL_IMPLEMENTATION
#include "zpl.h"

#define BUF_LEN 4096

///////////////////////////////////////////////////////////////////////////////////
//
// This demo requires you to have the following packages: "fortune" and "cowsay".
// You should find these in your distro repositories, or 
// at source ports sites.
//


int main(void)
{
    char buf[BUF_LEN] = {0};
    zpl_array_t(u8) arr = {0};
    zpl_array_init(arr, zpl_heap_allocator());
    
    zpl_system_command("fortune | cowsay", BUF_LEN, buf);
    zpl_system_command_str("fortune | cowsay", &arr);
    zpl_printf("Output:\n %s\n\n%s", buf, arr);
    return 0;
}

#if 0
    gcc -pthread -I../include -std=c99 -g "$0" -lm -ldl && ./a.out; exit
#endif

#define ZPL_IMPLEMENTATION
#include "zpl.h"

int main(void)
{
    zpl_list_t s, *head, *cursor;
    zpl_list_init(&s, "it is optional to call init: ");
    head = cursor = &s;

    // since we can construct an element implicitly this way
    // the second field gets overwritten once we add it to a list.
    zpl_list_t a = {"hello"};
    cursor = zpl_list_add(cursor, &a);

    zpl_list_t b = {"world"};
    cursor = zpl_list_add(cursor, &b);

    zpl_list_t c = {"!!! OK"};
    cursor = zpl_list_add(cursor, &c);

    for (zpl_list_t *l=head; l; l=l->next) {
        zpl_printf("%s ", cast(char *)l->ptr);
    }
    zpl_printf("\n");

    return 0;
}


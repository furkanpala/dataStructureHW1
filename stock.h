#include "shoe.h"

struct stock
{
    node *head;
    void create();
    void add_stock(int);
    void sell(int);
    void current_stock();
    void clear();
};
#include <iostream>
#include "stock.h"
using namespace std;

void stock::create()
{
    head = NULL;
    char *filename = "input.txt";
    FILE *filePtr;

    if (!(filePtr = fopen(filename, "r")))
    {
        cerr << "File could not be opened" << endl;
        exit(1);
    }

    fseek(filePtr, 0, SEEK_SET);

    while (!feof(filePtr))
    {
        int size;
        fscanf(filePtr, "%d", &size);
        if (size == 0)
        {
            current_stock();
        }
        else if (size > 0)
        {
            add_stock(size);
        }
        else if (size < 0)
        {
            sell(size);
        }
    }
}

void stock::add_stock(int size)
{
    node *temp1, *temp2, *newNode;
    if (head == NULL)
    {
        newNode = new node;
        newNode->size = size;
        newNode->quant = 1;
        newNode->next = NULL;
        head = newNode;
    }
    else
    {
        temp1 = head;
        bool isFound = false;
        while (temp1)
        {
            if (temp1->size == size)
            {
                isFound = true;
                temp1->quant++;
                break;
            }
            temp1 = temp1->next;
        }

        if (!isFound)
        {
            temp1 = head;
            temp2 = temp1;
            newNode = new node;
            newNode->size = size;
            newNode->quant = 1;
            newNode->next = NULL;

            if (size < head->size)
            {
                newNode->next = head;
                head = newNode;
            }
            else
            {

                while (temp1 && size > temp1->size)
                {
                    temp2 = temp1;
                    temp1 = temp1->next;
                }
                if (temp1)
                {
                    newNode->next = temp1;
                    temp2->next = newNode;
                }
                else
                {
                    temp2->next = newNode;
                }
            }
        }
    }
}

void stock::current_stock()
{
    node *traverse;
    traverse = head;
    while (traverse)
    {
        cout << traverse->size << ":" << traverse->quant << endl;
        traverse = traverse->next;
    }
}

void stock::sell(int size)
{
    node *traverse1, *traverse2;
    traverse1 = head;
    traverse2 = traverse1;
    int toBeSelled = abs(size);

    while (traverse2 && traverse2->size != toBeSelled)
    {
        traverse1 = traverse2;
        traverse2 = traverse2->next;
    }

    if (traverse2)
    {
        if (traverse2->quant == 1)
        {
            if (traverse2 == head)
            {
                head = traverse2->next;
            }
            else if (traverse2->next == NULL)
            {
                traverse1->next = NULL;
            }
            else
            {
                traverse1->next = traverse2->next;
            }
            delete traverse2;
        }
        else
        {
            traverse2->quant--;
        }
    }
    else
    {
        cout << "NO_STOCK" << endl;
    }
}

void stock::clear()
{
    node *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    stock s;
    s.create();
    s.clear();
    return 0;
}
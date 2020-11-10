#include "Bulk.h"

int main(int args, char* argv[])
{
    (void) args;
    Block b(static_cast<size_t>(stoi(argv[1])));
    b.exec();
}

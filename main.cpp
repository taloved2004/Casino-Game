#include <iostream>
#include <string.h>
#include "Casino.h"

int main()
{
    std::shared_ptr<Casino> my_casino(new Casino);
    my_casino->printOpenningAnouncment();
    int res = 1;
    while (res)
    {
        my_casino->printChoiseOptions();
        res = my_casino->handleChoise();
    }

    return 0;
}
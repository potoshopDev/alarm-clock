#include <stdio.h>

int main()
{
    auto  c = 0;

    auto printT = []() {
        printf("Enter the waiting time(m): ");
    };
    printT();

    while (scanf_s("%d", &c) == 0)
    {
        while (getchar() != '\n');
        printT();

    }




    printf("WAITING:  %d", c);
    return 0;
}
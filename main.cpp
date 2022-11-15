#include <stdio.h>

int main()
{
    auto  inWaitMinutes = 0;

    auto printT = []() {
        printf("Enter the waiting time(m): ");
    };
    printT();

    while (scanf_s("%d", &inWaitMinutes) == 0)
    {
        while (getchar() != '\n');
        printT();

    }




    printf("WAITING:  %d", inWaitMinutes);
    return 0;
}
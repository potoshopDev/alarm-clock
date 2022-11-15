
#include <stdio.h>



int main()
{
    auto c = 0;
    printf("Enter time");

    auto sc = scanf_s ("%d", &c);

    printf("c == %d", c);

  
    return 0;
}
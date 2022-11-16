#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <Windows.h>



int main()
{
    auto  inWaitMinutes = 0;

    

    auto printT = []() 
    {
        printf("Enter the waiting time(m): ");
    };
    auto printWaiting = [&inWaitMinutes]() 
    {
            printf("WAITING:  %d\n", inWaitMinutes);
    };



    printT();

    while (scanf_s("%d", &inWaitMinutes) == 0)
    {
        while (getchar() != '\n');
        printT();

    }

    printWaiting();

    auto StartTime = clock();
    auto CurrentTime = clock();

    auto CalculateTaiming = [&StartTime, &CurrentTime] () 
    {
        auto SecToMin = 60.0;
        return  static_cast<double>((CurrentTime - StartTime)) / CLOCKS_PER_SEC / SecToMin;

    };

    auto PrintTimer = [&inWaitMinutes](auto CurrTimeSec)
    {
        const auto CurrTimeMinf = static_cast<int> (CurrTimeSec / 60);
        const auto CurrTimeSecc = static_cast<int> (CurrTimeMinf * 60 - CurrTimeSec);
        const auto CurrTimeSecf = CurrTimeSecc < 0 ? CurrTimeSecc * -1 : CurrTimeSecc;

        auto LeftMin = inWaitMinutes;
        auto LeftSec = 0;

        LeftMin -= CurrTimeMinf;
        LeftSec -= CurrTimeSecf;

        if (LeftSec < 0)
        {
            LeftMin -= 1;
            LeftSec = 60 - CurrTimeSecf;
        }

        system("cls");

        printf_s("TIMER: %02d:%02d \\ %02d:00\n", LeftMin, LeftSec, inWaitMinutes);
    };
    

    while (CalculateTaiming() <= static_cast <double> (inWaitMinutes))
    {
        const auto CurrTime = CalculateTaiming();
        const auto CurrTimeSec = static_cast<int> (CurrTime * 60);
        
       

        static auto LastSec = 0;
        
        if (CurrTimeSec > LastSec)
        {
            PrintTimer(CurrTimeSec);
            LastSec = CurrTimeSec;
            
        }
        
        Sleep(100);

        //printf_s ("min: %f", CalculateTaiming());
        CurrentTime = clock();
    }

    const auto CurrTime = CalculateTaiming();
    const auto CurrTimeSec = static_cast<int> (CurrTime * 60);
    PrintTimer(CurrTimeSec);
 
    system ("call 1.mp3");
    system ("start https://www.youtube.com/watch?v=gkROXD2kzyM");
    system("pause");

    return 0;
}
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include <wchar.h>
#include <string>



int main()
{
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return GetLastError();
    }

    auto  inWaitMinutes = 0;
    const auto strClear = std::wstring(100, L' ');

    auto printT = []() 
    {
        wprintf(L"Enter the waiting time(m): ");
    };
    auto printWaiting = [&inWaitMinutes, &strClear]() 
    {
        wprintf(L"\x1b[1;1HWAITING:  %d%s\x1b[?25l", inWaitMinutes, strClear.c_str());
        wprintf(L"\n\x1b[1;31mPause: Click anywhere\nResume: <Enter>\r\x1b[0m");
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

        auto strCommand = std::wstring(L"\x1b[42m"); 
        if (LeftMin <= 0 && LeftSec <= 59 && LeftSec >10)
        {
            strCommand = std::wstring(L"\x1b[43m");
        }
        else if (LeftMin == 0 && LeftSec <= 10)
        {
            strCommand = std::wstring(L"\x1b[41m");
        }
        wprintf(L"\x1b[1;1HTIMER: %s%02d:%02d\x1b[0m\\ %02d:00\r",strCommand.c_str(), LeftMin, LeftSec, inWaitMinutes);
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
#ifndef HELPER_HPP
#define HELPER_HPP
#include <string>
#include <unistd.h>
#include <linux/limits.h>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <iostream>
    #include <termios.h>
#endif

struct helper
{
    static std::string get_exe_path()
    {
        char result[ PATH_MAX ];
        ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
        return std::string( result, (count > 0) ? count : 0 );
    }

    static void clear()
    {
#ifdef _WIN32 // Windows
        system("cls");
#else // Assuming POSIX compatible (Linux, macOS, etc.)
        system("clear");
#endif
    }

    static void pause()
    {
#ifdef _WIN32
        std::cout << "Press any key to continue...";
        _getch(); // Use _getch() on Windows
#else
        std::cout << "Press any key to continue...";
        std::cin.ignore();
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        int ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    }

    static std::string to_lowercase(const std::string& str)
    {
        std::string result;
        for (char c : str)
        {
            result += std::tolower(c);
        }
        return result;
    }
};



#endif //HELPER_HPP

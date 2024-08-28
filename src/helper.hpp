#ifndef HELPER_HPP
#define HELPER_HPP
#include <bemapiset.h>
#include <string>
#include <unistd.h>

#ifdef _WIN32
    #include <conio.h>
#include <windows.h>
#include <climits>
#else
    #include <iostream>
    #include <termios.h>
    #include <linux/limits.h>
#endif

struct helper
{
    static std::filesystem::path get_exe_path()
    {
#ifdef _WIN32
        wchar_t result[MAX_PATH] = {0};
        if (GetModuleFileNameW(nullptr, result, MAX_PATH) != 0)
        {
            std::filesystem::path path = result;
            return path;
        }
        else
        {
            // Handle error or return an empty string
            return {};
        }
#else
        char result[ PATH_MAX ];
        ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
        return std::string( result, (count > 0) ? count : 0 );
#endif
        
    }

    static std::string get_full_path()
    {
        std::filesystem::path exe_path = get_exe_path();
        return exe_path.parent_path().string();
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

     static std::string exec(const char* cmd)
    {
        std::array<char, 128> buffer{};
        std::string result;
        std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
        if (!pipe)
        {
            throw std::runtime_error("popen() failed!");
        }
        while (!feof(pipe.get()))
        {
            if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            {
                result += buffer.data();
            }
        }
        return result;
    }
};



#endif //HELPER_HPP

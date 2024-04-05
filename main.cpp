#include <iostream>
#include <nlohmann/json.hpp>

#include "src/game.hpp"
#include "src/helper.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"


int main()
{

    std::string exe_path = helper::get_exe_path();
    std::string path = exe_path.substr(0, exe_path.find_last_of('/')) + "/data/games.json";
    game::load(path);
    while (true)
    {
        helper::clear();
        std::cout << "\t\tThis is GameLogiX the best game tracker\n";
        std::cout << "1. Add game\n2. Remove game\n3. Show games\n4. search game by name\n5. edit game\n6. exit" << '\n';
        int choice;
        std::cin >> choice;
        switch (choice)
        {
            case 1:
            {
                std::cout << "Enter game name: ";
                std::cout << RED;
                std::string game_name;
                std::cin >> game_name;
                std::cout << RESET;

                std::cout << "Enter time played: ";
                std::cout << RED;
                float time_played;
                std::cin >> time_played;
                std::cout << RESET;

                std::cout << "Enter your score (1-10): ";
                std::cout << RED;
                int score;
                std::cin >> score;
                std::cout << RESET;

                std::cout << "completed: (y/n) ";
                std::cout << RED;
                char completed;
                std::cin >> completed;
                std::cout << RESET;

                game g;
                g.game_name = game_name;
                g.time_played = time_played;
                g.score = score;
                g.completed = completed == 'y';
                game::add_game(g);
                break;
            }

            case 2:
            {
                helper::clear();
                int i = 0;
                for (auto game: game::games)
                {
                    std::cout << i << ") " << game.to_string() << '\n';
                    i++;
                }
                std::cin.ignore();
                std::cout << "Enter the index of the game you want to remove: ";
                int index;
                std::cin >> index;
                game::remove_game(game::games[index].game_name);
                game::save(path);
                break;
            }
            case 3:
            {
                helper::clear();
                for (auto game: game::games)
                {
                    std::cout << game.to_string() << '\n';
                }
                std::cin.ignore();
                helper::pause();
                break;
            }

            case 4:
                break;
            case 5:
                break;

            case 6: return 0;

            default: break;
        }
    }
}

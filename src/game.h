#ifndef GAME_H
#define GAME_H
#include <string>
#include <nlohmann/json.hpp>


struct game
{
    static std::vector<game> games;



    std::string game_name;
    float time_played;
    int score;
    bool completed;

    nlohmann::json serialize() const;

    static game deserialize(const nlohmann::json& json_data);

    static void add_game(const game& g);

    static void remove_game(const std::string& game_name);

    static void print_games();

    static game* search_game(const std::string& game_name);

    std::string to_string() const;

    static void edit_game(int old_game_index, game new_game);


    static void save(const std::string& path);

    static void load(const std::string& path);
};



#endif //GAME_H

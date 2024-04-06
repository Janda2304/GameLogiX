#include "game.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "helper.hpp"

std::vector<game> game::games = {};

nlohmann::json game::serialize() const
{
    nlohmann::json json_data;
    json_data["game_name"] = game_name;
    json_data["time_played"] = time_played;
    json_data["score"] = score;
    json_data["completed"] = completed;
    return json_data;
}

game game::deserialize(const nlohmann::json &json_data)
{
    game g;
    g.game_name = json_data["game_name"];
    g.time_played = json_data["time_played"];
    g.score = json_data["score"];
    g.completed = json_data["completed"];
    return g;
}

void game::add_game(const game &g)
{
    games.push_back(g);
    std::string exe_path = helper::get_exe_path();
    std::string path = exe_path.substr(0, exe_path.find_last_of('/')) + "/data/games.json";
    save(path);
}

void game::remove_game(const std::string &game_name)
{
    std::erase_if(games, [&](const game& g) { return g.game_name == game_name; });
}

void game::print_games()
{
    int i = 0;
    for (const auto& g : games)
    {
        std::cout << i << ") " << g.to_string();
        i++;
    }
}

game * game::search_game(const std::string &game_name)
{
    for (auto& g : games)
    {
        if (g.game_name == game_name)
        {
            return &g;
        }
    }
    return nullptr;
}

std::string game::to_string() const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << time_played;
    std::string time_played_str = ss.str();

    return game_name + ", Time Played: " + time_played_str + " hours" + ", Score: " + std::to_string(score) + "/10" + ", " + (completed ? "Completed" : "Not Completed") + '\n';
}

void game::edit_game(int old_game_index, game new_game)
{
    games[old_game_index] = new_game;
}

void game::save(const std::string &path)
{
    nlohmann::json json_data;
    for (const auto& g : games)
    {
        json_data.push_back(g.serialize());
    }
    std::ofstream file(path);
    file << json_data.dump(4);
    file.close();
}

void game::load(const std::string &path)
{
    nlohmann::json json_data;
    std::ifstream file(path);
    file >> json_data;
    for (const auto& g : json_data)
    {
        games.push_back(deserialize(g));
    }
}

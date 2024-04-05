#ifndef GAME_H
#define GAME_H
#include <fstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "helper.hpp"


struct game
{
    static std::vector<game> games;



    std::string game_name;
    float time_played;
    int score;
    bool completed;

    nlohmann::json serialize() const
    {
        nlohmann::json json_data;
        json_data["game_name"] = game_name;
        json_data["time_played"] = time_played;
        json_data["score"] = score;
        json_data["completed"] = completed;
        return json_data;
    }

    static game deserialize(const nlohmann::json& json_data)
    {
        game g;
        g.game_name = json_data["game_name"];
        g.time_played = json_data["time_played"];
        g.score = json_data["score"];
        g.completed = json_data["completed"];
        return g;
    }

    static void add_game(const game& g)
    {
        games.push_back(g);
        std::string exe_path = helper::get_exe_path();
        std::string path = exe_path.substr(0, exe_path.find_last_of('/')) + "/data/games.json";
        save(path);
    }

    static void remove_game(const std::string& game_name)
    {
        std::erase_if(games, [&](const game& g) { return g.game_name == game_name; });
    }

    std::string to_string() const
    {
        return "Game: " + game_name + ", Time Played: " + std::to_string(time_played) + ", Score: " + std::to_string(score) + ", Completed: " + (completed ? "completed" : "not completed");
    }





    static void save(const std::string& path)
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

    static void load(const std::string& path)
    {
        nlohmann::json json_data;
        std::ifstream file(path);
        file >> json_data;
        for (const auto& g : json_data)
        {
            games.push_back(deserialize(g));
        }
    }


};



#endif //GAME_H

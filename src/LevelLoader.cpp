#include "LevelLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<LevelData> loadAllLvl(const std::string& path){
    std::vector<LevelData> levels;
    float aux;   //sf::Angle non supporta >> di sstream 
    bool first=true;
    LevelData defLvl;
    defLvl.offset=sf::degrees(0.0f);
    levels.push_back(defLvl);   //fallback al default in caso di problemi
    std::ifstream file(path);
    if(!file.is_open()){
        std::cerr<<"LevelLoader: impossibile aprire "<<path<<" fallback al livello di default"<<"\n";
        return levels;   //default level
    }
    std::string line;
    while(std::getline(file, line)){
        if(line.empty() || line[0]=='#') continue;
        std::istringstream ss(line);
        LevelData lvl;
        if(ss >> lvl.waitingD >> lvl.attachedD >> aux >> lvl.rotationSpeed >> lvl.changeRS >> lvl.changeRD){
            if(first){   //il file è stato aperto ed ha almeno un livello che segue il pattern corretto, non serve fallback al default -> lo togliamo
                levels.pop_back();
                first=false;
            }
            lvl.offset=sf::degrees(aux);
            levels.push_back(lvl);
        }
    }
    return levels;
}
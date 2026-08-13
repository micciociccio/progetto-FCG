#include "LevelLoader.hpp"
#include "GameUtils.hpp"
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
        if(ss >> lvl.waitingD >> lvl.attachedD >> aux >> lvl.rotationSpeed >> lvl.changeRS >> lvl.minRS >> lvl.maxRS >> lvl.changeRD){
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

std::size_t resumeLevel(const std::string& path){
    std::size_t level=1, tempLvl;   //default starting level
    std::ifstream file(path);
    if(!file.is_open()){
        std::cerr<<"LevelLoader: impossibile trovare l'ultimo livello dell'utente"<<"\n";
    }
    else{
        std::string line;   //il file può esistere, ma per qualche ragione essere vuoto, dobbiamo controllare
        while(std::getline(file, line)){
            if(line.empty() || line[0]=='#') continue;
            std::istringstream ss(line);
            if(ss >> tempLvl && tempLvl>0 && tempLvl<=utils::lastLvl) level=tempLvl;   //se c'è "spazzatura" oltre: commenti, linee vuote, spazi inline -> fallback al lvl di default 
        }
    }
    return level;
}

void writeLevel(const std::string& path, std::size_t level){
    if(level>utils::lastLvl) level=10;
    std::ofstream file(path);
    if(file.is_open()){   //se c'è stato un problema con i file .txt verrà semplicemente eseguito ogni volta il livello di default
        file << "# file per la persistenza dei livelli rispetto all'utente in locale\n"
            << "# si scrive su una riga un solo intero indicante il livello da caricare\n\n"
            << level;
    }
}
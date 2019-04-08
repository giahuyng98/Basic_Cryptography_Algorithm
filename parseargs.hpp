// A very simple parser command line
#include <iostream>
#include <string>
#include <map>

class ParseArgs{
private:
    std::map<std::string,std::string> table;

public:
    ParseArgs(int argc, char *argv[]){
        int i;
        for(i = 1; i + 1 < argc; i += 2){
            add(argv[i], argv[i + 1]);
        }
        if (i < argc) add(argv[i], "");
    }

    void add(std::string const &op, std::string const &des){
        table.insert({op, des});
    }

    std::string get(std::string const &op){
        static std::string empty("");
        auto iter = table.find(op);
        return (iter != table.end() ? iter->second : empty);
    }

    bool exist(std::string const &op){
        return table.find(op) != table.end();
    }

    void output(){
        for(auto &m : table){
            std::cerr << m.first << " " << m.second << "\n";
        }
    }
};

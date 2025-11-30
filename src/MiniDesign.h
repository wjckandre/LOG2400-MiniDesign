#ifndef MINIDESIGN_H
#define MINIDESIGN_H

#include "Orthese.h"

class MiniDesign {
private:
    std::vector<Orthese*> ortheses;
    std::vector<std::shared_ptr<PointComponent>> components;
    int nextNuageId = 0; // To track texture assignment

public:
    MiniDesign(std::string input);
    virtual ~MiniDesign();

    void run();
    void parseInput(std::string input);
    std::shared_ptr<PointComponent> findComponentById(int id);
    void removeComponentById(int id);
};

#endif

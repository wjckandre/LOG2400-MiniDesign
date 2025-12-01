#ifndef MINIDESIGN_H
#define MINIDESIGN_H

#include "Orthese.h"

#include <vector>
#include <memory>

struct Action {
    enum Type { Move, Delete } type;
    int id = -1;
    int oldX = 0, oldY = 0;
    int newX = 0, newY = 0;
    std::shared_ptr<PointComponent> comp;
    std::shared_ptr<class Nuage> parentNuage;
    size_t index = 0;
    bool wasTopLevel = false;
};

class MiniDesign {
private:
    std::vector<Orthese*> ortheses;
    std::vector<std::shared_ptr<PointComponent>> components;
    int nextNuageId = 0;
    std::vector<Action> undoStack;
    std::vector<Action> redoStack;

public:
    MiniDesign(std::string input);
    virtual ~MiniDesign();

    void run();
    void parseInput(std::string input);
    std::shared_ptr<PointComponent> findComponentById(int id);
    void removeComponentById(int id);
    void removeComponentPointer(const std::shared_ptr<PointComponent>& comp);
    std::pair<std::shared_ptr<Nuage>, size_t> findParentInfo(int id);
    void undo();
    void redo();
};

#endif

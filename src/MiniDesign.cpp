#include "MiniDesign.h"
#include "Point.h"
#include "Nuage.h"
#include "ListDisplayStrategy.h"
#include "TextureDisplayStrategy.h"
#include "IdDisplayStrategy.h"
#include "IdOrderStrategy.h"
#include "MinDistanceStrategy.h"
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <regex>

MiniDesign::MiniDesign(std::string input) {
    parseInput(input);
}

MiniDesign::~MiniDesign() {
    for (auto o : ortheses) delete o;
}

void MiniDesign::parseInput(std::string input) {
    std::regex regex(R"(\(\s*(\d+)\s*,\s*(\d+)\s*\))");
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), regex);
    auto words_end = std::sregex_iterator();

    int id = 0;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        int x = std::stoi(match[1].str());
        int y = std::stoi(match[2].str());
        auto point = std::make_shared<Point>(id++, x, y);
        components.push_back(point);
    }
}

std::shared_ptr<PointComponent> MiniDesign::findComponentById(int id) {
    
    for (auto c : components) {
        if (auto p = std::dynamic_pointer_cast<Point>(c)) {
            if (p->getId() == id) return p;
        } else if (auto n = std::dynamic_pointer_cast<Nuage>(c)) {
            auto children = n->getChildren();
            for (auto child : children) {
                 if (auto childP = std::dynamic_pointer_cast<Point>(child)) {
                     if (childP->getId() == id) return childP;
                 }
            }
        }
    }
    return nullptr;
}

void MiniDesign::removeComponentById(int id) {
    for (auto it = components.begin(); it != components.end(); ++it) {
        if (auto p = std::dynamic_pointer_cast<Point>(*it)) {
            if (p->getId() == id) {
                components.erase(it);
                return;
            }
        } else if (auto n = std::dynamic_pointer_cast<Nuage>(*it)) {
             auto children = n->getChildren();
             for (auto child : children) {
                 if (auto childP = std::dynamic_pointer_cast<Point>(child)) {
                     if (childP->getId() == id) {
                         n->remove(child);
                         return;
                     }
                 }
             }
        }
    }
}

void MiniDesign::run() {
    std::string command;
    while (std::cin >> command) {
        if (command == "q") {
            break;
        } else if (command == "a") {
            ListDisplayStrategy strategy;
            strategy.displayGrid(components);
        } else if (command == "o1") {
            TextureDisplayStrategy strategy;
            strategy.displayGrid(components);
        } else if (command == "o2") {
            IdDisplayStrategy strategy;
            strategy.displayGrid(components);
        } else if (command == "f") {
            std::string line;
            std::getline(std::cin >> std::ws, line);
            std::stringstream ss(line);
            int id;

            std::vector<int> ids;
            while (ss >> id) ids.push_back(id);

            // Remove duplicates while preserving order
            std::vector<int> uniqueIds;
            std::unordered_set<int> seen;
            for (int v : ids) {
                if (seen.insert(v).second) uniqueIds.push_back(v);
            }

            std::string texture = (nextNuageId == 0) ? "o" : "#";
            nextNuageId++;

            auto nuage = std::make_shared<Nuage>(texture, std::vector<Point>());
            std::vector<int> addedIds;
            for (int v : uniqueIds) {
                auto comp = findComponentById(v);
                if (!comp) {
                    std::cout << "Warning: ID " << v << " not found, ignored." << std::endl;
                    continue;
                }
                removeComponentById(v);
                nuage->add(comp);
                addedIds.push_back(v);
            }

            if (addedIds.empty()) {
                std::cout << "No valid IDs provided; nuage not created." << std::endl;
            } else {
                components.push_back(nuage);
                std::cout << "Nuage created with texture '" << texture << "' containing IDs:";
                for (int v : addedIds) std::cout << ' ' << v;
                std::cout << std::endl;
            }

        } else if (command == "d") {
            int id, x, y;
            std::cin >> id >> x >> y;
            auto comp = findComponentById(id);
            if (auto p = std::dynamic_pointer_cast<Point>(comp)) {
                // record move
                Action a;
                a.type = Action::Move;
                a.id = id;
                a.oldX = p->getX();
                a.oldY = p->getY();
                a.newX = x;
                a.newY = y;
                undoStack.push_back(a);
                redoStack.clear();
                p->move(x, y);
            }
        } else if (command == "s") {
            int id;
            std::cin >> id;
            auto comp = findComponentById(id);
            if (comp) {
                // find parent info
                auto parentInfo = findParentInfo(id);
                Action a;
                a.type = Action::Delete;
                a.id = id;
                a.comp = comp;
                if (parentInfo.first) {
                    a.wasTopLevel = false;
                    a.parentNuage = parentInfo.first;
                    a.index = parentInfo.second;
                } else {
                    a.wasTopLevel = true;
                    a.index = parentInfo.second;
                }
                undoStack.push_back(a);
                redoStack.clear();
                // remove
                removeComponentById(id);
            }
        } else if (command == "c1") {
            for (auto& c : components) {
                if (auto n = std::dynamic_pointer_cast<Nuage>(c)) {
                   IdOrderStrategy strategy;
                   auto children = n->getChildren();
                   auto ordered = strategy.orderPoints(children);

                   std::vector<Point> pts;
                   for(auto oc : ordered) {
                       if(auto p = std::dynamic_pointer_cast<Point>(oc)) pts.push_back(*p);
                   }
                   ortheses.push_back(new Orthese(n.get(), pts));
                }
            }
        } else if (command == "c2") {
            for (auto& c : components) {
                if (auto n = std::dynamic_pointer_cast<Nuage>(c)) {
                   MinDistanceStrategy strategy;
                   auto children = n->getChildren();
                   auto ordered = strategy.orderPoints(children);

                   std::vector<Point> pts;
                   for(auto oc : ordered) {
                       if(auto p = std::dynamic_pointer_cast<Point>(oc)) pts.push_back(*p);
                   }
                   ortheses.push_back(new Orthese(n.get(), pts));
                }
            }
        }
        else if (command == "u") {
            undo();
        } else if (command == "r") {
            redo();
        }
    }
}

void MiniDesign::removeComponentPointer(const std::shared_ptr<PointComponent>& comp) {
    // remove comp from top-level or from any nuage
    for (auto it = components.begin(); it != components.end(); ++it) {
        if (*it == comp) {
            components.erase(it);
            return;
        }
        if (auto n = std::dynamic_pointer_cast<Nuage>(*it)) {
            auto children = n->getChildren();
            for (auto child : children) {
                if (child == comp) {
                    n->remove(child);
                    return;
                }
            }
        }
    }
}

std::pair<std::shared_ptr<Nuage>, size_t> MiniDesign::findParentInfo(int id) {
    for (size_t i = 0; i < components.size(); ++i) {
        auto c = components[i];
        if (auto p = std::dynamic_pointer_cast<Point>(c)) {
            if (p->getId() == id) return {nullptr, i};
        } else if (auto n = std::dynamic_pointer_cast<Nuage>(c)) {
            auto children = n->getChildren();
            for (size_t j = 0; j < children.size(); ++j) {
                if (auto childP = std::dynamic_pointer_cast<Point>(children[j])) {
                    if (childP->getId() == id) return {n, j};
                } else if (auto childN = std::dynamic_pointer_cast<Nuage>(children[j])) {
                    // Search recursively within nested nuages
                    // Use getAllChildren to find points
                    auto all = childN->getAllChildren();
                    for (size_t k = 0; k < all.size(); ++k) {
                        if (auto ap = std::dynamic_pointer_cast<Point>(all[k])) {
                            if (ap->getId() == id) return {childN, k};
                        }
                    }
                }
            }
        }
    }
    return {nullptr, 0};
}

void MiniDesign::undo() {
    if (undoStack.empty()) {
        std::cout << "Nothing to undo." << std::endl;
        return;
    }
    Action a = undoStack.back();
    undoStack.pop_back();
    if (a.type == Action::Move) {
        auto comp = findComponentById(a.id);
        if (auto p = std::dynamic_pointer_cast<Point>(comp)) {
            p->move(a.oldX, a.oldY);
            redoStack.push_back(a);
            std::cout << "Undo: moved ID " << a.id << " back to (" << a.oldX << ", " << a.oldY << ")" << std::endl;
        }
    } else if (a.type == Action::Delete) {
        // reinsert
        if (a.wasTopLevel) {
            if (a.index <= components.size()) components.insert(components.begin() + a.index, a.comp);
            else components.push_back(a.comp);
        } else if (a.parentNuage) {
            a.parentNuage->addAt(a.comp, a.index);
        } else {
            components.push_back(a.comp);
        }
        redoStack.push_back(a);
        std::cout << "Undo: restored ID " << a.id << std::endl;
    }
}

void MiniDesign::redo() {
    if (redoStack.empty()) {
        std::cout << "Nothing to redo." << std::endl;
        return;
    }
    Action a = redoStack.back();
    redoStack.pop_back();
    if (a.type == Action::Move) {
        auto comp = findComponentById(a.id);
        if (auto p = std::dynamic_pointer_cast<Point>(comp)) {
            p->move(a.newX, a.newY);
            undoStack.push_back(a);
            std::cout << "Redo: moved ID " << a.id << " to (" << a.newX << ", " << a.newY << ")" << std::endl;
        }
    } else if (a.type == Action::Delete) {
        // perform delete again
        // locate by id and remove pointer
        auto comp = findComponentById(a.id);
        if (comp) {
            removeComponentPointer(comp);
            undoStack.push_back(a);
            std::cout << "Redo: deleted ID " << a.id << std::endl;
        }
    }
}

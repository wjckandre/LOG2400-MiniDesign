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
            std::getline(std::cin, line);
            std::stringstream ss(line);
            int id;
            std::string texture = (nextNuageId == 0) ? "o" : "#";
            nextNuageId++;

            auto nuage = std::make_shared<Nuage>(texture, std::vector<Point>());

            while (ss >> id) {
                auto comp = findComponentById(id);
                if (comp) {
                    removeComponentById(id);
                    nuage->add(comp);
                }
            }
            components.push_back(nuage);

        } else if (command == "d") {
            int id, x, y;
            std::cin >> id >> x >> y;
            auto comp = findComponentById(id);
            if (auto p = std::dynamic_pointer_cast<Point>(comp)) {
                p->move(x, y);
            }
        } else if (command == "s") {
            int id;
            std::cin >> id;
            removeComponentById(id);
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
    }
}

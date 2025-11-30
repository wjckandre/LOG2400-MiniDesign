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
    // Input format: "(5,0) (14,16) ..."
    std::regex regex(R"(\(\s*(\d+)\s*,\s*(\d+)\s*\))");
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), regex);
    auto words_end = std::sregex_iterator();

    int id = 0;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        // match[0] is the whole string "(5,0)"
        // match[1] is the first capture group (\d+) for x
        // match[2] is the second capture group (\d+) for y
        int x = std::stoi(match[1].str());
        int y = std::stoi(match[2].str());
        auto point = std::make_shared<Point>(id++, x, y);
        components.push_back(point);
    }
}

std::shared_ptr<PointComponent> MiniDesign::findComponentById(int id) {
    // Search recursively? No, based on context `f`, `d`, `s` operate on IDs.
    // If a point is inside a Nuage, can we find it?
    // "f: ... fusionner des points..." (points separation separated by space)
    // We need to look into all components.

    for (auto c : components) {
        if (auto p = std::dynamic_pointer_cast<Point>(c)) {
            if (p->getId() == id) return p;
        } else if (auto n = std::dynamic_pointer_cast<Nuage>(c)) {
            // Check children
            std::vector<Point> points;
            n->getPoints(points); // This returns copies... wait.
            // Nuage::getPoints returns copies. We need access to real objects.
            // Nuage::getChildren returns shared_ptr.
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
    // Remove from top level or from a cloud
    for (auto it = components.begin(); it != components.end(); ++it) {
        if (auto p = std::dynamic_pointer_cast<Point>(*it)) {
            if (p->getId() == id) {
                components.erase(it);
                return;
            }
        } else if (auto n = std::dynamic_pointer_cast<Nuage>(*it)) {
            // Check children
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
            // Read line or next ints? "il faut entrer les points séparés d’un espace"
            // Usually in these labs, it might be on same line or next.
            // Let's assume remaining of line.
            std::string line;
            std::getline(std::cin, line);
            std::stringstream ss(line);
            int id;

            std::string texture = (nextNuageId == 0) ? "o" : "#";
            nextNuageId++;
            // Note: If more than 2 clouds, what texture? Assume repeating or something?
            // "Le premier nuage a la texture “o” et le deuxième a la texture “#”."
            // We'll stick to that.

            auto nuage = std::make_shared<Nuage>();
            // Hacky way to set texture since setter isn't in interface but I can rebuild it
            // OR I assume I can create it empty and populate.
            // My Nuage constructor `Nuage(string, vector)` exists.
            // But I want to add existing pointers.
            // I'll create a new Nuage with texture and add children manually.

            // Wait, Nuage texture is private and no setter.
            // I should add a setter or use constructor with empty vector.
            // I'll add a constructor `Nuage(string)` or just pass empty vector.
            std::vector<Point> empty;
            nuage = std::make_shared<Nuage>(texture, empty);

            while (ss >> id) {
                auto comp = findComponentById(id);
                if (comp) {
                    // Remove from old location
                    removeComponentById(id);
                    // Add to new Nuage
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
            // Apply IdOrderStrategy to all Nuages
            for (auto& c : components) {
                if (auto n = std::dynamic_pointer_cast<Nuage>(c)) {
                   IdOrderStrategy strategy;
                   auto children = n->getChildren();
                   auto ordered = strategy.orderPoints(children);
                   // Construct Orthese? The requirement says "c1 relie les points..."
                   // Usually implies printing the connection.
                   // Or stores it.
                   // For now, let's print "Nuage texture: id1 id2 ..." to show it works?
                   // Or create Orthese.

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

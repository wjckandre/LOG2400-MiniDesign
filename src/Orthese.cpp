#include "Orthese.h"

Orthese::Orthese() : pointComponent(nullptr) {

}

Orthese::Orthese(Nuage* nuage, std::vector<Point> orderedPoints) : orderedPoints(orderedPoints), pointComponent(nuage) {

}

Orthese::~Orthese() {

}

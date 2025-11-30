#ifndef POINTCOMPONENT_H
#define POINTCOMPONENT_H

#include <memory>

class DisplayStrategy;
class ConnectionStrategy;

class PointComponent {
public:
    std::shared_ptr<DisplayStrategy> m_DisplayStrategy;
    std::shared_ptr<ConnectionStrategy> m_ConnectionStrategy;

    PointComponent();
    virtual ~PointComponent();
};

#endif

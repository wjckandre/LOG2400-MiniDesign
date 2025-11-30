#ifndef MINIDESIGN_H
#define MINIDESIGN_H

#include "Orthese.h"

class MiniDesign {
private:
    Orthese* orthese;
    Orthese* m_Orthese; // Duplicate? Java has "private Orhtèse orthèse;" and "public Orthèse m_Orthèse;"

public:
    MiniDesign();
    virtual ~MiniDesign();

    void run();
};

#endif

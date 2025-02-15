#pragma once
#include <iostream>
#include "SupportADessin.h"

class Dessinable {

    public:

        virtual void dessine_sur(SupportADessin& support) const = 0;
};


#pragma once
#ifndef LETADLO_H
#define LETADLO_H

#include "Path.h"
#include "TerrainMap.h"
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <set>

class Letadlo : public Path
{
public:
    Letadlo(TerrainMap& m, std::string name_in, Point start_in, Point finish_in);
    ~Letadlo();
    virtual bool find();
    double calculateCost(const Point& from, const Point& to); // Corrected

private:

};

#endif

// Copyright (c) 2005 - 2020 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <cmath>
#include <vector>

template<typename T>
class GammaTable
{
private:
    std::vector<T> table;
    float gamma;

public:
    GammaTable(unsigned s, float g = 1) : gamma(-1)
    {
        table.resize(s > 2 ? s : 2);
        set_gamma(g);
    }

    const float& get_gamma() { return gamma; }

    void set_gamma(float g)
    {
        if(g < 0.001f)
            g = 0.001f;
        if(g == gamma) //-V550
            return;
        gamma = g;

        float sizef = table.size() - 1.f;
        for(unsigned i = 0; i < table.size(); i++)
            table[i] = (T)(std::pow(i / sizef, 1 / gamma) * sizef);
    }

    const T& operator[](const T& i) const { return table[i]; }
};

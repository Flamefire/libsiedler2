// Copyright (c) 2005 - 2015 Settlers Freaks (sf-team at siedler25.org)
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
#ifndef ARCHIVITEM_MAP_H_INCLUDED
#define ARCHIVITEM_MAP_H_INCLUDED

#pragma once

#include "ArchivItem.h"
#include "ArchivInfo.h"
#include <iosfwd>

namespace libsiedler2
{
    /// Klasse für eine Mapfile.
    class ArchivItem_Map : public ArchivItem, public ArchivInfo
    {
        public:
            /// Konstruktor von @p ArchivItem_Map.
            ArchivItem_Map(void);
            /// Kopierkonstruktor von @p ArchivItem_Map.
            ArchivItem_Map(const ArchivItem_Map& item);
            /// Destruktor von @p ArchivItem_Map.
            ~ArchivItem_Map(void) override;

            /// lädt die Mapdaten aus einer Datei.
            virtual int load(std::istream& file, bool only_header);
            /// schreibt die Mapdaten in eine Datei.
            virtual int write(std::ostream& file) const;
    };
}

#endif // !ARCHIVITEM_MAP_H_INCLUDED

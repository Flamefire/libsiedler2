// Copyright (c) 2005 - 2017 Settlers Freaks (sf-team at siedler25.org)
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

#include "libSiedler2Defines.h" // IWYU pragma: keep
#include "ArchivItem_Map.h"
#include "ArchivInfo.h"
#include "prototypen.h"
#include "ErrorCodes.h"
#include <boost/filesystem/fstream.hpp>

/**
 *  schreibt ein ArchivInfo in eine SWD/WSD-File.
 *
 *  @param[in] file    Dateiname der SWD/WSD-File
 *  @param[in] items   ArchivInfo-Struktur, von welcher gelesen wird
 *
 *  @return Null bei Erfolg, ein Wert ungleich Null bei Fehler
 */
int libsiedler2::loader::WriteMAP(const std::string& file, const ArchivInfo& items)
{
    if(file.empty())
        return ErrorCode::INVALID_BUFFER;

    const ArchivItem_Map* item = dynamic_cast<const ArchivItem_Map*>(items[0]);
    if(!item)
        return ErrorCode::WRONG_ARCHIV;

    // Datei zum lesen öffnen
    bfs::ofstream fs(file, std::ios_base::binary);

    // hat das geklappt?
    if(!fs)
        return ErrorCode::FILE_NOT_ACCESSIBLE;

    return item->write(fs);
}

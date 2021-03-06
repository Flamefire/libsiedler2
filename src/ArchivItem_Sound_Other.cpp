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

#include "ArchivItem_Sound_Other.h"
#include "ErrorCodes.h"
#include "libendian/EndianIStreamAdapter.h"
#include "libendian/EndianOStreamAdapter.h"
#include <iostream>

namespace libsiedler2 {
/** @class baseArchivItem_Sound_Other
 *
 *  Klasse für Other-Sounds.
 */

ArchivItem_Sound_Other::ArchivItem_Sound_Other(SoundType sndType) : ArchivItem_Sound(sndType) {}

/**
 *  lädt die Daten aus einer Datei.
 *
 *  @param[in] file    Dateihandle der Datei
 *  @param[in] length  Länge der Daten
 *
 *  @return liefert Null bei Erfolg, ungleich Null bei Fehler
 */
int ArchivItem_Sound_Other::load(std::istream& file, uint32_t length)
{
    if(!file)
        return ErrorCode::FILE_NOT_ACCESSIBLE;
    if(length == 0)
        return ErrorCode::WRONG_HEADER;

    data.resize(length);
    libendian::EndianIStreamAdapter<false, std::istream&> fs(file);

    fs >> data;

    return (!file) ? ErrorCode::UNEXPECTED_EOF : ErrorCode::NONE;
}

/**
 *  schreibt die Daten in eine Datei.
 *
 *  @param[in] file        Dateihandle der Datei
 *
 *  @return liefert Null bei Erfolg, ungleich Null bei Fehler
 */
int ArchivItem_Sound_Other::write(std::ostream& file) const
{
    if(!file)
        return ErrorCode::FILE_NOT_ACCESSIBLE;

    libendian::EndianOStreamAdapter<false, std::ostream&> fs(file);
    fs << data;

    return (!file) ? ErrorCode::UNEXPECTED_EOF : ErrorCode::NONE;
}

/**
 *  räumt den Soundspeicher auf.
 */
void ArchivItem_Sound_Other::clear()
{
    data.resize(0);
}
} // namespace libsiedler2

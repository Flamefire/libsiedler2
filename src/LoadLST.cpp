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

#include "Archiv.h"
#include "ArchivItem.h"
#include "ErrorCodes.h"
#include "OpenMemoryStream.h"
#include "prototypen.h"
#include "libendian/EndianIStreamAdapter.h"

/**
 *  lädt eine LST-File in ein Archiv.
 *
 *  @param[in]  filepath    Dateiname der LST-File
 *  @param[in]  palette Grundpalette der LST-File
 *  @param[out] items   Archiv-Struktur, welche gefüllt wird
 *
 *  @return Null bei Erfolg, ein Wert ungleich Null bei Fehler
 */
int libsiedler2::loader::LoadLST(const boost::filesystem::path& filepath, Archiv& items,
                                 const ArchivItem_Palette* palette)
{
    MMStream mmapStream;
    if(int ec = openMemoryStream(filepath, mmapStream))
        return ec;

    libendian::EndianIStreamAdapter<false, MMStream&> lst(mmapStream);

    uint16_t header;
    uint32_t count;

    // Header einlesen
    lst >> header;

    // ist es eine GER/ENG-File? (Header 0xE7FD)
    if(header == 0xFDE7)
        return LoadTXT(filepath, items, true);

    // ist es eine LST-File? (Header 0x204E)
    if(header != 0x4E20)
        return ErrorCode::WRONG_HEADER;

    // Anzahl einlesen
    lst >> count;

    if(!lst)
        return ErrorCode::WRONG_FORMAT;

    items.clear();

    // items einlesen
    for(uint32_t i = 0; i < count; ++i)
    {
        int16_t used;
        int16_t bobtype_s;

        // use-Flag einlesen
        if(!(lst >> used))
            return ErrorCode::UNEXPECTED_EOF;

        // ist das Item benutzt?
        if(used != 1)
        {
            items.push(nullptr);
            continue;
        }

        // bobtype des Items einlesen
        lst >> bobtype_s;
        auto bobtype = static_cast<BobType>(bobtype_s);

        // Daten von Item auswerten
        std::unique_ptr<ArchivItem> item;
        if(int ec = LoadType(bobtype, lst.getStream(), item, palette))
            return ec;
        items.push(std::move(item));
    }

    return ErrorCode::NONE;
}

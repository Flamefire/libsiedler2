// $Id: ArchivItem_Sound_Other.cpp 9359 2014-04-25 15:37:22Z FloSoft $
//
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

///////////////////////////////////////////////////////////////////////////////
// Header
#include "main.h"
#include "ArchivItem_Sound_Other.h"

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#if defined _WIN32 && defined _DEBUG && defined _MSC_VER
#define new new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
/** @class libsiedler2::baseArchivItem_Sound_Other
 *
 *  Klasse für Other-Sounds.
 *
 *  @author FloSoft
 */

///////////////////////////////////////////////////////////////////////////////
/**
 *  Konstruktor von @p baseArchivItem_Sound_Other.
 *
 *  @author FloSoft
 */
libsiedler2::baseArchivItem_Sound_Other::baseArchivItem_Sound_Other(void) : baseArchivItem_Sound()
{
    setType(SOUNDTYPE_OTHER);
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  Destruktor von @p baseArchivItem_Sound_Other.
 *
 *  @author FloSoft
 */
libsiedler2::baseArchivItem_Sound_Other::~baseArchivItem_Sound_Other(void)
{}

///////////////////////////////////////////////////////////////////////////////
/**
 *  lädt die Daten aus einer Datei.
 *
 *  @param[in] file    Dateihandle der Datei
 *  @param[in] length  Länge der Daten
 *
 *  @return liefert Null bei Erfolg, ungleich Null bei Fehler
 *
 *  @author FloSoft
 */
int libsiedler2::baseArchivItem_Sound_Other::load(FILE* file, unsigned int length)
{
    if(file == NULL || length == 0)
        return 1;

    data.resize(length);

    if(libendian::le_read_uc(&data.front(), length, file) != (int)length)
        return 2;

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  schreibt die Daten in eine Datei.
 *
 *  @param[in] file        Dateihandle der Datei
 *
 *  @return liefert Null bei Erfolg, ungleich Null bei Fehler
 *
 *  @author FloSoft
 */
int libsiedler2::baseArchivItem_Sound_Other::write(FILE* file) const
{
    if(file == NULL)
        return 1;

    if(libendian::le_write_ui(data.size(), file) != 0)
        return 2;

    if(libendian::le_write_uc(&data.front(), data.size(), file) != (int)data.size())
        return 3;

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  räumt den Soundspeicher auf.
 *
 *  @author FloSoft
 */
void libsiedler2::baseArchivItem_Sound_Other::clear(void)
{
    data.resize(0);
}

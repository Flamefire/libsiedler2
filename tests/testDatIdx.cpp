// Copyright (c) 2017 - 2020 Settlers Freaks (sf-team at siedler25.org)
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

#include "LoadPalette.h"
#include "test/config.h"
#include "libsiedler2/Archiv.h"
#include "libsiedler2/ArchivItem_BitmapBase.h"
#include "libsiedler2/ArchivItem_Font.h"
#include "libsiedler2/ArchivItem_Palette.h"
#include "libsiedler2/libsiedler2.h"
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(DatIdxFiles, LoadPalette)

BOOST_AUTO_TEST_CASE(LoadDatIdxFile)
{
    if(!libsiedler2::test::hasS2Data)
        return;
    // Both should work
    for(const auto* const file : {"EDITRES.IDX", "EDITRES.DAT"})
    {
        const boost::filesystem::path inPath = libsiedler2::test::s2Path / "DATA" / file;
        libsiedler2::Archiv archiv;
        BOOST_REQUIRE_EQUAL(libsiedler2::Load(inPath, archiv, palette), 0);
        BOOST_REQUIRE_EQUAL(archiv.size(), 57u);
        BOOST_REQUIRE(dynamic_cast<libsiedler2::ArchivItem_Font*>(archiv[0]));
        BOOST_REQUIRE(dynamic_cast<libsiedler2::ArchivItem_Palette*>(archiv[1]));
        BOOST_REQUIRE(dynamic_cast<libsiedler2::ArchivItem_Font*>(archiv[2]));
        BOOST_REQUIRE(dynamic_cast<libsiedler2::ArchivItem_Font*>(archiv[3]));
        for(unsigned i = 4; i < archiv.size(); i++)
        {
            const auto* bmp = dynamic_cast<const libsiedler2::ArchivItem_BitmapBase*>(archiv[i]);
            BOOST_REQUIRE(bmp);
            BOOST_REQUIRE_GT(bmp->getWidth(), 0u);
            BOOST_REQUIRE_GT(bmp->getHeight(), 0u);
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()

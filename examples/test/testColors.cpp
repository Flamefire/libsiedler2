// Copyright (c) 2017 - 2017 Settlers Freaks (sf-team at siedler25.org)
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

#include "ColorOutput.h"
#include "libsiedler2/src/ColorRGB.h"
#include "libsiedler2/src/ColorRGBA.h"
#include <boost/test/unit_test.hpp>
#include <boost/array.hpp>
#include <boost/static_assert.hpp>
#include <boost/endian/conversion.hpp>
#include <algorithm>

using libsiedler2::ColorRGBA;
using libsiedler2::ColorRGB;

BOOST_AUTO_TEST_CASE(ColorRGBCtor)
{
    // Default should be all zeros
    ColorRGB clrDef;
    BOOST_REQUIRE_EQUAL(clrDef.getRed(), 0u);
    BOOST_REQUIRE_EQUAL(clrDef.getGreen(), 0u);
    BOOST_REQUIRE_EQUAL(clrDef.getBlue(), 0u);
    // Check setting of elements
    ColorRGB clr(1, 2, 3);
    BOOST_REQUIRE_EQUAL(clr.getRed(), 1u);
    BOOST_REQUIRE_EQUAL(clr.getGreen(), 2u);
    BOOST_REQUIRE_EQUAL(clr.getBlue(), 3u);
}

BOOST_AUTO_TEST_CASE(ColorARGBCtor)
{
    // Default should be all zeros
    ColorRGBA clrDef;
    BOOST_REQUIRE_EQUAL(clrDef.getRed(), 0u);
    BOOST_REQUIRE_EQUAL(clrDef.getGreen(), 0u);
    BOOST_REQUIRE_EQUAL(clrDef.getBlue(), 0u);
    BOOST_REQUIRE_EQUAL(clrDef.getAlpha(), 0u);
    // Default for alpha is 0xFF
    ColorRGBA clr2(1, 2, 3);
    BOOST_REQUIRE_EQUAL(clr2.getRed(), 1u);
    BOOST_REQUIRE_EQUAL(clr2.getGreen(), 2u);
    BOOST_REQUIRE_EQUAL(clr2.getBlue(), 3u);
    BOOST_REQUIRE_EQUAL(clr2.getAlpha(), 0xFF);
    // Check setting of elements
    ColorRGBA clr(1, 2, 3, 4);
    BOOST_REQUIRE_EQUAL(clr.getRed(), 1u);
    BOOST_REQUIRE_EQUAL(clr.getGreen(), 2u);
    BOOST_REQUIRE_EQUAL(clr.getBlue(), 3u);
    BOOST_REQUIRE_EQUAL(clr.getAlpha(), 4u);
    // Construct from RGB
    ColorRGBA clrRGB(ColorRGB(5, 6, 7));
    BOOST_REQUIRE_EQUAL(clrRGB.getRed(), 5u);
    BOOST_REQUIRE_EQUAL(clrRGB.getGreen(), 6u);
    BOOST_REQUIRE_EQUAL(clrRGB.getBlue(), 7u);
    BOOST_REQUIRE_EQUAL(clrRGB.getAlpha(), 0xFF);
    // Set components
    clr.setRed(10);
    BOOST_REQUIRE_EQUAL(clr, ColorRGBA(10, 2, 3, 4));
    clr.setGreen(20);
    BOOST_REQUIRE_EQUAL(clr, ColorRGBA(10, 20, 3, 4));
    clr.setBlue(30);
    BOOST_REQUIRE_EQUAL(clr, ColorRGBA(10, 20, 30, 4));
    clr.setAlpha(40);
    BOOST_REQUIRE_EQUAL(clr, ColorRGBA(10, 20, 30, 40));
}

BOOST_AUTO_TEST_CASE(ColorRGBBuffer)
{
    // Read from buffer
    ColorRGB checkClr(1, 42, 24);
    boost::array<uint8_t, 3> buf;
    buf[0] = checkClr.getBlue();
    buf[1] = checkClr.getGreen();
    buf[2] = checkClr.getRed();
    BOOST_REQUIRE_EQUAL(ColorRGB::fromBGR(&buf[0]), checkClr);
    // Write to buffer. Check by reading from it which is tested
    ColorRGB checkClr2(5, 6, 23);
    checkClr2.toBGR(&buf[0]);
    BOOST_REQUIRE_EQUAL(ColorRGB::fromBGR(&buf[0]), checkClr2);

    boost::array<uint8_t, 6> buf2;
    buf2[0] = checkClr.getRed();
    buf2[1] = checkClr.getGreen();
    buf2[2] = checkClr.getBlue();
    buf2[3] = checkClr2.getRed();
    buf2[4] = checkClr2.getGreen();
    buf2[5] = checkClr2.getBlue();
    BOOST_STATIC_ASSERT_MSG(sizeof(ColorRGB) == 3u, "Padding added to ColorRGB. Cannot read it as buffer");
    // Interpreting a buffer of RGBRGB values as ColorRGB should be possible
    const ColorRGB* clrs = reinterpret_cast<const ColorRGB*>(&buf2[0]);
    BOOST_REQUIRE_EQUAL(clrs[0], checkClr);
    BOOST_REQUIRE_EQUAL(clrs[1], checkClr2);
}

BOOST_AUTO_TEST_CASE(ColorARGBBuffer)
{
    // Read from buffer
    ColorRGBA checkClr(1, 42, 24, 99);
    boost::array<uint8_t, 4> buf, buf2;
    // RGBA
    buf[0] = checkClr.getRed();
    buf[1] = checkClr.getGreen();
    buf[2] = checkClr.getBlue();
    buf[3] = checkClr.getAlpha();
    // ABGR
    std::reverse_copy(buf.begin(), buf.end(), buf2.begin());
    BOOST_REQUIRE_EQUAL(ColorRGBA::fromRGBA(&buf[0]), checkClr);
    BOOST_REQUIRE_EQUAL(ColorRGBA::fromABGR(&buf2[0]), checkClr);
    // Write to buffer. Check by reading from it which is tested
    ColorRGBA checkClr2(5, 6, 23, 34);
    checkClr2.toRGBA(&buf[0]);
    BOOST_REQUIRE_EQUAL(ColorRGBA::fromRGBA(&buf[0]), checkClr2);
    checkClr2.toABGR(&buf[0]);
    BOOST_REQUIRE_EQUAL(ColorRGBA::fromABGR(&buf[0]), checkClr2);

    boost::array<uint8_t, 8> bufABGR;
    bufABGR[0] = checkClr.getAlpha();
    bufABGR[1] = checkClr.getBlue();
    bufABGR[2] = checkClr.getGreen();
    bufABGR[3] = checkClr.getRed();
    bufABGR[4] = checkClr2.getAlpha();
    bufABGR[5] = checkClr2.getBlue();
    bufABGR[6] = checkClr2.getGreen();
    bufABGR[7] = checkClr2.getRed();
    BOOST_STATIC_ASSERT_MSG(sizeof(ColorRGBA) == 4u, "Padding added to ColorARGB. Cannot read it as buffer");
#if BOOST_BIG_ENDIAN
    // On big endian systems this is a word RGBA buffer. Swap it to BGRA
    boost::endian::endian_reverse_inplace(*reinterpret_cast<uint32_t*>(&bufABGR[0]));
    boost::endian::endian_reverse_inplace(*reinterpret_cast<uint32_t*>(&bufABGR[4]));
#endif
    // Interpreting a buffer of ABGRABGR values as ColorARGB should be possible
    const ColorRGBA* clrs = reinterpret_cast<const ColorRGBA*>(&bufABGR[0]);
    BOOST_REQUIRE_EQUAL(clrs[0], checkClr);
    BOOST_REQUIRE_EQUAL(clrs[1], checkClr2);
}
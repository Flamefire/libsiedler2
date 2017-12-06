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

#ifndef ARCHIVITEM_BITMAPBASE_H_INCLUDED
#define ARCHIVITEM_BITMAPBASE_H_INCLUDED

#include "ArchivItem.h"
#include "enumTypes.h"
#include <iosfwd>
#include <stdint.h>
#include <vector>

namespace libsiedler2 {

class ArchivItem_Palette;
struct ColorARGB;

/**
 * Base class for all bitmaps (regular and player bitmaps)
 */
class ArchivItem_BitmapBase : public ArchivItem
{
public:
    ArchivItem_BitmapBase();
    ArchivItem_BitmapBase(const ArchivItem_BitmapBase&);
    ~ArchivItem_BitmapBase() override;

    /// setzt einen Pixel auf einen bestimmten Wert.
    void setPixel(uint16_t x, uint16_t y, uint8_t colorIdx);
    void setPixel(uint16_t x, uint16_t y, const ColorARGB clr);

    /// Return the color index at the given position using the current palette for ARGB conversion
    uint8_t getPixelClrIdx(uint16_t x, uint16_t y) const;
    /// Return the color index at the given position using the given palette for ARGB conversion. Otherwise not required
    uint8_t getPixelClrIdx(uint16_t x, uint16_t y, const ArchivItem_Palette* palette) const;
    /// Return the color at the given position using the current palette for paletted bmps
    ColorARGB getPixel(uint16_t x, uint16_t y) const;

    /// lädt die Bilddaten aus einer Datei.
    virtual int load(std::istream& file, const ArchivItem_Palette* palette) = 0;

    /// schreibt die Bilddaten in eine Datei.
    virtual int write(std::ostream& file, const ArchivItem_Palette* palette) const = 0;

    /// liefert den Textur-Datenblock.
    const std::vector<uint8_t>& getPixelData() const { return pxlData_; }

    /// liefert den X-Nullpunkt.
    int16_t getNx() const;

    /// liefert den Y-Nullpunkt.
    int16_t getNy() const;

    /// liefert die Breite des Bildes.
    uint16_t getWidth() const { return width_; }

    /// liefert die Höhe des Bildes.
    uint16_t getHeight() const { return height_; }

    /// setzt den X-Nullpunkt.
    void setNx(int16_t nx);

    /// setzt den Y-Nullpunkt.
    void setNy(int16_t ny);

    /// Allocates memory for the given size and format and initializes it to transparent
    /// using the currently set palette
    virtual void init(int16_t width, int16_t height, TextureFormat format);
    /// Allocates memory for the given size and format and initializes it to transparent
    /// newPal will replace the existing palette by copy or remove it if it is NULL
    /// newPal is required for paletted format
    void init(int16_t width, int16_t height, TextureFormat format, const ArchivItem_Palette* newPal);

    /// räumt den Bildspeicher auf.
    virtual void clear();

    /// Return the currently used palette
    const ArchivItem_Palette* getPalette() const { return palette_; }
    /// Check if the given palette can be used for this bitmap. That is all ARGB colors are in the palette
    bool checkPalette(const ArchivItem_Palette& palette) const;
    /// Set the palette passing ownership
    void setPalette(ArchivItem_Palette* palette);
    /// Set the palette NOT passing ownership
    void setPaletteCopy(const ArchivItem_Palette& palette);
    /// Remove the currently used palette
    void removePalette();

    TextureFormat getFormat() const { return format_; }
    /// Convert the bitmap to the new format using the internal palette
    virtual int convertFormat(TextureFormat newFormat);

    virtual void getVisibleArea(int& vx, int& vy, unsigned& vw, unsigned& vh);

    /// Return the bytes per pixel for a given format
    static uint32_t getBBP(TextureFormat format);
    uint32_t getBBP() const { return getBBP(getFormat()); }

    /// Adjusts the global format incooporating the "ORIGINAL" format
    static TextureFormat getWantedFormat(TextureFormat origFormat);

protected:
    /// Return a pointer to the start of the given pixel
    uint8_t* getPixelPtr(uint16_t x, uint16_t y);
    const uint8_t* getPixelPtr(uint16_t x, uint16_t y) const;
    /// Return the pixel at the given position assuming the bitmap is paletted
    uint8_t getPalettedPixel(uint16_t x, uint16_t y) const;
    /// Return the pixel at the given position assuming the bitmap is ARGB
    ColorARGB getARGBPixel(uint16_t x, uint16_t y) const;

    std::vector<uint8_t>& getPixelData() { return pxlData_; }

    int16_t nx_; /// X-Nullpunkt.
    int16_t ny_; /// Y-Nullpunkt.
private:
    uint16_t width_;  /// Breite des Bildes.
    uint16_t height_; /// Höhe des Bildes.

    std::vector<uint8_t> pxlData_; /// Die Texturdaten.

    const ArchivItem_Palette* palette_; /// Die Palette.
    TextureFormat format_;              /// Das Texturformat.
};

// Define inline in header to allow optimizations
inline uint32_t ArchivItem_BitmapBase::getBBP(TextureFormat format)
{
    return (format == FORMAT_PALETTED) ? 1 : 4;
}

} // namespace libsiedler2

#endif // ARCHIVITEM_BITMAPBASE_H_INCLUDED
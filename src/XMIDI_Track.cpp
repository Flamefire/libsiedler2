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

#include "XMIDI_Track.h"
#include "ErrorCodes.h"
#include <iostream>

namespace libsiedler2 {
XMIDI_Track::XMIDI_Track() = default;

XMIDI_Track::~XMIDI_Track() = default;

int XMIDI_Track::read(std::istream& file, size_t length)
{
    data_.resize(length);
    if(!file.read(reinterpret_cast<char*>(&data_.front()), length))
        return ErrorCode::UNEXPECTED_EOF;
    return ErrorCode::NONE;
}

void XMIDI_Track::clear()
{
    data_.clear();
}
} // namespace libsiedler2

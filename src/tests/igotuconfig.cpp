/******************************************************************************
 * Copyright (C) 2009  Michael Hofmann <mh21@mh21.de>                         *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License along    *
 * with this program; if not, write to the Free Software Foundation, Inc.,    *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.                *
 ******************************************************************************/

#include "igotu/igotuconfig.h"

#include "tests.h"

using namespace igotu;

void Tests::igotuConfig()
{
    const char resetConfig[] =
        "\x01\x0d\xfc\x00\xff\x0f\xff\x3c\x00\xf1\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x3c\x3c\x00\x05\x00\x00\x00\xc8\x0c\x01\x2c\x32"
        "\x05\x14\x01\x01\x01\x02\x02\x05\x0a\x0a\x18\x6a\x0c\x35\x04\xe2"
        "\x00\xbb\x01\x17\x1e\x00\x01\x08\x08\x04\x04\x02\x02\x02\x02\x00"
        "\x00\x20\x0f\x01\x01\x01\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\xa0\xa2\x00\x19\x80\xff\xd2\x7b\xeb\x00\x4b\xc8\x62\x00\x28\x92"
        "\xaf\x00\x01\x77\x00\x01\x3a\x18\x84\x05\xa7\x0c\x88\x09\x24\xb0"
        "\xb3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x32\x11\xa0\xa2\x00\x09\x97\x00\x00\x00\xc8\x00\x00\x00\xc8\x02"
        "\x27\xb0\xb3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x32\x17\xa0\xa2\x00\x0f\xa7\x00\x00\x03\xe8\x00\x2d\xc6\xc0\x00"
        "\x00\x07\x08\x00\x01\x03\x19\xb0\xb3\x00\x00\x00\x00\x00\x00\x00"
        "\x32\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
        "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f";

    IgotuConfig config = IgotuConfig::gt120DefaultConfig();
    config.setFirstScheduleDate(QDate(2009, 10, 19));
    ARRAYCOMP(config.memoryDump().data(), resetConfig, 0x1000);
}

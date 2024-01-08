# hex-lexer

    Copyright (C) 2024 Gabriel Jickells

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

tool that converts hex written in plain text into raw binary

the hex values are written without the 0x prefix and are interpreted 2 characters at a time. For example: 0a0b will produce the 2 bytes 0x0a and 0x0b. If an invalid character is encountered, it is skipped. For example: "0a b 4kc  #2" will produce the 3 bytes 0a b4 and c2

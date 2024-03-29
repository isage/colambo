/*
        Colambo
        Copyright (C) 2024 Cat (Ivan Epifanov)

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
*/

const Color VGA_COLORS[256] = {
  0x000000,
  0x0000AA,
  0x00AA00,
  0x00AAAA,
  0xAA0000,
  0xAA00AA,
  0xAA5500,
  0xAAAAAA,
  0x555555,
  0x5555FF,
  0x55FF55,
  0x55FFFF,
  0xFF5555,
  0xFF55FF,
  0xFFFF55,
  0xFFFFFF,
  0x000000,
  0x101010,
  0x202020,
  0x353535,
  0x454545,
  0x555555,
  0x656565,
  0x757575,
  0x8A8A8A,
  0x9A9A9A,
  0xAAAAAA,
  0xBABABA,
  0xCACACA,
  0xDFDFDF,
  0xEFEFEF,
  0xFFFFFF,
  0x0000FF,
  0x4100FF,
  0x8200FF,
  0xBE00FF,
  0xFF00FF,
  0xFF00BE,
  0xFF0082,
  0xFF0041,
  0xFF0000,
  0xFF4100,
  0xFF8200,
  0xFFBE00,
  0xFFFF00,
  0xBEFF00,
  0x82FF00,
  0x41FF00,
  0x00FF00,
  0x00FF41,
  0x00FF82,
  0x00FFBE,
  0x00FFFF,
  0x00BEFF,
  0x0082FF,
  0x0041FF,
  0x8282FF,
  0x9E82FF,
  0xBE82FF,
  0xDF82FF,
  0xFF82FF,
  0xFF82DF,
  0xFF82BE,
  0xFF829E,
  0xFF8282,
  0xFF9E82,
  0xFFBE82,
  0xFFDF82,
  0xFFFF82,
  0xDFFF82,
  0xBEFF82,
  0x9EFF82,
  0x82FF82,
  0x82FF9E,
  0x82FFBE,
  0x82FFDF,
  0x82FFFF,
  0x82DFFF,
  0x82BEFF,
  0x829EFF,
  0xBABAFF,
  0xCABAFF,
  0xDFBAFF,
  0xEFBAFF,
  0xFFBAFF,
  0xFFBAEF,
  0xFFBADF,
  0xFFBACA,
  0xFFBABA,
  0xFFCABA,
  0xFFDFBA,
  0xFFEFBA,
  0xFFFFBA,
  0xEFFFBA,
  0xDFFFBA,
  0xCAFFBA,
  0xBAFFBA,
  0xBAFFCA,
  0xBAFFDF,
  0xBAFFEF,
  0xBAFFFF,
  0xBAEFFF,
  0xBADFFF,
  0xBACAFF,
  0x000071,
  0x1C0071,
  0x390071,
  0x550071,
  0x710071,
  0x710055,
  0x710039,
  0x71001C,
  0x710000,
  0x711C00,
  0x713900,
  0x715500,
  0x717100,
  0x557100,
  0x397100,
  0x1C7100,
  0x007100,
  0x00711C,
  0x007139,
  0x007155,
  0x007171,
  0x005571,
  0x003971,
  0x001C71,
  0x393971,
  0x453971,
  0x553971,
  0x613971,
  0x713971,
  0x713961,
  0x713955,
  0x713945,
  0x713939,
  0x714539,
  0x715539,
  0x716139,
  0x717139,
  0x617139,
  0x557139,
  0x457139,
  0x397139,
  0x397145,
  0x397155,
  0x397161,
  0x397171,
  0x396171,
  0x395571,
  0x394571,
  0x515171,
  0x595171,
  0x615171,
  0x695171,
  0x715171,
  0x715169,
  0x715161,
  0x715159,
  0x715151,
  0x715951,
  0x716151,
  0x716951,
  0x717151,
  0x697151,
  0x617151,
  0x597151,
  0x517151,
  0x517159,
  0x517161,
  0x517169,
  0x517171,
  0x516971,
  0x516171,
  0x515971,
  0x000041,
  0x100041,
  0x200041,
  0x310041,
  0x410041,
  0x410031,
  0x410020,
  0x410010,
  0x410000,
  0x411000,
  0x412000,
  0x413100,
  0x414100,
  0x314100,
  0x204100,
  0x104100,
  0x004100,
  0x004110,
  0x004120,
  0x004131,
  0x004141,
  0x003141,
  0x002041,
  0x001041,
  0x202041,
  0x282041,
  0x312041,
  0x392041,
  0x412041,
  0x412039,
  0x412031,
  0x412028,
  0x412020,
  0x412820,
  0x413120,
  0x413920,
  0x414120,
  0x394120,
  0x314120,
  0x284120,
  0x204120,
  0x204128,
  0x204131,
  0x204139,
  0x204141,
  0x203941,
  0x203141,
  0x202841,
  0x2D2D41,
  0x312D41,
  0x352D41,
  0x3D2D41,
  0x412D41,
  0x412D3D,
  0x412D35,
  0x412D31,
  0x412D2D,
  0x41312D,
  0x41352D,
  0x413D2D,
  0x41412D,
  0x3D412D,
  0x35412D,
  0x31412D,
  0x2D412D,
  0x2D4131,
  0x2D4135,
  0x2D413D,
  0x2D4141,
  0x2D3D41,
  0x2D3541,
  0x2D3141,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000
};
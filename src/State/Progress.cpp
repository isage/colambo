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

#include "../State/Progress.h"

#include <ctime>
#include <string>
#include <vector>
#include <memory>

#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../Utils/Logger.h"


using namespace Colambo::Graphics;

namespace Colambo
{
    namespace State
    {
        Progress::Progress() : State()
        {
        }

        Progress::~Progress()
        {
        }

        void Progress::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(false);
        }

        void Progress::think(uint32_t delta)
        {
            auto game = Game::Game::getInstance();
            State::think(delta);
            _period += delta;
            if (_period >= 500)
            {
                _period = 0;
                _progress = colamboGetDumpProgress();
            }

            if (_progress>=100)
                game->popState();
        }

        void Progress::render()
        {
            int pzx = (Renderer::getInstance()->screenWidth / 2) - (536/2);
            Renderer::getInstance()->fillRect(pzx, 216, pzx+534, 216+44, VGA_COLORS[1]);
            Renderer::getInstance()->font.draw(pzx, 216+16*0, "╔═══════════════════════ Dumping ═════════════════════════╗", VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx, 216+16*1, fmt::format("║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ {:>3d}% ║",_progress), VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx, 216+16*2, "╚═════════════════════════════════════════════════════════╝", VGA_COLORS[0x0F]);

            for (int i = 0; i < _progress/2; i++)
                Renderer::getInstance()->font.draw(pzx+16+8*i, 216+16*1, "█", VGA_COLORS[0x0F]);
        }



    }
}

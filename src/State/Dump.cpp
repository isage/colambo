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

#include "../State/Dump.h"

#include <ctime>
#include <string>
#include <vector>
#include <memory>

#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../Utils/Logger.h"
#include "../State/FadeOut.h"
#include "../State/Exit.h"
#include "../State/Peripherals.h"
#include "../State/Monitor.h"
#include "../State/Progress.h"

using namespace Colambo::Graphics;

namespace Colambo
{
    namespace State
    {
        Dump::Dump() : State()
        {
        }

        Dump::~Dump()
        {
        }

        void Dump::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(true);
            _menuPos = 2;
        }

        void Dump::think(uint32_t delta)
        {
            State::think(delta);
        }

        void Dump::render()
        {
            auto game = Game::Game::getInstance();
            State::render();

            Renderer::getInstance()->fillRect(4, 16+16*(_submenu+2), 220, 16+16*(_submenu+3), VGA_COLORS[0x00]);
            Renderer::getInstance()->font.draw(8, 16+16*(_submenu+2), "\x10", VGA_COLORS[0x34]);

            Renderer::getInstance()->font.draw(16, 16+16*2, fmt::format("Dump info"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(16, 16+16*3, fmt::format("Dump IdStorage"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(16, 16+16*4, fmt::format("Dump Abby registers"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(16, 16+16*5, fmt::format("Dump Abby dataflash"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(16, 16+16*6, fmt::format("Dump Cookie registers"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(16, 16+16*7, fmt::format("Dump Elmo registers"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(16, 16+16*8, fmt::format("Reset abby"), VGA_COLORS[0x34]);

            switch(_submenu)
            {
                case 0:
                    drawHelpText("Press X to dump General/Periphery info to ux0:/data/Calambo/data.txt");
                    break;
                case 1:
                    drawHelpText("Press X to dump IdStorage leafs to ux0:/data/Calambo/idstorage/");
                    break;
                case 2:
                    drawHelpText("Press X to dump Abby registers to ux0:/data/Calambo/abby/");
                    break;
                case 3:
                    drawHelpText("Press X to dump Abby DataFlash to ux0:/data/Calambo/abbydf/");
                    break;
                case 4:
                    drawHelpText("Press X to dump Cookie registers to ux0:/data/Calambo/cookie/");
                    break;
                case 5:
                    drawHelpText("Press X to dump Elmo registers to ux0:/data/Calambo/elmo/");
                    break;
                case 6:
                    drawHelpText("Press X to reset Abby FG");
                    break;
             }
        }

        void Dump::onKeyDown(Event::Keyboard* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->keyCode())
            {
                case SDLK_z:
                    break;
                default:
                  break;
            }
        }

        void Dump::onButtonDown(Event::Gamepad* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->button())
            {
                case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                    game->setState(new Peripherals());
                    break;
                case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                    game->setState(new Monitor());
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                    _submenu++;
                    if (_submenu > 6) _submenu = 6;
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_UP:
                    _submenu--;
                    if (_submenu < 0) _submenu = 0;
                    break;
                case SDL_CONTROLLER_BUTTON_A:
                    switch(_submenu)
                    {
                        case 0:
                            colamboDumpInfo();
                            game->pushState(new Progress());
                            break;
                        case 1:
                            colamboDumpIdstorage();
                            game->pushState(new Progress());
                            break;
                        case 2:
                            colamboDumpAbbyRegisters();
                            game->pushState(new Progress());
                            break;
                        case 3:
                            colamboDumpAbbyDataflash();
                            game->pushState(new Progress());
                            break;
                        case 4:
                            colamboDumpCookieRegisters();
                            game->pushState(new Progress());
                            break;
                        case 5:
                            colamboDumpElmoRegisters();
                            game->pushState(new Progress());
                            break;
                        case 6:
                            colamboResetAbby();
                            break;
/*                        case 6:
                            colamboDumpNvs();
                            game->pushState(new Progress());
                            break;*/
                    }
                    break;
                default:
                  break;
            }
        }

    }
}

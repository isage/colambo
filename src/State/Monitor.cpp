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

#include "../State/Monitor.h"

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
#include "../State/General.h"
#include "../State/Dump.h"

using namespace Colambo::Graphics;

namespace Colambo
{
    namespace State
    {
        Monitor::Monitor() : State()
        {
        }

        Monitor::~Monitor()
        {
        }

        void Monitor::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(true);
            _menuPos = 3;
            colamboGetMonitorData(&_monitor);
        }

        void Monitor::think(uint32_t delta)
        {
            State::think(delta);
            _period += delta;
            if (_period >= 1000)
            {
                _period = 0;
                colamboGetMonitorData(&_monitor);
            }
        }

        void Monitor::render()
        {
            auto game = Game::Game::getInstance();
            State::render();

            Renderer::getInstance()->font.draw(8, 16+16*2, fmt::format("MultiCn state:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*2, fmt::format("0x{:08X}", _monitor.multicnState), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*4, fmt::format("USB state:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*4, fmt::format("0: {} 1: {} 2: {}", _monitor.usb0State ? "client" : "host", _monitor.usb1State ? "client" : "host", _monitor.usb2State ? "client" : "host"), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*6, fmt::format("Cookie state:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*6, fmt::format("Reg01: 0x{:04X} Reg02: 0x{:04X}", _monitor.cookieReg01, _monitor.cookieReg02), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*8, fmt::format("HPRemote state:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*8, fmt::format("Mic: {:01X} HP: {:01X} DOCK: {:01X} REMOTE: {:01X}", _monitor.hpremoteMic, _monitor.hpremoteHp, _monitor.hpremoteDock, _monitor.hpremoteRemote), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*10, fmt::format("VC calib:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*10, fmt::format("VolrageRam: 0x{:04X} Voltage: 0x{:04X} CurrentRam: 0x{:04X} Current: 0x{:04X}", _monitor.voltageCalibRam, _monitor.voltageCalib, _monitor.currentCalibRam, _monitor.currentCalib), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*12, fmt::format("Abby:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*12, fmt::format("Flags: 0x{:04X} Status: 0x{:04X} SOH: 0x{:04X}", _monitor.abbyRegFlags, _monitor.abbyRegStatus, _monitor.abbyRegSOH), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*14, fmt::format("Abby:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*14, fmt::format("RC: 0x{:04X} FCC: 0x{:04X}", _monitor.abbyRegRC, _monitor.abbyRegFCC), VGA_COLORS[0x1F]);

//            drawHelpText("Test");
        }

        void Monitor::onKeyDown(Event::Keyboard* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->keyCode())
            {
                case SDLK_z:
                    LOG_DEBUG("ZEE PRESSED");
//                          game->setState(new DeviceWaiting());
//                          game->pushState(new FadeOut(new DeviceWaiting()));
//                          game->setState(new Exit());
                    break;
                default:
                  break;
            }
        }

        void Monitor::onButtonDown(Event::Gamepad* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->button())
            {
                case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                    game->setState(new Dump());
                    break;
                case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                    game->setState(new General());
                    break;
                case SDL_CONTROLLER_BUTTON_A:
//                    colamboResetAbby();
                    break;
                default:
                  break;
            }
        }

    }
}

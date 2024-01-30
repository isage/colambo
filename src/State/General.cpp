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

#include "../State/General.h"

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
#include "../State/Monitor.h"
#include "../State/Peripherals.h"

using namespace Colambo::Graphics;

namespace Colambo
{
    namespace State
    {
        General::General() : State()
        {
        }

        General::~General()
        {
        }

        void General::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(true);
            _menuPos = 0;
        }

        void General::think(uint32_t delta)
        {
            State::think(delta);
        }

        void General::render()
        {
            auto game = Game::Game::getInstance();
            auto info = game->getInfo();
            State::render();

            Renderer::getInstance()->font.draw(8, 16+16*2, fmt::format("Repair diagnostics run:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*2, fmt::format("{}", info.diagnosticsRun ? "yes" : "no"), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*3, "Product:", VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*3, fmt::format("{}", info.productTypeInfo), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*4, "Firmware:", VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*4, fmt::format("min 0x{:08X}, previous 0x{:08X}, current 0x{:08X}", info.minFw, info.prevFw, info.curFw), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*5, fmt::format("SoC revision:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*5, fmt::format("0x{:08X}", info.socRev), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*6, fmt::format("BL revision:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*6, fmt::format("0x{:04X}", info.bootloaderRev), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*7, fmt::format("HWInfo:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*7, fmt::format("0x{:08X}", info.hwInfo), VGA_COLORS[0x1F]);


            Renderer::getInstance()->font.draw(8, 16+16*8, fmt::format("SleepFactor:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*8, fmt::format("0x{:08X}", info.sleepFactor), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*9, fmt::format("WakeupFactor:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*9, fmt::format("0x{:08X}", info.wakeupFactor), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*10, fmt::format("UdcdStatus:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*10, fmt::format("0x{:08X}", info.udcdStatus), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*11, fmt::format("PowerInfo:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*11, fmt::format("0x{:08X}", info.powerInfo), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*12, "HWInfo2", VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*12, fmt::format("{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}", info.hwInfo2[0], info.hwInfo2[1], info.hwInfo2[2], info.hwInfo2[3], info.hwInfo2[4], info.hwInfo2[5], info.hwInfo2[6], info.hwInfo2[7], info.hwInfo2[8], info.hwInfo2[9], info.hwInfo2[10], info.hwInfo2[11], info.hwInfo2[12], info.hwInfo2[13], info.hwInfo2[14], info.hwInfo2[15]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*13, fmt::format("ConsoleID:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*13, fmt::format("{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}", info.consoleId[0], info.consoleId[1], info.consoleId[2], info.consoleId[3], info.consoleId[4], info.consoleId[5], info.consoleId[6], info.consoleId[7], info.consoleId[8], info.consoleId[9], info.consoleId[10], info.consoleId[11], info.consoleId[12], info.consoleId[13], info.consoleId[14], info.consoleId[15]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*14, fmt::format("openPSID:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*14, fmt::format("{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}", info.openPSID[0], info.openPSID[1], info.openPSID[2], info.openPSID[3], info.openPSID[4], info.openPSID[5], info.openPSID[6], info.openPSID[7], info.openPSID[8], info.openPSID[9], info.openPSID[10], info.openPSID[11], info.openPSID[12], info.openPSID[13], info.openPSID[14], info.openPSID[15]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*15, fmt::format("pscode:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*15, fmt::format("{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}", info.pscode[0], info.pscode[1], info.pscode[2], info.pscode[3], info.pscode[4], info.pscode[5], info.pscode[6], info.pscode[7], info.pscode[8], info.pscode[9], info.pscode[10], info.pscode[11], info.pscode[12], info.pscode[13], info.pscode[14], info.pscode[15]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*16, fmt::format("qaFlags:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*16, fmt::format("{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}", info.qaFlags[0], info.qaFlags[1], info.qaFlags[2], info.qaFlags[3], info.qaFlags[4], info.qaFlags[5], info.qaFlags[6], info.qaFlags[7], info.qaFlags[8], info.qaFlags[9], info.qaFlags[10], info.qaFlags[11], info.qaFlags[12], info.qaFlags[13], info.qaFlags[14], info.qaFlags[15]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*17, fmt::format("bootFlags:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*17, fmt::format("{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}", info.bootFlags[0], info.bootFlags[1], info.bootFlags[2], info.bootFlags[3], info.bootFlags[4], info.bootFlags[5], info.bootFlags[6], info.bootFlags[7], info.bootFlags[8], info.bootFlags[9], info.bootFlags[10], info.bootFlags[11], info.bootFlags[12], info.bootFlags[13], info.bootFlags[14], info.bootFlags[15]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*18, fmt::format("dipSwitches:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*18, fmt::format("{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}", info.dipSwitches[0], info.dipSwitches[1], info.dipSwitches[2], info.dipSwitches[3], info.dipSwitches[4], info.dipSwitches[5], info.dipSwitches[6], info.dipSwitches[7], info.dipSwitches[8], info.dipSwitches[9], info.dipSwitches[10], info.dipSwitches[11], info.dipSwitches[12], info.dipSwitches[13], info.dipSwitches[14], info.dipSwitches[15]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*19, fmt::format("gcpID:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*19, fmt::format("{}", info.gcpId), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*20, fmt::format("productID:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*20, fmt::format("{}", info.productId), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*21, fmt::format("Prepackaged sim:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*21, fmt::format("0x{:02X}", info.simPackNum), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*22, fmt::format("Com Type:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*22, fmt::format("0x{:02X}", info.comType), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*23, fmt::format("spkg 0x18 contents Ver:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*23, fmt::format("0x{:08X}", info.contentsVer), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*24, fmt::format("Factory sw ver:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*24, fmt::format("0x{:04X} 0x{:04X} 0x{:04X}", info.softVer[0],info.softVer[1],info.softVer[2]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*25, fmt::format("Color variation:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*25, fmt::format("{:02X} {:02X} {:02X} {:02X}", info.colorVariation[0], info.colorVariation[1], info.colorVariation[2], info.colorVariation[3]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*26, fmt::format("Temperature threshold:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*26, fmt::format("{:02X} {:02X} {:02X} {:02X}", info.temperatureThreshhold[0], info.temperatureThreshhold[1], info.temperatureThreshhold[2], info.temperatureThreshhold[3]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*28, fmt::format("{}", info.str1), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(8, 16+16*30, fmt::format("{}", info.str2), VGA_COLORS[0x34]);

//            drawHelpText("Test");
        }

        void General::onKeyDown(Event::Keyboard* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->keyCode())
            {
                case SDLK_z:
                    LOG_DEBUG("ZEE PRESSED");
                    break;
                default:
                  break;
            }
        }

        void General::onButtonDown(Event::Gamepad* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->button())
            {
                case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                    game->setState(new Monitor());
                    break;
                case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                    game->setState(new Peripherals());
                    break;
                default:
                  break;
            }
        }

    }
}

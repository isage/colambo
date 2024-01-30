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

#include "../State/Peripherals.h"

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
#include "../State/Dump.h"
#include "../State/General.h"

using namespace Colambo::Graphics;

namespace Colambo
{
    namespace State
    {
        Peripherals::Peripherals() : State()
        {
        }

        Peripherals::~Peripherals()
        {
        }

        void Peripherals::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(true);
            _menuPos = 1;
        }

        void Peripherals::think(uint32_t delta)
        {
            State::think(delta);
        }

        void Peripherals::render()
        {
            auto game = Game::Game::getInstance();
            auto info = game->getInfo();
            State::render();

            Renderer::getInstance()->font.draw(8, 16+16*2, fmt::format("Ernie:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*2, fmt::format("HW: 0x{:08X} FW: 0x{:08X} DL: 0x{:08X} CFG: 0x{:04X}", info.ernieHwInfo, info.ernieFwVersion, info.ernieDlVersion, info.ernieCfgVersion), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*3, fmt::format("Elmo:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*3, fmt::format("FW: 0x{:04X}", info.elmoFWVer), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*4, fmt::format("Cookie:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*4, fmt::format("FW: 0x{:04X}", info.cookieFWVer), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*5, fmt::format("Abby:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*5, fmt::format("HW: 0x{:04X} FW: 0x{:04X} DF: 0x{:04X}", info.abbyHWVersion, info.abbyFWVersion, info.abbyDFVersion), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*6, fmt::format("Battery calibration:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*6, fmt::format("Volt: 0x{:04X} Current: 0x{:04X}", info.batteryVoltageCalib, info.batteryCurrentCalib), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*7, fmt::format("Battery lot:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*7, fmt::format("{}", info.batteryLotInfo), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*8, fmt::format("EmmcFw:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*8, fmt::format("{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}", info.emmcFwVersion[0], info.emmcFwVersion[1], info.emmcFwVersion[2], info.emmcFwVersion[3], info.emmcFwVersion[4], info.emmcFwVersion[5], info.emmcFwVersion[6], info.emmcFwVersion[7]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*9, fmt::format("EmmcFw2:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*9, fmt::format("{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}", info.emmcFwVersion2[0], info.emmcFwVersion2[1], info.emmcFwVersion2[2], info.emmcFwVersion2[3], info.emmcFwVersion2[4], info.emmcFwVersion2[5], info.emmcFwVersion2[6], info.emmcFwVersion2[7]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*10, fmt::format("Front touch:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*10, fmt::format("Vendor: {:04X} FW: {:04X} Cfg: {:04X} Lot: {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}", info.tpFrontVendorID, info.tpFrontFirmwareRev, info.tpFrontCfgVersion, info.tpFrontLotInfo[0], info.tpFrontLotInfo[1], info.tpFrontLotInfo[2], info.tpFrontLotInfo[3], info.tpFrontLotInfo[4], info.tpFrontLotInfo[5], info.tpFrontLotInfo[6], info.tpFrontLotInfo[7]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*11, fmt::format("Rear touch:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*11, fmt::format("Vendor: {:04X} FW: {:04X} Cfg: {:04X} Lot: {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}", info.tpRearVendorID, info.tpRearFirmwareRev, info.tpRearCfgVersion, info.tpRearLotInfo[0], info.tpRearLotInfo[1], info.tpRearLotInfo[2], info.tpRearLotInfo[3], info.tpRearLotInfo[4], info.tpRearLotInfo[5], info.tpRearLotInfo[6], info.tpRearLotInfo[7]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*12, fmt::format("WLANBT:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*12, fmt::format("HW: {:08X} WLAN MAC: {:02X}:{:02X}:{:02X}:{:02X}:{:02X}:{:02X} BT MAC: {:02X}:{:02X}:{:02X}:{:02X}:{:02X}:{:02X}", info.wlanBtHWRevision, info.wlanMacAddress[0], info.wlanMacAddress[1], info.wlanMacAddress[2], info.wlanMacAddress[3], info.wlanMacAddress[4], info.wlanMacAddress[5], info.btMacAddress[0], info.btMacAddress[1], info.btMacAddress[2], info.btMacAddress[3], info.btMacAddress[4], info.btMacAddress[5]), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*13, fmt::format("ETH:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*13, fmt::format("MAC: {:02X}:{:02X}:{:02X}:{:02X}:{:02X}:{:02X}", info.ethMacAddress[0], info.ethMacAddress[1], info.ethMacAddress[2], info.ethMacAddress[3], info.ethMacAddress[4], info.ethMacAddress[5]), VGA_COLORS[0x1F]);


            Renderer::getInstance()->font.draw(8, 16+16*14, fmt::format("OLED lot:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*14, fmt::format("{}", info.oledLotInfo), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*15, fmt::format("LCD lot:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*15, fmt::format("{}", info.lcdLotInfo), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*16, fmt::format("Unknown lot:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*16, fmt::format("{}", info.unkInfo), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*17, fmt::format("Unknown lot 2:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*17, fmt::format("{}", info.unkInfo2), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*18, fmt::format("IMEI:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*18, fmt::format("{}", info.imei), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*19, fmt::format("IMEI barcode:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*19, fmt::format("{}", info.imeiBarcode), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*20, fmt::format("Parts barcode:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*20, fmt::format("{}", info.partsNoBarcode), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*21, fmt::format("IMSI:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*21, fmt::format("{}", info.imsi), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*22, fmt::format("ICCID:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*22, fmt::format("{}", info.iccId), VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(8, 16+16*23, fmt::format("KibanID:"), VGA_COLORS[0x34]);
            Renderer::getInstance()->font.draw(288, 16+16*23, fmt::format("{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}", info.kibanId[0], info.kibanId[1], info.kibanId[2], info.kibanId[3], info.kibanId[4], info.kibanId[5], info.kibanId[6], info.kibanId[7], info.kibanId[8], info.kibanId[9], info.kibanId[10], info.kibanId[11], info.kibanId[12], info.kibanId[13], info.kibanId[14], info.kibanId[15]), VGA_COLORS[0x1F]);

//            drawHelpText("Test");
        }

        void Peripherals::onKeyDown(Event::Keyboard* event)
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

        void Peripherals::onButtonDown(Event::Gamepad* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->button())
            {
                case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                    game->setState(new General());
                    break;
                case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                    game->setState(new Dump());
                    break;
                default:
                  break;
            }
        }

    }
}

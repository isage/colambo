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

#include "../State/State.h"

#include <algorithm>
#include <memory>

#include "../Event/State.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"

using namespace Colambo::Graphics;

namespace Colambo
{
    namespace State
    {
        State::State() : Event::EventTarget(Game::Game::getInstance()->eventDispatcher())
        {
            activateHandler().add([this](Event::State* event){ this->onStateActivate(event); });
            deactivateHandler().add([this](Event::State* event){ this->onStateDeactivate(event); });

            keyDownHandler().add([this](Event::Keyboard* event) { this->onKeyDown(event); });
            keyUpHandler().add([this](Event::Keyboard* event) { this->onKeyUp(event); });

            buttonDownHandler().add([this](Event::Gamepad* event) { this->onButtonDown(event); });
            buttonUpHandler().add([this](Event::Gamepad* event) { this->onButtonUp(event); });
            axisHandler().add([this](Event::Gamepad* event) { this->onAxis(event); });

            textInputHandler().add([this](Event::Text* event) { this->onTextInput(event); });
            textEditingHandler().add([this](Event::Text* event) { this->onTextEditing(event); });

        }

        State::~State()
        {
        }

        void State::drawHelpText(std::string text)
        {
            Renderer::getInstance()->fillRect(0, Renderer::getInstance()->screenHeight-16, Renderer::getInstance()->screenWidth, Renderer::getInstance()->screenHeight, VGA_COLORS[0x03]);
            Renderer::getInstance()->font.draw(4, Renderer::getInstance()->screenHeight-16, text.substr(0,1), VGA_COLORS[0x04]);
            Renderer::getInstance()->font.draw(12, Renderer::getInstance()->screenHeight-16, text.substr(1), VGA_COLORS[0x1f]);
        }

        void State::renderTopMenu()
        {
            std::vector<std::string> _items = {
                "General",
                "Peripherals",
                "Dump",
                "Monitor"
            };

            Renderer::getInstance()->fillRect(0, 0, Renderer::getInstance()->screenWidth, 16, VGA_COLORS[0x03]);
            Renderer::getInstance()->fillRect(0, 0, 40, 16, VGA_COLORS[0x4F]);
            Renderer::getInstance()->font.draw(4, 0, "\x11 L1", VGA_COLORS[0x00]);
            Renderer::getInstance()->fillRect(Renderer::getInstance()->screenWidth - 40, 0, Renderer::getInstance()->screenWidth, 16, VGA_COLORS[0x4F]);
            Renderer::getInstance()->font.draw(Renderer::getInstance()->screenWidth - 36, 0, "R1 \x10", VGA_COLORS[0x00]);

            int x = 60;
            int pos = 0;
            for(auto& str : _items)
            {
                if (pos == _menuPos)
                {
                    int w = Renderer::getInstance()->font.getWidth(str);
                    Renderer::getInstance()->fillRect(x-4, 0, x+w+4, 16, VGA_COLORS[0x00]);
                }
                x += Renderer::getInstance()->font.draw(x, 0, str, VGA_COLORS[0x1f]) + 16;
                pos++;
            }

        }


        void State::init()
        {
            _initialized = true;
        }

        void State::think(uint32_t delta)
        {
        }

        bool State::initialized()
        {
            return _initialized;
        }

        bool State::fullscreen() const
        {
            return _fullscreen;
        }

        void State::setFullscreen(bool value)
        {
            _fullscreen = value;
        }

        bool State::modal() const
        {
            return _modal;
        }

        void State::setModal(bool value)
        {
            _modal = value;
        }

        void State::handle(Event::Event* event)
        {
            if (event->handled()) return;

            if (auto keyboardEvent = dynamic_cast<Event::Keyboard*>(event))
            {
                switch (keyboardEvent->originalType())
                {
                    case Event::Keyboard::Type::KEY_UP:
                    {
                        emitEvent(std::make_unique<Event::Keyboard>(*keyboardEvent), keyUpHandler());
                        break;
                    }
                    case Event::Keyboard::Type::KEY_DOWN:
                    {
                        emitEvent(std::make_unique<Event::Keyboard>(*keyboardEvent), keyDownHandler());
                        break;
                    }
                }
            }

            if (auto gamepadEvent = dynamic_cast<Event::Gamepad*>(event))
            {
                switch (gamepadEvent->originalType())
                {
                    case Event::Gamepad::Type::BUTTON_UP:
                    {
                        emitEvent(std::make_unique<Event::Gamepad>(*gamepadEvent), buttonUpHandler());
                        break;
                    }
                    case Event::Gamepad::Type::BUTTON_DOWN:
                    {
                        emitEvent(std::make_unique<Event::Gamepad>(*gamepadEvent), buttonDownHandler());
                        break;
                    }
                    case Event::Gamepad::Type::AXIS:
                    {
                        emitEvent(std::make_unique<Event::Gamepad>(*gamepadEvent), axisHandler());
                        break;
                    }
                }
            }

            if (auto textEvent = dynamic_cast<Event::Text*>(event))
            {
                switch (textEvent->originalType())
                {
                    case Event::Text::Type::INPUT:
                    {
                        emitEvent(std::make_unique<Event::Text>(*textEvent), textInputHandler());
                        break;
                    }
                    case Event::Text::Type::EDITING:
                    {
                        emitEvent(std::make_unique<Event::Text>(*textEvent), textEditingHandler());
                        break;
                    }
                }
            }
        }

        void State::render()
        {
            Renderer::getInstance()->clearScreen(VGA_COLORS[0x15]);
            renderTopMenu();
        }

        void State::onStateActivate(Event::State* event)
        {
        }

        void State::onStateDeactivate(Event::State* event)
        {
        }

        void State::onKeyDown(Event::Keyboard* event)
        {
        }

        void State::onKeyUp(Event::Keyboard* event)
        {
        }

        void State::onButtonDown(Event::Gamepad* event)
        {
        }

        void State::onButtonUp(Event::Gamepad* event)
        {
        }

        void State::onAxis(Event::Gamepad* event)
        {
        }

        void State::onTextInput(Event::Text* event)
        {
        }

        void State::onTextEditing(Event::Text* event)
        {
        }

        bool State::active()
        {
            return _active;
        }

        void State::setActive(bool value)
        {
            _active = value;
        }

        Event::StateHandler& State::pushHandler()
        {
            return _pushHandler;
        }

        Event::StateHandler& State::popHandler()
        {
            return _popHandler;
        }

        Event::StateHandler& State::activateHandler()
        {
            return _activateHandler;
        }

        Event::StateHandler& State::deactivateHandler()
        {
            return _deactivateHandler;
        }

        Event::KeyboardHandler& State::keyDownHandler()
        {
            return _keyDownHandler;
        }

        Event::KeyboardHandler& State::keyUpHandler()
        {
            return _keyUpHandler;
        }

        Event::GamepadHandler& State::buttonUpHandler()
        {
            return _buttonUpHandler;
        }

        Event::GamepadHandler& State::buttonDownHandler()
        {
            return _buttonDownHandler;
        }

        Event::GamepadHandler& State::axisHandler()
        {
            return _axisHandler;
        }

        Event::TextHandler& State::textInputHandler()
        {
            return _textInputHandler;
        }

        Event::TextHandler& State::textEditingHandler()
        {
            return _textEditingHandler;
        }
    }
}

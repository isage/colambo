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

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "../Base/Delegate.h"

namespace Colambo
{
namespace Event
{
class Event;
class Keyboard;
class Gamepad;
class Text;
class State;

using Handler = Base::Delegate<Event*>;
using KeyboardHandler = Base::Delegate<Keyboard*>;
using GamepadHandler = Base::Delegate<Gamepad*>;
using TextHandler = Base::Delegate<Text*>;
using StateHandler = Base::Delegate<State*>;

}
}

#endif //EVENT_HANDLER_H

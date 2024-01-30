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

#ifndef STATE_MONITOR_H
#define STATE_MONITOR_H

#include "../State/State.h"
#include <colambo-helper.h>

namespace Colambo
{
    namespace State
    {
        class Monitor : public State
        {
            public:
                Monitor();
                ~Monitor() override;

                void think(uint32_t delta) override;
                void init() override;
                void render() override;
                void onKeyDown(Event::Keyboard* event) override;
                void onButtonDown(Event::Gamepad* event) override;
            private:
                 monitor_t _monitor = {0};
                 uint32_t _period = 0;
        };
    }
}
#endif // STATE_MONITOR_H

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

#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include "Base/Singleton.h"

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Colambo
{
class ResourceManager
{

public:
  static ResourceManager *getInstance();
  static bool fileExists(const std::string &filename);

  void shutdown();
  std::string getLocalizedPath(const std::string &filename);
  std::string getPrefPath(const std::string &filename);
  std::string getPathForDir(const std::string &dir);
protected:
  friend class Base::Singleton<ResourceManager>;

  ResourceManager();
  ~ResourceManager();
  ResourceManager(const ResourceManager &) = delete;
  ResourceManager &operator=(const ResourceManager &) = delete;
};
}
#endif

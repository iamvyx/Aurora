#pragma once

#include <string>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

namespace Aurora
{
    class VirtualMachine
    {
        public:
            static VirtualMachine* Create();
            static VirtualMachine* Create(std::string path);

            void Destroy();

            void Parse(std::string path);

            template<typename T>
            T To(int idx);

        private:
            VirtualMachine();
            ~VirtualMachine();

        private:
            lua_State* m_luau;
    };

    template<>
    inline std::string VirtualMachine::To<std::string>(int idx)
    {
        return lua_tostring(m_luau, idx);
    }
}
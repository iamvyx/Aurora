#include "VirtualMachine.h"

#include <iostream>
#include <sstream>

namespace Aurora
{
    VirtualMachine* VirtualMachine::Create()
    {
        auto* instance = new VirtualMachine();

        return instance;
    }

    VirtualMachine* VirtualMachine::Create(std::string path)
    {
        auto* instance = new VirtualMachine();

        instance->Parse(path);

        return instance;
    }

    void VirtualMachine::Destroy()
    {
        delete this;
    }

    void VirtualMachine::Parse(std::string path)
    {
        std::string sourceCode = R"(
            local message = "Hello from Luau!"
            print(message)
            
            -- Testing Luau type-infusion / syntax structure
            local function add(a: number, b: number): number
                return a + b
            end
            print("Result: " .. add(10, 20))
        )";

        // 3. Compile Luau text into bytecode
        size_t bytecodeSize = 0;
        // luau_compile allocates a heap buffer containing the bytecode
        char* bytecode = luau_compile(sourceCode.c_str(), sourceCode.length(), nullptr, &bytecodeSize);

        if (!bytecode) {
            std::cerr << "Compilation failed to allocate memory." << std::endl;
            lua_close(m_luau);
        }

        // 4. Load the bytecode into the Luau VM
        // luau_load returns 0 on success
        if (luau_load(m_luau, "main", bytecode, bytecodeSize, 0) == 0) {
            // Free bytecode buffer immediately after loading
            free(bytecode);

            // 5. Execute the loaded chunk
            if (lua_pcall(m_luau, 0, 0, 0) != 0) {
                std::cerr << "Runtime Error: " << To<std::string>(-1) << std::endl;
                lua_pop(m_luau, 1); // Remove error object
            }
        } else {
            std::cerr << "Load Error: " << To<std::string>(-1) << std::endl;
            lua_pop(m_luau, 1);
            free(bytecode);
        }
    }

    VirtualMachine::VirtualMachine()
    {
        try
        {
            m_luau = luaL_newstate();
            if (m_luau == nullptr)
            {
                throw std::runtime_error((std::stringstream("Virtual Machine Error: ") << To<std::string>(-1)).str());
            }

            luaL_openlibs(m_luau);

            #if defined(AURORA_DEBUG)
            std::cout << "Virtual Machine Created with Success\n";
            #endif
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    VirtualMachine::~VirtualMachine()
    {
        if (m_luau)
            lua_close(m_luau);
        
        #if defined(AURORA_DEBUG)
        std::cout << "Virtual Machine Destroyed with Success\n";
        #endif
    }
}
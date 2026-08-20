#include <iostream>

#include <VirtualMachine.h>

using Aurora::VirtualMachine;

int main()
{
    VirtualMachine* vm = VirtualMachine::Create("");

    vm->Destroy();

    return 0;
}
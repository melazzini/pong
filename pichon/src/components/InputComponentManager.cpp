#include "components/InputComponent.h"

InputComponentManager *InputComponentManager::getInstance()
{
    static InputComponentManager instance;
    return &instance;
}

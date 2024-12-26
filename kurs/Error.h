#pragma once

#include <stdexcept>
#include <string>

using namespace std;

/**
 * @class Error
 * @brief Класс для обработки ошибок, наследуется от std::runtime_error.
 */
class Error : public runtime_error
{
public:
    /**
     * @brief Конструктор для создания исключения с сообщением об ошибке и именем функции.
     * 
     * @param message Сообщение об ошибке.
     * @param func Имя функции, в которой произошла ошибка.
     */
    Error(const string &message, const string &func);
};

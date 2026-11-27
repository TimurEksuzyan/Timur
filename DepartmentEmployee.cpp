#include "DepartmentEmployee.h"
#include <stdexcept>
#include <utility>

namespace
{
    bool HasNoControlChars(const std::string& text)
    {
        for (const char ch : text)
        {
            const unsigned char uch = static_cast<unsigned char>(ch);
            if (uch < 0x20 || uch == 0x7F)
            {
                return false;
            }
        }
        return true;
    }

    bool IsValidNonEmptyText(const std::string& text)
    {
        if (!HasNoControlChars(text))
        {
            return false;
        }
        for (const char ch : text)
        {
            if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r')
            {
                return true;
            }
        }
        return false;
    }
}

std::string EmployeeRoleToString(const EmployeeRole role)
{
    switch (role)
    {
    case EmployeeRole::Teacher:
        return "Преподаватель";
    case EmployeeRole::Engineer:
        return "Инженер";
    default:
        throw std::invalid_argument("Неизвестный вид работника кафедры");
    }
}

DepartmentEmployee::DepartmentEmployee()
    : id(""), surname(""), name(""), patronymic(""), position("")
{
}

DepartmentEmployee::DepartmentEmployee(const std::string& id,
                                       const std::string& surname,
                                       const std::string& name,
                                       const std::string& patronymic,
                                       const std::string& position)
    : id(id),
      surname(surname),
      name(name),
      patronymic(patronymic),
      position(position)
{
    if (!IsValidNonEmptyText(this->id))
    {
        throw std::invalid_argument("Идентификатор работника не может быть пустым или содержать управляющие символы");
    }
    if (!IsValidNonEmptyText(this->surname) || !IsValidNonEmptyText(this->name))
    {
        throw std::invalid_argument("Фамилия и имя работника не могут быть пустыми или содержать управляющие символы");
    }
    if (!HasNoControlChars(this->patronymic))
    {
        throw std::invalid_argument("Отчество не может содержать управляющие символы");
    }
    if (!IsValidNonEmptyText(this->position))
    {
        throw std::invalid_argument("Должность не может быть пустой или содержать управляющие символы");
    }
}

DepartmentEmployee::DepartmentEmployee(const DepartmentEmployee& other)
    : id(other.id),
      surname(other.surname),
      name(other.name),
      patronymic(other.patronymic),
      position(other.position)
{
}

DepartmentEmployee& DepartmentEmployee::operator=(const DepartmentEmployee& other)
{
    if (this != &other)
    {
        id = other.id;
        surname = other.surname;
        name = other.name;
        patronymic = other.patronymic;
        position = other.position;
    }
    return *this;
}

DepartmentEmployee::DepartmentEmployee(DepartmentEmployee&& other) noexcept
    : id(std::move(other.id)),
      surname(std::move(other.surname)),
      name(std::move(other.name)),
      patronymic(std::move(other.patronymic)),
      position(std::move(other.position))
{
}

DepartmentEmployee& DepartmentEmployee::operator=(DepartmentEmployee&& other) noexcept
{
    if (this != &other)
    {
        id = std::move(other.id);
        surname = std::move(other.surname);
        name = std::move(other.name);
        patronymic = std::move(other.patronymic);
        position = std::move(other.position);
    }
    return *this;
}

const std::string& DepartmentEmployee::GetId() const
{
    return id;
}

void DepartmentEmployee::SetId(const std::string& newId)
{
    if (!IsValidNonEmptyText(newId))
    {
        throw std::invalid_argument("Идентификатор работника не может быть пустым или содержать управляющие символы");
    }
    id = newId;
}

const std::string& DepartmentEmployee::GetSurname() const
{
    return surname;
}

void DepartmentEmployee::SetSurname(const std::string& newSurname)
{
    if (!IsValidNonEmptyText(newSurname))
    {
        throw std::invalid_argument("Фамилия не может быть пустой или содержать управляющие символы");
    }
    surname = newSurname;
}

const std::string& DepartmentEmployee::GetName() const
{
    return name;
}

void DepartmentEmployee::SetName(const std::string& newName)
{
    if (!IsValidNonEmptyText(newName))
    {
        throw std::invalid_argument("Имя не может быть пустым или содержать управляющие символы");
    }
    name = newName;
}

const std::string& DepartmentEmployee::GetPatronymic() const
{
    return patronymic;
}

void DepartmentEmployee::SetPatronymic(const std::string& newPatronymic)
{
    if (!HasNoControlChars(newPatronymic))
    {
        throw std::invalid_argument("Отчество не может содержать управляющие символы");
    }
    patronymic = newPatronymic;
}

const std::string& DepartmentEmployee::GetPosition() const
{
    return position;
}

void DepartmentEmployee::SetPosition(const std::string& newPosition)
{
    if (!IsValidNonEmptyText(newPosition))
    {
        throw std::invalid_argument("Должность не может быть пустой или содержать управляющие символы");
    }
    position = newPosition;
}

std::string DepartmentEmployee::GetFullName() const
{
    std::string fullName = surname;
    if (!name.empty())
    {
        if (!fullName.empty()) fullName += " ";
        fullName += name;
    }
    if (!patronymic.empty())
    {
        if (!fullName.empty()) fullName += " ";
        fullName += patronymic;
    }
    return fullName;
}

bool DepartmentEmployee::BaseEquals(const DepartmentEmployee& other) const
{
    return id == other.id &&
           surname == other.surname &&
           name == other.name &&
           patronymic == other.patronymic &&
           position == other.position;
}
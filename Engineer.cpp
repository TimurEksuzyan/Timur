#include "Engineer.h"
#include <algorithm>
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

Engineer::Engineer()
    : DepartmentEmployee(), specialization(""), researchTopics()
{
}

Engineer::Engineer(const std::string& id,
                   const std::string& surname,
                   const std::string& name,
                   const std::string& patronymic,
                   const std::string& position,
                   const std::string& specialization)
    : DepartmentEmployee(id, surname, name, patronymic, position),
      specialization(specialization),
      researchTopics()
{
    if (!HasNoControlChars(this->specialization))
    {
        throw std::invalid_argument("Специализация не может содержать управляющие символы");
    }
}

Engineer::Engineer(const Engineer& other)
    : DepartmentEmployee(other),
      specialization(other.specialization),
      researchTopics(other.researchTopics)
{
}

Engineer& Engineer::operator=(const Engineer& other)
{
    if (this != &other)
    {
        DepartmentEmployee::operator=(other);
        specialization = other.specialization;
        researchTopics = other.researchTopics;
    }
    return *this;
}

Engineer::Engineer(Engineer&& other) noexcept
    : DepartmentEmployee(std::move(other)),
      specialization(std::move(other.specialization)),
      researchTopics(std::move(other.researchTopics))
{
}

Engineer& Engineer::operator=(Engineer&& other) noexcept
{
    if (this != &other)
    {
        DepartmentEmployee::operator=(std::move(other));
        specialization = std::move(other.specialization);
        researchTopics = std::move(other.researchTopics);
    }
    return *this;
}

const std::string& Engineer::GetSpecialization() const
{
    return specialization;
}

void Engineer::SetSpecialization(const std::string& newSpecialization)
{
    if (!HasNoControlChars(newSpecialization))
    {
        throw std::invalid_argument("Специализация не может содержать управляющие символы");
    }
    specialization = newSpecialization;
}

void Engineer::AddResearchTopic(const std::string& topic)
{
    if (!IsValidNonEmptyText(topic))
    {
        throw std::invalid_argument("Тема НИР не может быть пустой");
    }
    if (std::find(researchTopics.begin(), researchTopics.end(), topic) == researchTopics.end())
    {
        researchTopics.push_back(topic);
    }
}

const std::vector<std::string>& Engineer::GetResearchTopics() const
{
    return researchTopics;
}

EmployeeRole Engineer::GetRole() const
{
    return EmployeeRole::Engineer;
}

std::unique_ptr<DepartmentEmployee> Engineer::Clone() const
{
    return std::make_unique<Engineer>(*this);
}

bool Engineer::Equals(const DepartmentEmployee& other) const
{
    const Engineer* otherEngineer = dynamic_cast<const Engineer*>(&other);
    return otherEngineer != nullptr && (*this == *otherEngineer);
}

std::string Engineer::ToString() const
{
    std::string res = "[Инженер] ФИО: " + GetFullName();
    if (!id.empty())
    {
        res += " (ID: " + id + ")";
    }
    res += " | Должность: " + (position.empty() ? "не указана" : position);
    if (!specialization.empty())
    {
        res += " | Специализация: " + specialization;
    }
    res += " | НИР: " + std::to_string(researchTopics.size());
    return res;
}

std::string Engineer::GetSummary() const
{
    std::string res = "Инженер: " + GetFullName()
        + " | Должность: " + (position.empty() ? "не указана" : position);
    if (!specialization.empty())
    {
        res += " (" + specialization + ")";
    }
    return res;
}

bool Engineer::operator==(const Engineer& other) const
{
    return BaseEquals(other) &&
           specialization == other.specialization &&
           researchTopics == other.researchTopics;
}

bool Engineer::operator!=(const Engineer& other) const
{
    return !(*this == other);
}
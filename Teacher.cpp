#include "Teacher.h"
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

Teacher::Teacher()
    : DepartmentEmployee(), academicDegree(""), teachingLoad(), researchTopics()
{
}

Teacher::Teacher(const std::string& id,
                 const std::string& surname,
                 const std::string& name,
                 const std::string& patronymic,
                 const std::string& position,
                 const std::string& academicDegree)
    : DepartmentEmployee(id, surname, name, patronymic, position),
      academicDegree(academicDegree),
      teachingLoad(),
      researchTopics()
{
    if (!HasNoControlChars(this->academicDegree))
    {
        throw std::invalid_argument("Ученая степень не может содержать управляющие символы");
    }
}

Teacher::Teacher(const Teacher& other)
    : DepartmentEmployee(other),
      academicDegree(other.academicDegree),
      teachingLoad(other.teachingLoad),
      researchTopics(other.researchTopics)
{
}

Teacher& Teacher::operator=(const Teacher& other)
{
    if (this != &other)
    {
        DepartmentEmployee::operator=(other);
        academicDegree = other.academicDegree;
        teachingLoad = other.teachingLoad;
        researchTopics = other.researchTopics;
    }
    return *this;
}

Teacher::Teacher(Teacher&& other) noexcept
    : DepartmentEmployee(std::move(other)),
      academicDegree(std::move(other.academicDegree)),
      teachingLoad(std::move(other.teachingLoad)),
      researchTopics(std::move(other.researchTopics))
{
}

Teacher& Teacher::operator=(Teacher&& other) noexcept
{
    if (this != &other)
    {
        DepartmentEmployee::operator=(std::move(other));
        academicDegree = std::move(other.academicDegree);
        teachingLoad = std::move(other.teachingLoad);
        researchTopics = std::move(other.researchTopics);
    }
    return *this;
}

const std::string& Teacher::GetAcademicDegree() const
{
    return academicDegree;
}

void Teacher::SetAcademicDegree(const std::string& newDegree)
{
    if (!HasNoControlChars(newDegree))
    {
        throw std::invalid_argument("Ученая степень не может содержать управляющие символы");
    }
    academicDegree = newDegree;
}

void Teacher::AddTeachingActivity(const std::string& discipline, const std::string& classType)
{
    if (!IsValidNonEmptyText(discipline) || !IsValidNonEmptyText(classType))
    {
        throw std::invalid_argument("Название дисциплины и вид занятия не могут быть пустыми");
    }
    const auto item = std::make_pair(discipline, classType);
    if (std::find(teachingLoad.begin(), teachingLoad.end(), item) == teachingLoad.end())
    {
        teachingLoad.push_back(item);
    }
}

const std::vector<std::pair<std::string, std::string>>& Teacher::GetTeachingLoad() const
{
    return teachingLoad;
}

bool Teacher::TeachesClass(const std::string& discipline, const std::string& classType) const
{
    const auto item = std::make_pair(discipline, classType);
    return std::find(teachingLoad.begin(), teachingLoad.end(), item) != teachingLoad.end();
}

std::vector<std::string> Teacher::GetClassTypesByDiscipline(const std::string& discipline) const
{
    std::vector<std::string> types;
    for (const auto& entry : teachingLoad)
    {
        if (entry.first == discipline &&
            std::find(types.begin(), types.end(), entry.second) == types.end())
        {
            types.push_back(entry.second);
        }
    }
    return types;
}

void Teacher::AddResearchTopic(const std::string& topic)
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

const std::vector<std::string>& Teacher::GetResearchTopics() const
{
    return researchTopics;
}

EmployeeRole Teacher::GetRole() const
{
    return EmployeeRole::Teacher;
}

std::unique_ptr<DepartmentEmployee> Teacher::Clone() const
{
    return std::make_unique<Teacher>(*this);
}

bool Teacher::Equals(const DepartmentEmployee& other) const
{
    const Teacher* otherTeacher = dynamic_cast<const Teacher*>(&other);
    return otherTeacher != nullptr && (*this == *otherTeacher);
}

std::string Teacher::ToString() const
{
    std::string res = "[Преподаватель] ФИО: " + GetFullName();
    if (!id.empty())
    {
        res += " (ID: " + id + ")";
    }
    res += " | Должность: " + (position.empty() ? "не указана" : position);
    if (!academicDegree.empty())
    {
        res += " | Степень/звание: " + academicDegree;
    }
    res += " | Занятий: " + std::to_string(teachingLoad.size());
    res += " | НИР: " + std::to_string(researchTopics.size());
    return res;
}

std::string Teacher::GetSummary() const
{
    std::string res = "Преподаватель: " + GetFullName()
        + " | Должность: " + (position.empty() ? "не указана" : position);
    if (!academicDegree.empty())
    {
        res += " (" + academicDegree + ")";
    }
    return res;
}

bool Teacher::operator==(const Teacher& other) const
{
    return BaseEquals(other) &&
           academicDegree == other.academicDegree &&
           teachingLoad == other.teachingLoad &&
           researchTopics == other.researchTopics;
}

bool Teacher::operator!=(const Teacher& other) const
{
    return !(*this == other);
}
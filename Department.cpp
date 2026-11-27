#include "Department.h"
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

std::vector<std::unique_ptr<DepartmentEmployee>> Department::CloneEmployees(
    const std::vector<std::unique_ptr<DepartmentEmployee>>& source)
{
    std::vector<std::unique_ptr<DepartmentEmployee>> result;
    result.reserve(source.size());
    for (const auto& emp : source)
    {
        if (emp)
        {
            result.push_back(emp->Clone());
        }
    }
    return result;
}

Department::Department()
    : name(""), employees(), researchWorks(), nextResearchId(1)
{
}

Department::Department(const std::string& name)
    : name(name), employees(), researchWorks(), nextResearchId(1)
{
    if (!IsValidNonEmptyText(this->name))
    {
        throw std::invalid_argument("Название кафедры не может быть пустым или содержать управляющие символы");
    }
}

Department::Department(const Department& other)
    : name(other.name),
      employees(CloneEmployees(other.employees)),
      researchWorks(other.researchWorks),
      nextResearchId(other.nextResearchId)
{
}

Department& Department::operator=(const Department& other)
{
    if (this != &other)
    {
        auto cloned = CloneEmployees(other.employees);
        name = other.name;
        employees = std::move(cloned);
        researchWorks = other.researchWorks;
        nextResearchId = other.nextResearchId;
    }
    return *this;
}

Department::Department(Department&& other) noexcept
    : name(std::move(other.name)),
      employees(std::move(other.employees)),
      researchWorks(std::move(other.researchWorks)),
      nextResearchId(other.nextResearchId)
{
    other.nextResearchId = 1;
}

Department& Department::operator=(Department&& other) noexcept
{
    if (this != &other)
    {
        name = std::move(other.name);
        employees = std::move(other.employees);
        researchWorks = std::move(other.researchWorks);
        nextResearchId = other.nextResearchId;
        other.nextResearchId = 1;
    }
    return *this;
}

const std::string& Department::GetName() const
{
    return name;
}

void Department::SetName(const std::string& newName)
{
    if (!IsValidNonEmptyText(newName))
    {
        throw std::invalid_argument("Название кафедры не может быть пустым или содержать управляющие символы");
    }
    name = newName;
}

void Department::AddEmployee(const DepartmentEmployee& employee)
{
    for (const auto& existing : employees)
    {
        if (existing && existing->GetId() == employee.GetId())
        {
            throw std::invalid_argument("Работник с ID " + employee.GetId() + " уже зарегистрирован на кафедре");
        }
    }
    employees.push_back(employee.Clone());
}

ResearchWork Department::RegisterResearchWork(const std::string& title, const std::string& supervisor)
{
    while (ResearchWork::IsIdExists(nextResearchId))
    {
        nextResearchId++;
    }
    const int workId = nextResearchId++;
    ResearchWork work(workId, title, supervisor);
    researchWorks.push_back(work);
    return work;
}

void Department::AddResearchWork(const ResearchWork& work)
{
    for (const ResearchWork& existing : researchWorks)
    {
        if (existing.GetId() == work.GetId())
        {
            throw std::invalid_argument("НИР с ID " + std::to_string(work.GetId()) + " уже зарегистрирована на кафедре");
        }
    }
    researchWorks.push_back(work);
}

const std::vector<std::unique_ptr<DepartmentEmployee>>& Department::GetEmployees() const
{
    return employees;
}

const std::vector<ResearchWork>& Department::GetResearchWorks() const
{
    return researchWorks;
}

std::vector<ResearchWork> Department::FindResearchWorksByTopic(const std::string& topicQuery) const
{
    if (!IsValidNonEmptyText(topicQuery))
    {
        throw std::invalid_argument("Запрос поиска по теме НИР не может быть пустым");
    }

    std::vector<ResearchWork> result;
    for (const ResearchWork& work : researchWorks)
    {
        if (work.GetTitle().find(topicQuery) != std::string::npos)
        {
            result.push_back(work);
        }
    }
    return result;
}

std::vector<std::unique_ptr<DepartmentEmployee>> Department::FindTeachersByDisciplineAndClassType(
    const std::string& discipline,
    const std::string& classType) const
{
    if (!IsValidNonEmptyText(discipline) || !IsValidNonEmptyText(classType))
    {
        throw std::invalid_argument("Название дисциплины и вид занятия не могут быть пустыми");
    }

    std::vector<std::unique_ptr<DepartmentEmployee>> result;
    for (const auto& emp : employees)
    {
        const Teacher* teacher = dynamic_cast<const Teacher*>(emp.get());
        if (teacher != nullptr && teacher->TeachesClass(discipline, classType))
        {
            result.push_back(teacher->Clone());
        }
    }
    return result;
}

std::vector<std::string> Department::GetClassTypesForDiscipline(const std::string& discipline) const
{
    if (!IsValidNonEmptyText(discipline))
    {
        throw std::invalid_argument("Название дисциплины не может быть пустым");
    }

    std::vector<std::string> types;
    for (const auto& emp : employees)
    {
        const Teacher* teacher = dynamic_cast<const Teacher*>(emp.get());
        if (teacher == nullptr)
        {
            continue;
        }
        const auto teacherTypes = teacher->GetClassTypesByDiscipline(discipline);
        for (const std::string& t : teacherTypes)
        {
            if (std::find(types.begin(), types.end(), t) == types.end())
            {
                types.push_back(t);
            }
        }
    }
    return types;
}

std::string Department::GetEmployeesSummary() const
{
    std::string summary = "=== Сводная информация о работниках кафедры";
    if (!name.empty())
    {
        summary += " \"" + name + "\"";
    }
    summary += " ===\n";
    summary += "Всего работников: " + std::to_string(employees.size()) + "\n";
    summary += "--------------------------------------------------\n";
    if (employees.empty())
    {
        summary += "Работники не зарегистрированы.\n";
        return summary;
    }

    int idx = 1;
    for (const auto& emp : employees)
    {
        summary += std::to_string(idx++) + ". " + (emp ? emp->GetSummary() : std::string("пустой указатель")) + "\n";
    }
    return summary;
}

std::string Department::GetResearchWorksSummary(const std::string& topicFilter) const
{
    std::vector<ResearchWork> list;
    if (topicFilter.empty())
    {
        list = researchWorks;
    }
    else
    {
        list = FindResearchWorksByTopic(topicFilter);
    }

    std::string summary = "=== Научно-исследовательские работы (НИР) кафедры ===\n";
    summary += "Найдено НИР: " + std::to_string(list.size()) + "\n";
    summary += "--------------------------------------------------\n";
    if (list.empty())
    {
        summary += "НИР не найдены.\n";
        return summary;
    }

    int idx = 1;
    for (const ResearchWork& work : list)
    {
        summary += std::to_string(idx++) + ". " + work.GetSummary() + "\n";
    }
    return summary;
}

std::string Department::GetTeacherByDisciplineAndClassTypeSummary(const std::string& discipline,
                                                                const std::string& classType) const
{
    const auto found = FindTeachersByDisciplineAndClassType(discipline, classType);
    std::string summary = "=== Преподаватели по дисциплине \"" + discipline + "\" (" + classType + ") ===\n";
    if (found.empty())
    {
        summary += "Преподаватели по заданным параметрам не найдены.\n";
        return summary;
    }

    int idx = 1;
    for (const auto& emp : found)
    {
        summary += std::to_string(idx++) + ". " + emp->ToString() + "\n";
    }
    return summary;
}

std::string Department::GetClassTypesSummary(const std::string& discipline) const
{
    const auto types = GetClassTypesForDiscipline(discipline);
    std::string summary = "=== Виды занятий по дисциплине \"" + discipline + "\" ===\n";
    if (types.empty())
    {
        summary += "Виды занятий не найдены.\n";
        return summary;
    }

    int idx = 1;
    for (const std::string& t : types)
    {
        summary += std::to_string(idx++) + ". " + t + "\n";
    }
    return summary;
}

size_t Department::GetEmployeeCount() const
{
    return employees.size();
}

size_t Department::GetResearchWorkCount() const
{
    return researchWorks.size();
}
#include "ResearchWork.h"
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

std::set<int> ResearchWork::existingIds;
std::map<int, int> ResearchWork::idRefCount;

ResearchWork::ResearchWork()
    : id(0), title(""), supervisor(""), participants()
{
}

ResearchWork::ResearchWork(const int id,
                           const std::string& title,
                           const std::string& supervisor)
    : id(id), title(title), supervisor(supervisor), participants()
{
    if (this->id <= 0)
    {
        throw std::invalid_argument("ID НИР должен быть больше нуля");
    }
    if (!IsValidNonEmptyText(this->title))
    {
        throw std::invalid_argument("Тема НИР не может быть пустой или содержать управляющие символы");
    }
    if (!IsValidNonEmptyText(this->supervisor))
    {
        throw std::invalid_argument("Руководитель НИР не может быть пустым или содержать управляющие символы");
    }
    if (existingIds.find(this->id) != existingIds.end())
    {
        throw std::invalid_argument("НИР с ID " + std::to_string(this->id) + " уже существует");
    }
    existingIds.insert(this->id);
    idRefCount[this->id] = 1;
}

ResearchWork::~ResearchWork()
{
    if (id > 0)
    {
        auto it = idRefCount.find(id);
        if (it != idRefCount.end() && --it->second <= 0)
        {
            idRefCount.erase(it);
            existingIds.erase(id);
        }
    }
}

ResearchWork::ResearchWork(const ResearchWork& other)
    : id(other.id),
      title(other.title),
      supervisor(other.supervisor),
      participants(other.participants)
{
    if (id > 0)
    {
        idRefCount[id]++;
    }
}

ResearchWork& ResearchWork::operator=(const ResearchWork& other)
{
    if (this != &other)
    {
        if (id > 0)
        {
            auto it = idRefCount.find(id);
            if (it != idRefCount.end() && --it->second <= 0)
            {
                idRefCount.erase(it);
                existingIds.erase(id);
            }
        }

        id = other.id;
        title = other.title;
        supervisor = other.supervisor;
        participants = other.participants;

        if (id > 0)
        {
            idRefCount[id]++;
        }
    }
    return *this;
}

ResearchWork::ResearchWork(ResearchWork&& other) noexcept
    : id(other.id),
      title(std::move(other.title)),
      supervisor(std::move(other.supervisor)),
      participants(std::move(other.participants))
{
    other.id = 0;
}

ResearchWork& ResearchWork::operator=(ResearchWork&& other) noexcept
{
    if (this != &other)
    {
        if (id > 0)
        {
            auto it = idRefCount.find(id);
            if (it != idRefCount.end() && --it->second <= 0)
            {
                idRefCount.erase(it);
                existingIds.erase(id);
            }
        }

        id = other.id;
        title = std::move(other.title);
        supervisor = std::move(other.supervisor);
        participants = std::move(other.participants);
        other.id = 0;
    }
    return *this;
}

int ResearchWork::GetId() const
{
    return id;
}

void ResearchWork::SetId(const int newId)
{
    if (newId <= 0)
    {
        throw std::invalid_argument("ID НИР должен быть больше нуля");
    }
    if (newId == id)
    {
        return;
    }
    if (existingIds.find(newId) != existingIds.end())
    {
        throw std::invalid_argument("НИР с ID " + std::to_string(newId) + " уже существует");
    }
    if (id > 0)
    {
        auto it = idRefCount.find(id);
        if (it != idRefCount.end() && --it->second <= 0)
        {
            idRefCount.erase(it);
            existingIds.erase(id);
        }
    }
    id = newId;
    existingIds.insert(id);
    idRefCount[id] = 1;
}

const std::string& ResearchWork::GetTitle() const
{
    return title;
}

void ResearchWork::SetTitle(const std::string& newTitle)
{
    if (!IsValidNonEmptyText(newTitle))
    {
        throw std::invalid_argument("Тема НИР не может быть пустой или содержать управляющие символы");
    }
    title = newTitle;
}

const std::string& ResearchWork::GetSupervisor() const
{
    return supervisor;
}

void ResearchWork::SetSupervisor(const std::string& newSupervisor)
{
    if (!IsValidNonEmptyText(newSupervisor))
    {
        throw std::invalid_argument("Руководитель НИР не может быть пустым или содержать управляющие символы");
    }
    supervisor = newSupervisor;
}

void ResearchWork::AddParticipant(const std::string& participant)
{
    if (!IsValidNonEmptyText(participant))
    {
        throw std::invalid_argument("Имя исполнителя НИР не может быть пустым или содержать управляющие символы");
    }
    if (std::find(participants.begin(), participants.end(), participant) == participants.end())
    {
        participants.push_back(participant);
    }
}

const std::vector<std::string>& ResearchWork::GetParticipants() const
{
    return participants;
}

bool ResearchWork::IsIdExists(const int searchId)
{
    return existingIds.find(searchId) != existingIds.end();
}

void ResearchWork::ResetRegistry()
{
    existingIds.clear();
    idRefCount.clear();
}

std::string ResearchWork::ToString() const
{
    std::string res = "НИР #" + std::to_string(id) + ": " + title;
    res += " | Руководитель: " + supervisor;
    res += " | Исполнителей: " + std::to_string(participants.size());
    return res;
}

std::string ResearchWork::GetSummary() const
{
    return "НИР #" + std::to_string(id) + " — " + title
        + " (рук.: " + supervisor + ", исп.: " + std::to_string(participants.size()) + ")";
}

bool ResearchWork::operator==(const ResearchWork& other) const
{
    return id == other.id &&
           title == other.title &&
           supervisor == other.supervisor &&
           participants == other.participants;
}

bool ResearchWork::operator!=(const ResearchWork& other) const
{
    return !(*this == other);
}
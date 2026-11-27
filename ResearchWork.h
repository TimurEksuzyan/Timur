/**
 * @file ResearchWork.h
 * @brief Заголовочный файл с объявлением класса научно-исследовательской работы (НИР)
 */

#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

/**
 * @brief Класс для представления научно-исследовательской работы (НИР) кафедры
 */
class ResearchWork
{
private:
    /**
     * @brief Реестр занятых идентификаторов НИР
     */
    static std::set<int> existingIds;

    /**
     * @brief Счетчик ссылок копий на каждый идентификатор НИР
     */
    static std::map<int, int> idRefCount;

    /**
     * @brief Уникальный идентификатор НИР
     */
    int id;

    /**
     * @brief Тема / название НИР
     */
    std::string title;

    /**
     * @brief Руководитель НИР (ФИО)
     */
    std::string supervisor;

    /**
     * @brief Список исполнителей НИР (ФИО)
     */
    std::vector<std::string> participants;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    ResearchWork();

    /**
     * @brief Конструктор с параметрами
     * @param id Уникальный идентификатор НИР (> 0)
     * @param title Тема НИР
     * @param supervisor Руководитель НИР
     * @throws std::invalid_argument При некорректных параметрах или дубликате ID
     */
    ResearchWork(const int id,
                 const std::string& title,
                 const std::string& supervisor);

    /**
     * @brief Деструктор с освобождением идентификатора из реестра
     */
    ~ResearchWork();

    /**
     * @brief Конструктор копирования
     * @param other Копируемая НИР
     */
    ResearchWork(const ResearchWork& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемая НИР
     * @return Ссылка на текущий объект
     */
    ResearchWork& operator=(const ResearchWork& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемая НИР
     */
    ResearchWork(ResearchWork&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемая НИР
     * @return Ссылка на текущий объект
     */
    ResearchWork& operator=(ResearchWork&& other) noexcept;

    /**
     * @brief Получить идентификатор НИР
     * @return Идентификатор НИР
     */
    int GetId() const;

    /**
     * @brief Установить идентификатор НИР с проверкой уникальности
     * @param newId Новый идентификатор (> 0)
     * @throws std::invalid_argument При неположительном или занятом идентификаторе
     */
    void SetId(const int newId);

    /**
     * @brief Получить тему НИР
     * @return Константная ссылка на тему НИР
     */
    const std::string& GetTitle() const;

    /**
     * @brief Установить тему НИР
     * @param newTitle Новая тема НИР
     * @throws std::invalid_argument Если тема пуста или содержит управляющие символы
     */
    void SetTitle(const std::string& newTitle);

    /**
     * @brief Получить руководителя НИР
     * @return Константная ссылка на руководителя НИР
     */
    const std::string& GetSupervisor() const;

    /**
     * @brief Установить руководителя НИР
     * @param newSupervisor Новый руководитель НИР
     * @throws std::invalid_argument Если имя руководителя пусто или содержит управляющие символы
     */
    void SetSupervisor(const std::string& newSupervisor);

    /**
     * @brief Добавить исполнителя НИР
     * @param participant ФИО исполнителя
     * @throws std::invalid_argument Если имя исполнителя некорректно
     */
    void AddParticipant(const std::string& participant);

    /**
     * @brief Получить список исполнителей НИР
     * @return Константная ссылка на вектор исполнителей
     */
    const std::vector<std::string>& GetParticipants() const;

    /**
     * @brief Проверить, занят ли указанный идентификатор НИР
     * @param searchId Идентификатор для проверки
     * @return true, если занят, иначе false
     */
    static bool IsIdExists(const int searchId);

    /**
     * @brief Очистить статический реестр занятых идентификаторов
     */
    static void ResetRegistry();

    /**
     * @brief Полная строковая информация о НИР
     * @return Строка с подробным описанием НИР
     */
    std::string ToString() const;

    /**
     * @brief Сводная информация о НИР
     * @return Краткая строка для отчетов
     */
    std::string GetSummary() const;

    /**
     * @brief Оператор проверки равенства НИР
     * @param other НИР для сравнения
     * @return true, если объекты равны, иначе false
     */
    bool operator==(const ResearchWork& other) const;

    /**
     * @brief Оператор проверки неравенства НИР
     * @param other НИР для сравнения
     * @return true, если объекты не равны, иначе false
     */
    bool operator!=(const ResearchWork& other) const;
};
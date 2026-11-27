/**
 * @file Department.h
 * @brief Заголовочный файл с объявлением класса кафедры для управления работниками и НИР
 */

#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "DepartmentEmployee.h"
#include "ResearchWork.h"

/**
 * @brief Класс для представления кафедры и выполнения запросов по работникам, НИР и занятиям
 */
class Department
{
private:
    /**
     * @brief Название кафедры
     */
    std::string name;

    /**
     * @brief Полиморфная коллекция работников кафедры (преподаватели и инженеры)
     */
    std::vector<std::unique_ptr<DepartmentEmployee>> employees;

    /**
     * @brief Коллекция научно-исследовательских работ (НИР) кафедры
     */
    std::vector<ResearchWork> researchWorks;

    /**
     * @brief Счетчик для генерации идентификаторов новых НИР
     */
    int nextResearchId;

    /**
     * @brief Вспомогательный метод глубокого копирования коллекции работников
     * @param source Исходная коллекция работников
     * @return Новая коллекция клонов
     */
    static std::vector<std::unique_ptr<DepartmentEmployee>> CloneEmployees(
        const std::vector<std::unique_ptr<DepartmentEmployee>>& source);

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Department();

    /**
     * @brief Конструктор с параметрами
     * @param name Название кафедры
     * @throws std::invalid_argument При некорректном названии кафедры
     */
    explicit Department(const std::string& name);

    /**
     * @brief Деструктор по умолчанию
     */
    ~Department() = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемая кафедра
     */
    Department(const Department& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемая кафедра
     * @return Ссылка на текущий объект
     */
    Department& operator=(const Department& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемая кафедра
     */
    Department(Department&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемая кафедра
     * @return Ссылка на текущий объект
     */
    Department& operator=(Department&& other) noexcept;

    /**
     * @brief Получить название кафедры
     * @return Константная ссылка на название кафедры
     */
    const std::string& GetName() const;

    /**
     * @brief Установить название кафедры
     * @param newName Новое название кафедры
     * @throws std::invalid_argument Если название пусто или содержит управляющие символы
     */
    void SetName(const std::string& newName);

    /**
     * @brief Добавить работника кафедры (преподавателя или инженера)
     * @param employee Объект работника
     * @throws std::invalid_argument Если работник с таким ID уже зарегистрирован
     */
    void AddEmployee(const DepartmentEmployee& employee);

    /**
     * @brief Зарегистрировать научно-исследовательскую работу (НИР)
     * @param title Тема НИР
     * @param supervisor Руководитель НИР
     * @return Созданный объект НИР
     */
    ResearchWork RegisterResearchWork(const std::string& title, const std::string& supervisor);

    /**
     * @brief Добавить существующий объект НИР в кафедру
     * @param work Объект НИР
     * @throws std::invalid_argument Если НИР с таким ID уже добавлена на кафедру
     */
    void AddResearchWork(const ResearchWork& work);

    /**
     * @brief Получить всех работников кафедры
     * @return Константная ссылка на вектор умных указателей на работников
     */
    const std::vector<std::unique_ptr<DepartmentEmployee>>& GetEmployees() const;

    /**
     * @brief Получить все НИР кафедры
     * @return Константная ссылка на вектор НИР
     */
    const std::vector<ResearchWork>& GetResearchWorks() const;

    /**
     * @brief Найти НИР по фрагменту или точному совпадению темы
     * @param topicQuery Строка поиска по теме НИР
     * @return Вектор подходящих НИР
     * @throws std::invalid_argument Если строка поиска пуста или содержит управляющие символы
     */
    std::vector<ResearchWork> FindResearchWorksByTopic(const std::string& topicQuery) const;

    /**
     * @brief Найти преподавателей, ведущих указанный вид занятий по указанной дисциплине
     * @param discipline Название дисциплины
     * @param classType Вид занятия
     * @return Вектор копий подходящих преподавателей
     * @throws std::invalid_argument Если дисциплина или вид занятия пусты
     */
    std::vector<std::unique_ptr<DepartmentEmployee>> FindTeachersByDisciplineAndClassType(
        const std::string& discipline,
        const std::string& classType) const;

    /**
     * @brief Получить список видов занятий, проводимых по выбранной дисциплине
     * @param discipline Название дисциплины
     * @return Вектор уникальных видов занятий по дисциплине
     * @throws std::invalid_argument Если название дисциплины пусто
     */
    std::vector<std::string> GetClassTypesForDiscipline(const std::string& discipline) const;

    /**
     * @brief Получить сводную информацию обо всех работниках кафедры
     * @return Форматированная строка отчета
     */
    std::string GetEmployeesSummary() const;

    /**
     * @brief Получить сводную информацию о НИР (всех или по теме)
     * @param topicFilter Фильтр по теме (пустая строка — все НИР)
     * @return Форматированная строка отчета
     */
    std::string GetResearchWorksSummary(const std::string& topicFilter = "") const;

    /**
     * @brief Получить информацию о преподавателе, ведущем указанный вид занятий по дисциплине
     * @param discipline Название дисциплины
     * @param classType Вид занятия
     * @return Форматированная строка результата
     */
    std::string GetTeacherByDisciplineAndClassTypeSummary(const std::string& discipline,
                                                         const std::string& classType) const;

    /**
     * @brief Получить информацию о видах занятий по выбранной дисциплине
     * @param discipline Название дисциплины
     * @return Форматированная строка результата
     */
    std::string GetClassTypesSummary(const std::string& discipline) const;

    /**
     * @brief Получить количество работников кафедры
     * @return Количество работников
     */
    size_t GetEmployeeCount() const;

    /**
     * @brief Получить количество НИР кафедры
     * @return Количество НИР
     */
    size_t GetResearchWorkCount() const;
};
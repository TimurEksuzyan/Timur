/**
 * @file Teacher.h
 * @brief Заголовочный файл с объявлением класса преподавателя кафедры
 */

#pragma once

#include <string>
#include <utility>
#include <vector>
#include "DepartmentEmployee.h"

/**
 * @brief Класс для представления преподавателя кафедры
 */
class Teacher : public DepartmentEmployee
{
private:
    /**
     * @brief Ученая степень или звание преподавателя
     */
    std::string academicDegree;

    /**
     * @brief Список занятий преподавателя (пара: название дисциплины, вид занятия)
     */
    std::vector<std::pair<std::string, std::string>> teachingLoad;

    /**
     * @brief Список тем НИР преподавателя
     */
    std::vector<std::string> researchTopics;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Teacher();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор преподавателя
     * @param surname Фамилия
     * @param name Имя
     * @param patronymic Отчество
     * @param position Должность
     * @param academicDegree Ученая степень или звание
     * @throws std::invalid_argument При некорректных параметрах
     */
    Teacher(const std::string& id,
            const std::string& surname,
            const std::string& name,
            const std::string& patronymic,
            const std::string& position,
            const std::string& academicDegree);

    /**
     * @brief Виртуальный деструктор по умолчанию
     */
    virtual ~Teacher() override = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый преподаватель
     */
    Teacher(const Teacher& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый преподаватель
     * @return Ссылка на текущий объект
     */
    Teacher& operator=(const Teacher& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый преподаватель
     */
    Teacher(Teacher&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый преподаватель
     * @return Ссылка на текущий объект
     */
    Teacher& operator=(Teacher&& other) noexcept;

    /**
     * @brief Получить ученую степень или звание
     * @return Константная ссылка на степень или звание
     */
    const std::string& GetAcademicDegree() const;

    /**
     * @brief Установить ученую степень или звание
     * @param newDegree Новая степень или звание
     * @throws std::invalid_argument Если строка содержит управляющие символы
     */
    void SetAcademicDegree(const std::string& newDegree);

    /**
     * @brief Добавить занятие по дисциплине
     * @param discipline Название дисциплины
     * @param classType Вид занятия (лекции, лабораторные работы, практики и т.д.)
     * @throws std::invalid_argument Если название дисциплины или вид занятия некорректны
     */
    void AddTeachingActivity(const std::string& discipline, const std::string& classType);

    /**
     * @brief Получить список занятий преподавателя
     * @return Константная ссылка на вектор пар (дисциплина, вид занятия)
     */
    const std::vector<std::pair<std::string, std::string>>& GetTeachingLoad() const;

    /**
     * @brief Проверить, ведет ли преподаватель указанный вид занятия по дисциплине
     * @param discipline Название дисциплины
     * @param classType Вид занятия
     * @return true, если ведет, иначе false
     */
    bool TeachesClass(const std::string& discipline, const std::string& classType) const;

    /**
     * @brief Получить список видов занятий преподавателя по выбранной дисциплине
     * @param discipline Название дисциплины
     * @return Вектор видов занятий по данной дисциплине
     */
    std::vector<std::string> GetClassTypesByDiscipline(const std::string& discipline) const;

    /**
     * @brief Добавить тему НИР
     * @param topic Название темы НИР
     * @throws std::invalid_argument Если тема пуста или содержит управляющие символы
     */
    void AddResearchTopic(const std::string& topic);

    /**
     * @brief Получить список тем НИР преподавателя
     * @return Константная ссылка на вектор тем НИР
     */
    const std::vector<std::string>& GetResearchTopics() const;

    /**
     * @brief Получить вид работника кафедры
     * @return EmployeeRole::Teacher
     */
    EmployeeRole GetRole() const override;

    /**
     * @brief Создать полиморфную копию преподавателя
     * @return Умный указатель на копию
     */
    std::unique_ptr<DepartmentEmployee> Clone() const override;

    /**
     * @brief Проверить равенство с другим работником кафедры
     * @param other Другой работник кафедры
     * @return true, если объекты равны, иначе false
     */
    bool Equals(const DepartmentEmployee& other) const override;

    /**
     * @brief Полная строковая информация о преподавателе
     * @return Строка с подробной информацией
     */
    std::string ToString() const override;

    /**
     * @brief Сводная информация о преподавателе
     * @return Строка со сводкой для отчетов
     */
    std::string GetSummary() const override;

    /**
     * @brief Оператор проверки равенства преподавателей
     * @param other Преподаватель для сравнения
     * @return true, если объекты равны, иначе false
     */
    bool operator==(const Teacher& other) const;

    /**
     * @brief Оператор проверки неравенства преподавателей
     * @param other Преподаватель для сравнения
     * @return true, если объекты не равны, иначе false
     */
    bool operator!=(const Teacher& other) const;
};
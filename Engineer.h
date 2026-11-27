/**
 * @file Engineer.h
 * @brief Заголовочный файл с объявлением класса инженера кафедры
 */

#pragma once

#include <string>
#include <vector>
#include "DepartmentEmployee.h"

/**
 * @brief Класс для представления инженера кафедры
 */
class Engineer : public DepartmentEmployee
{
private:
    /**
     * @brief Специализация или закрепленное направление работы
     */
    std::string specialization;

    /**
     * @brief Список тем НИР, в которых участвует инженер
     */
    std::vector<std::string> researchTopics;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Engineer();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор инженера
     * @param surname Фамилия
     * @param name Имя
     * @param patronymic Отчество
     * @param position Должность
     * @param specialization Специализация инженера
     * @throws std::invalid_argument При некорректных параметрах
     */
    Engineer(const std::string& id,
             const std::string& surname,
             const std::string& name,
             const std::string& patronymic,
             const std::string& position,
             const std::string& specialization);

    /**
     * @brief Виртуальный деструктор по умолчанию
     */
    virtual ~Engineer() override = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый инженер
     */
    Engineer(const Engineer& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый инженер
     * @return Ссылка на текущий объект
     */
    Engineer& operator=(const Engineer& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый инженер
     */
    Engineer(Engineer&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый инженер
     * @return Ссылка на текущий объект
     */
    Engineer& operator=(Engineer&& other) noexcept;

    /**
     * @brief Получить специализацию инженера
     * @return Константная ссылка на специализацию
     */
    const std::string& GetSpecialization() const;

    /**
     * @brief Установить специализацию инженера
     * @param newSpecialization Новая специализация
     * @throws std::invalid_argument Если строка содержит управляющие символы
     */
    void SetSpecialization(const std::string& newSpecialization);

    /**
     * @brief Добавить тему НИР
     * @param topic Название темы НИР
     * @throws std::invalid_argument Если тема пуста или содержит управляющие символы
     */
    void AddResearchTopic(const std::string& topic);

    /**
     * @brief Получить список тем НИР инженера
     * @return Константная ссылка на вектор тем НИР
     */
    const std::vector<std::string>& GetResearchTopics() const;

    /**
     * @brief Получить вид работника кафедры
     * @return EmployeeRole::Engineer
     */
    EmployeeRole GetRole() const override;

    /**
     * @brief Создать полиморфную копию инженера
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
     * @brief Полная строковая информация об инженере
     * @return Строка с подробной информацией
     */
    std::string ToString() const override;

    /**
     * @brief Сводная информация об инженере
     * @return Строка со сводкой для отчетов
     */
    std::string GetSummary() const override;

    /**
     * @brief Оператор проверки равенства инженеров
     * @param other Инженер для сравнения
     * @return true, если объекты равны, иначе false
     */
    bool operator==(const Engineer& other) const;

    /**
     * @brief Оператор проверки неравенства инженеров
     * @param other Инженер для сравнения
     * @return true, если объекты не равны, иначе false
     */
    bool operator!=(const Engineer& other) const;
};
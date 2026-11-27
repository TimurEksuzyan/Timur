/**
 * @file DepartmentEmployee.h
 * @brief Заголовочный файл с объявлением базового класса работника кафедры
 */

#pragma once

#include <memory>
#include <string>

/**
 * @brief Вид работника кафедры
 */
enum class EmployeeRole
{
    /**
     * @brief Преподаватель
     */
    Teacher,

    /**
     * @brief Инженер
     */
    Engineer
};

/**
 * @brief Преобразовать вид работника кафедры в строковое название
 * @param role Вид работника
 * @return Название вида работника
 * @throws std::invalid_argument При передаче неизвестного вида работника
 */
std::string EmployeeRoleToString(const EmployeeRole role);

/**
 * @brief Абстрактный базовый класс для представления работника кафедры
 */
class DepartmentEmployee
{
protected:
    /**
     * @brief Уникальный идентификатор работника
     */
    std::string id;

    /**
     * @brief Фамилия работника
     */
    std::string surname;

    /**
     * @brief Имя работника
     */
    std::string name;

    /**
     * @brief Отчество работника
     */
    std::string patronymic;

    /**
     * @brief Занимаемая должность
     */
    std::string position;

    /**
     * @brief Конструктор по умолчанию
     */
    DepartmentEmployee();

    /**
     * @brief Конструктор копирования
     * @param other Копируемый работник
     */
    DepartmentEmployee(const DepartmentEmployee& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый работник
     * @return Ссылка на текущий объект
     */
    DepartmentEmployee& operator=(const DepartmentEmployee& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый работник
     */
    DepartmentEmployee(DepartmentEmployee&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый работник
     * @return Ссылка на текущий объект
     */
    DepartmentEmployee& operator=(DepartmentEmployee&& other) noexcept;

    /**
     * @brief Сравнить базовые поля двух работников кафедры
     * @param other Другой работник кафедры
     * @return true, если базовые поля совпадают, иначе false
     */
    bool BaseEquals(const DepartmentEmployee& other) const;

public:
    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор работника
     * @param surname Фамилия работника
     * @param name Имя работника
     * @param patronymic Отчество работника
     * @param position Должность работника
     * @throws std::invalid_argument При некорректных полях работника
     */
    DepartmentEmployee(const std::string& id,
                       const std::string& surname,
                       const std::string& name,
                       const std::string& patronymic,
                       const std::string& position);

    /**
     * @brief Виртуальный деструктор по умолчанию
     */
    virtual ~DepartmentEmployee() = default;

    /**
     * @brief Получить идентификатор работника
     * @return Константная ссылка на идентификатор
     */
    const std::string& GetId() const;

    /**
     * @brief Установить идентификатор работника
     * @param newId Новый идентификатор
     * @throws std::invalid_argument Если идентификатор пуст или содержит управляющие символы
     */
    void SetId(const std::string& newId);

    /**
     * @brief Получить фамилию работника
     * @return Константная ссылка на фамилию
     */
    const std::string& GetSurname() const;

    /**
     * @brief Установить фамилию работника
     * @param newSurname Новая фамилия
     * @throws std::invalid_argument Если фамилия пуста или содержит управляющие символы
     */
    void SetSurname(const std::string& newSurname);

    /**
     * @brief Получить имя работника
     * @return Константная ссылка на имя
     */
    const std::string& GetName() const;

    /**
     * @brief Установить имя работника
     * @param newName Новое имя
     * @throws std::invalid_argument Если имя пусто или содержит управляющие символы
     */
    void SetName(const std::string& newName);

    /**
     * @brief Получить отчество работника
     * @return Константная ссылка на отчество
     */
    const std::string& GetPatronymic() const;

    /**
     * @brief Установить отчество работника
     * @param newPatronymic Новое отчество
     * @throws std::invalid_argument Если отчество содержит управляющие символы
     */
    void SetPatronymic(const std::string& newPatronymic);

    /**
     * @brief Получить должность работника
     * @return Константная ссылка на должность
     */
    const std::string& GetPosition() const;

    /**
     * @brief Установить должность работника
     * @param newPosition Новая должность
     * @throws std::invalid_argument Если должность пуста или содержит управляющие символы
     */
    void SetPosition(const std::string& newPosition);

    /**
     * @brief Получить полное ФИО работника
     * @return Строка формата "Фамилия Имя Отчество"
     */
    std::string GetFullName() const;

    /**
     * @brief Получить вид работника кафедры
     * @return Значение перечисления EmployeeRole
     */
    virtual EmployeeRole GetRole() const = 0;

    /**
     * @brief Создать полиморфную копию работника
     * @return Умный указатель на копию
     */
    virtual std::unique_ptr<DepartmentEmployee> Clone() const = 0;

    /**
     * @brief Проверить равенство с другим работником кафедры с учетом типа
     * @param other Другой работник кафедры
     * @return true, если типы и все поля совпадают, иначе false
     */
    virtual bool Equals(const DepartmentEmployee& other) const = 0;

    /**
     * @brief Полная строковая информация о работнике
     * @return Строка с подробной информацией
     */
    virtual std::string ToString() const = 0;

    /**
     * @brief Сводная информация о работнике
     * @return Строка со сводкой для отчетов
     */
    virtual std::string GetSummary() const = 0;
};
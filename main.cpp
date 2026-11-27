/**
 * @file main.cpp
 * @brief Демонстрационная программа для варианта "Кафедра"
 */

#define NOMINMAX
#include <exception>
#include <iostream>
#include <memory>
#include <vector>
#include <windows.h>
#include "DepartmentEmployee.h"
#include "Teacher.h"
#include "Engineer.h"
#include "ResearchWork.h"
#include "Department.h"

/**
 * @brief Точка входа в демонстрационную программу
 * @return 0 при успешном завершении программы, иначе 1
 */
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    try
    {
        std::vector<std::unique_ptr<DepartmentEmployee>> staff;

        Teacher t1("EMP-01", "Смирнов", "Алексей", "Петрович", "Доцент", "к.т.н.");
        t1.AddTeachingActivity("ООП на C++", "Лекции");
        t1.AddTeachingActivity("ООП на C++", "Лабораторные работы");
        t1.AddResearchTopic("Моделирование распределенных систем");

        Teacher t2("EMP-02", "Кузнецова", "Елена", "Сергеевна", "Старший преподаватель", "б/с");
        t2.AddTeachingActivity("ООП на C++", "Практические занятия");
        t2.AddTeachingActivity("Базы данных", "Лекции");
        t2.AddResearchTopic("Анализ графовых структур");

        Engineer e1("EMP-03", "Волков", "Игорь", "Николаевич", "Ведущий инженер", "Сетевое оборудование и стенды");
        e1.AddResearchTopic("Моделирование распределенных систем");

        Engineer e2("EMP-04", "Морозова", "Ольга", "Андреевна", "Инженер 1 категории", "Диагностика вычислительных кластеров");
        e2.AddResearchTopic("Анализ графовых структур");

        staff.push_back(std::make_unique<Teacher>(t1));
        staff.push_back(std::make_unique<Teacher>(t2));
        staff.push_back(std::make_unique<Engineer>(e1));
        staff.push_back(std::make_unique<Engineer>(e2));

        for (const auto& member : staff)
        {
            std::cout << member->ToString() << "\n";
        }
        std::cout << "\n";

        Department dept("Кафедра программной инженерии");
        for (const auto& member : staff)
        {
            dept.AddEmployee(*member);
        }

        ResearchWork r1 = dept.RegisterResearchWork("Моделирование распределенных систем", "Смирнов Алексей Петрович");
        r1.AddParticipant("Смирнов Алексей Петрович");
        r1.AddParticipant("Волков Игорь Николаевич");

        ResearchWork r2 = dept.RegisterResearchWork("Анализ графовых структур", "Кузнецова Елена Сергеевна");
        r2.AddParticipant("Кузнецова Елена Сергеевна");
        r2.AddParticipant("Морозова Ольга Андреевна");

        dept.AddResearchWork(r1);
        dept.AddResearchWork(r2);

        std::cout << "ЗАДАНИЕ 1\n";
        std::cout << dept.GetEmployeesSummary() << "\n";

        std::cout << "ЗАДАНИЕ 2\n";
        std::cout << dept.GetResearchWorksSummary() << "\n";
        std::cout << dept.GetResearchWorksSummary("распределенных") << "\n";

        std::cout << "ЗАДАНИЕ 3\n";
        std::cout << dept.GetTeacherByDisciplineAndClassTypeSummary("ООП на C++", "Лекции") << "\n";

        std::cout << "ЗАДАНИЕ 4\n";
        std::cout << dept.GetClassTypesSummary("ООП на C++") << "\n";
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Ошибка: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
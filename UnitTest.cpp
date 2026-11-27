/**
 * @file UnitTest.cpp
 * @brief Модульные тесты библиотеки кафедры
 */

#include "CppUnitTest.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "DepartmentEmployee.h"
#include "Teacher.h"
#include "Engineer.h"
#include "ResearchWork.h"
#include "Department.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    /**
     * @brief Тесты базового класса DepartmentEmployee и наследников Teacher / Engineer
     */
    TEST_CLASS(EmployeeHierarchyTests)
    {
    public:
        /**
         * @brief Проверка полиморфизма, клонирования и сравнения
         */
        TEST_METHOD(PolymorphismAndClone_Test)
        {
            std::unique_ptr<DepartmentEmployee> emp1 = std::make_unique<Teacher>(
                "T-1", "Иванов", "Иван", "Иванович", "Доцент", "к.т.н.");
            std::unique_ptr<DepartmentEmployee> emp2 = std::make_unique<Engineer>(
                "E-1", "Петров", "Петр", "Петрович", "Инженер", "Сети");

            Assert::IsTrue(emp1->GetRole() == EmployeeRole::Teacher);
            Assert::IsTrue(emp2->GetRole() == EmployeeRole::Engineer);
            Assert::IsTrue(emp1->ToString().find("Преподаватель") != std::string::npos);
            Assert::IsTrue(emp2->ToString().find("Инженер") != std::string::npos);

            const auto clone1 = emp1->Clone();
            Assert::IsTrue(clone1->Equals(*emp1));
            Assert::IsFalse(clone1->Equals(*emp2));
        }

        /**
         * @brief Проверка правила пяти и валидации для Teacher
         */
        TEST_METHOD(TeacherValidationAndRuleOfFive_Test)
        {
            Teacher t1("T-10", "Сидоров", "Алексей", "Олегович", "Профессор", "д.т.н.");
            t1.AddTeachingActivity("Алгоритмы", "Лекции");
            t1.AddTeachingActivity("Алгоритмы", "Лабораторные");
            t1.AddResearchTopic("Оптимизация компиляторов");

            Assert::IsTrue(t1.TeachesClass("Алгоритмы", "Лекции"));
            Assert::IsFalse(t1.TeachesClass("Алгоритмы", "Практика"));
            Assert::AreEqual(static_cast<size_t>(2), t1.GetClassTypesByDiscipline("Алгоритмы").size());

            Teacher copy(t1);
            Assert::IsTrue(t1 == copy);

            Teacher assigned;
            assigned = t1;
            Assert::IsTrue(t1 == assigned);

            Teacher moved(std::move(copy));
            Assert::AreEqual(std::string("Сидоров Алексей Олегович"), moved.GetFullName());

            Teacher moveAssigned;
            moveAssigned = std::move(assigned);
            Assert::AreEqual(std::string("д.т.н."), moveAssigned.GetAcademicDegree());

            Assert::ExpectException<std::invalid_argument>([]() {
                Teacher bad("", "Сидоров", "Алексей", "Олегович", "Доцент", "к.т.н.");
            });
            Assert::ExpectException<std::invalid_argument>([&]() {
                t1.AddTeachingActivity("", "Лекции");
            });
        }

        /**
         * @brief Проверка правила пяти и валидации для Engineer
         */
        TEST_METHOD(EngineerValidationAndRuleOfFive_Test)
        {
            Engineer e1("E-10", "Орлов", "Дмитрий", "Павлович", "Ведущий инженер", "Микроконтроллеры");
            e1.AddResearchTopic("Встраиваемые системы");

            Engineer copy(e1);
            Assert::IsTrue(e1 == copy);

            Engineer assigned;
            assigned = e1;
            Assert::IsTrue(e1 == assigned);

            Engineer moved(std::move(copy));
            Assert::AreEqual(std::string("Микроконтроллеры"), moved.GetSpecialization());

            Engineer moveAssigned;
            moveAssigned = std::move(assigned);
            Assert::AreEqual(static_cast<size_t>(1), moveAssigned.GetResearchTopics().size());

            Assert::ExpectException<std::invalid_argument>([]() {
                Engineer bad("E-11", "   ", "Дмитрий", "Павлович", "Инженер", "Сети");
            });
        }
    };

    /**
     * @brief Тесты класса ResearchWork
     */
    TEST_CLASS(ResearchWorkTests)
    {
    public:
        /**
         * @brief Проверка создания, уникальности ID и правила пяти ResearchWork
         */
        TEST_METHOD(ResearchWorkValidationAndRuleOfFive_Test)
        {
            ResearchWork::ResetRegistry();
            ResearchWork w1(1, "Робототехника", "Смирнов А. П.");
            w1.AddParticipant("Орлов Д. П.");

            Assert::ExpectException<std::invalid_argument>([&]() {
                ResearchWork dup(1, "Другая тема", "Смирнов А. П.");
            });
            Assert::ExpectException<std::invalid_argument>([&]() {
                ResearchWork badId(0, "Тема", "Руководитель");
            });

            ResearchWork copy(w1);
            Assert::IsTrue(w1 == copy);

            ResearchWork assigned;
            assigned = w1;
            Assert::IsTrue(w1 == assigned);

            ResearchWork moved(std::move(copy));
            Assert::AreEqual(1, moved.GetId());
        }
    };

    /**
     * @brief Тесты класса Department и всех четырех заданий варианта 6
     */
    TEST_CLASS(DepartmentTests)
    {
    public:
        /**
         * @brief Проверка Задания 1: сводная информация о работниках кафедры
         */
        TEST_METHOD(Task1_EmployeesSummary_Test)
        {
            Department dept("Кафедра ИТ");
            Teacher t("T-1", "Иванов", "Иван", "Иванович", "Доцент", "к.т.н.");
            Engineer e("E-1", "Петров", "Петр", "Петрович", "Инженер", "Стенды");
            dept.AddEmployee(t);
            dept.AddEmployee(e);

            Assert::AreEqual(static_cast<size_t>(2), dept.GetEmployeeCount());
            const std::string summary = dept.GetEmployeesSummary();
            Assert::IsTrue(summary.find("Иванов Иван Иванович") != std::string::npos);
            Assert::IsTrue(summary.find("Петров Петр Петрович") != std::string::npos);
        }

        /**
         * @brief Проверка Задания 2: информация о НИР
         */
        TEST_METHOD(Task2_ResearchWorks_Test)
        {
            ResearchWork::ResetRegistry();
            Department dept("Кафедра ИТ");
            ResearchWork w1 = dept.RegisterResearchWork("Нейросети в медицине", "Иванов И. И.");
            ResearchWork w2 = dept.RegisterResearchWork("Квантовая криптография", "Петров П. П.");
            (void)w1;
            (void)w2;

            const auto found = dept.FindResearchWorksByTopic("Нейросети");
            Assert::AreEqual(static_cast<size_t>(1), found.size());
            Assert::AreEqual(std::string("Нейросети в медицине"), found[0].GetTitle());
            Assert::IsTrue(dept.GetResearchWorksSummary().find("Квантовая криптография") != std::string::npos);
        }

        /**
         * @brief Проверка Задания 3: поиск преподавателя по дисциплине и виду занятий
         */
        TEST_METHOD(Task3_TeacherByDisciplineAndClassType_Test)
        {
            Department dept("Кафедра ИТ");
            Teacher t1("T-1", "Иванов", "Иван", "Иванович", "Доцент", "к.т.н.");
            t1.AddTeachingActivity("C++", "Лекции");
            Teacher t2("T-2", "Смирнова", "Анна", "Сергеевна", "Ассистент", "");
            t2.AddTeachingActivity("C++", "Лабораторные работы");

            dept.AddEmployee(t1);
            dept.AddEmployee(t2);

            const auto found = dept.FindTeachersByDisciplineAndClassType("C++", "Лекции");
            Assert::AreEqual(static_cast<size_t>(1), found.size());
            Assert::AreEqual(std::string("Иванов Иван Иванович"), found[0]->GetFullName());
            Assert::IsTrue(dept.GetTeacherByDisciplineAndClassTypeSummary("C++", "Лекции")
                .find("Иванов Иван Иванович") != std::string::npos);
        }

        /**
         * @brief Проверка Задания 4: виды занятий по выбранной дисциплине
         */
        TEST_METHOD(Task4_ClassTypesForDiscipline_Test)
        {
            Department dept("Кафедра ИТ");
            Teacher t1("T-1", "Иванов", "Иван", "Иванович", "Доцент", "к.т.н.");
            t1.AddTeachingActivity("C++", "Лекции");
            t1.AddTeachingActivity("C++", "Лабораторные работы");
            Teacher t2("T-2", "Смирнова", "Анна", "Сергеевна", "Ассистент", "");
            t2.AddTeachingActivity("C++", "Лабораторные работы");
            t2.AddTeachingActivity("C++", "Практики");

            dept.AddEmployee(t1);
            dept.AddEmployee(t2);

            const auto types = dept.GetClassTypesForDiscipline("C++");
            Assert::AreEqual(static_cast<size_t>(3), types.size());
            Assert::IsTrue(dept.GetClassTypesSummary("C++").find("Практики") != std::string::npos);
        }

        /**
         * @brief Проверка правила пяти для Department
         */
        TEST_METHOD(DepartmentRuleOfFive_Test)
        {
            ResearchWork::ResetRegistry();
            Department d1("Исходная кафедра");
            Teacher t("T-1", "Иванов", "Иван", "Иванович", "Доцент", "к.т.н.");
            d1.AddEmployee(t);
            d1.RegisterResearchWork("Тема 1", "Иванов И. И.");

            Department d2(d1);
            Assert::AreEqual(d1.GetEmployeeCount(), d2.GetEmployeeCount());
            Assert::AreEqual(d1.GetResearchWorkCount(), d2.GetResearchWorkCount());

            Department d3;
            d3 = d1;
            Assert::AreEqual(d1.GetEmployeeCount(), d3.GetEmployeeCount());

            Department d4(std::move(d2));
            Assert::AreEqual(static_cast<size_t>(1), d4.GetEmployeeCount());

            Department d5;
            d5 = std::move(d3);
            Assert::AreEqual(static_cast<size_t>(1), d5.GetResearchWorkCount());
        }
    };
}
#include "pch.h"
#include "CppUnitTest.h"
#include "../lab10.3.cpp"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestSortByZodiac)
        {
            int size = 3;
            Zodiac* people = new Zodiac[size];

            // Додаємо тестові дані
            people[0] = { "Ivanov", "Ivan", "Leo", {15, 8, 1990} };
            people[1] = { "Petrov", "Petro", "Aries", {10, 4, 1985} };
            people[2] = { "Sidorov", "Sidor", "Cancer", {20, 6, 1970} };

            sortByZodiac(people, size);

            // Перевірка, чи відсортовано за знаком Зодіаку
            Assert::AreEqual(people[0].zodiac_sign, string("Aries"));
            Assert::AreEqual(people[1].zodiac_sign, string("Cancer"));
            Assert::AreEqual(people[2].zodiac_sign, string("Leo"));

            // Очищення
            delete[] people;
        }

        TEST_METHOD(TestDisplayByMonth)
        {
            int size = 3;
            Zodiac* people = new Zodiac[size];

            // Додаємо тестові дані
            people[0] = { "Ivanov", "Ivan", "Leo", {15, 8, 1990} };
            people[1] = { "Petrov", "Petro", "Aries", {10, 4, 1985} };
            people[2] = { "Sidorov", "Sidor", "Cancer", {20, 6, 1970} };

            // Перевірка місяця 4 (квітень)
            std::stringstream buffer;
            std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

            displayByMonth(people, size, 4);

            std::cout.rdbuf(oldCout);
            string output = buffer.str();

            // Перевірка, що був знайдений запис з квітня
            Assert::IsTrue(output.find("Petrov") != string::npos);

            // Очищення
            delete[] people;
        }

        TEST_METHOD(TestSaveToFileAndLoadFromFile)
        {
            int size = 2;
            Zodiac* people = new Zodiac[size];

            // Додаємо тестові дані
            people[0] = { "Ivanov", "Ivan", "Leo", {15, 8, 1990} };
            people[1] = { "Petrov", "Petro", "Aries", {10, 4, 1985} };

            string filename = "testfile.txt";

            // Збереження у файл
            saveToFile(people, size, filename);

            // Створення нового масиву і завантаження з файлу
            Zodiac* loadedPeople = nullptr;
            int loadedSize = 0;
            loadFromFile(loadedPeople, loadedSize, filename);

            // Перевірка, чи завантажені дані збігаються з оригіналом
            Assert::AreEqual(size, loadedSize);
            Assert::AreEqual(people[0].surname, loadedPeople[0].surname);
            Assert::AreEqual(people[1].surname, loadedPeople[1].surname);

            // Очищення
            delete[] people;
            delete[] loadedPeople;

            // Видалення тестового файлу
            std::remove(filename.c_str());
        }
    };
}

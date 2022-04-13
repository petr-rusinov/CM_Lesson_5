#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

//=======================================================================================================================
//          TASK 1
//=======================================================================================================================

// Создать шаблонную функцию, которая принимает итераторы на начало и конец
// последовательности слов, и выводящую в консоль список уникальных слов(если слово
// повторяется больше 1 раза, то вывести его надо один раз).Продемонстрировать работу
// функции, передав итераторы различных типов.

template <class T, class IT>
void uniqueShow(IT first, IT last)
{
    set<T> tempSet;

    for (IT it = first; it != last; ++it)
        tempSet.insert(*it);

    copy(tempSet.begin(), tempSet.end(), ostream_iterator<T>(cout, " "));
    cout << endl;
}

void task_1()
{
    vector<int> vec{ 1, 1, 2, 2, 2, 3, 2, 3, 3, 3, 4, 4, 5, 6 , 6, 4, 5, 3, 3 };
    uniqueShow<int>(vec.begin(), vec.end());

    vector<string> vec2{ "one", "one", "two", "two", "two", "one", "three", "three", "three", "four", "five", "six" };
    uniqueShow<string>(vec2.begin(), vec2.end());

    multiset<string> ms{ "one", "one", "two", "two", "two", "one", "three", "three", "three", "four", "five", "six" };
    uniqueShow<string>(ms.begin(), ms.end());
}


//=======================================================================================================================
//          TASK 2
//=======================================================================================================================
// Используя ассоциативный контейнер, напишите программу, которая будет считывать данные
// введенные пользователем из стандартного потока ввода и разбивать их на предложения.
// 
// Далее программа должна вывести пользователю все предложения, а также количество слов в
// них, отсортировав предложения по количеству слов.
//=======================================================================================================================

size_t wordsCount(const string& str)
{
    size_t count = 0;
    size_t pos = 0;
    string tempStr(str);
    //убираем запятые
    auto end = remove_if(tempStr.begin(), tempStr.end(), [](auto sym) { if (sym == ',') return true; else return false; });
    tempStr = string(tempStr.begin(), end);
    end = unique(tempStr.begin(), tempStr.end(), [](char l, char r) { return isspace(l) && isspace(r); });
    tempStr = string(tempStr.begin(), end);

    while (tempStr.length() != 0)
    {
        if (tempStr[0] == ' ')
            tempStr.erase(0, 1);
        else
            break;
    }

    for_each(tempStr.begin(), tempStr.end(), [&](char sym) {
        if (sym == ' ' || sym == '.') 
            ++count; });
    return count;
}

void task_2()
{
    setlocale(LC_ALL, "Russian");

    string inputStr = "";
    multimap<int, string> sentenses;

    size_t pos = 0;

    //Тестовые строки:
    inputStr = "qqq,    www,   eee. rrr  yy";
    inputStr = "Варкалось. Хливкие шорьки пырялись по наве. И хрюкотали зелюки, как мюмзики в мове";


    inputStr = "";

    //Ввод из потока
    cout << "Введите текст: " << endl;
    getline(cin, inputStr);

    cout << "Введено: ";
    cout << inputStr << endl << endl;

    //ищем все точки
    do
    {
        pos = inputStr.find('.');
        if (pos != inputStr.npos)
        {
            string str = inputStr.substr(0, pos + 1);
            sentenses.insert({ wordsCount(str), str });
            inputStr.erase(0, pos + 1);
        }
    } while (pos != inputStr.npos);
    sentenses.insert({ wordsCount(inputStr), inputStr });

    for_each(sentenses.begin(), sentenses.end(), [](pair<int, string> item) 
                                                    { if (item.second.length() != 0) 
                                                        cout << item.first << "\t" << item.second << endl; 
                                                    });
}

int main()
{
    task_1();
    task_2();
}

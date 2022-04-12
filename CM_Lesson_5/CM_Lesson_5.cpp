
#include <iostream>
#include <iterator>
#include <set>

using namespace std;

template <class InputIt, class T>
void uniqueWords(InputIt first, InputIt last)
{
    set<T> tempSet;

    for (; first != last; ++first)
    {
        tempSet.insert(*first);
    }

    copy(tempSet.begin(), tempSet.end(), ostream_iterator<T>(cout, " "));
}


int main()
{
    std::cout << "Hello World!\n";
}

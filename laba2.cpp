
#include <algorithm>
#include <cctype>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

namespace {

template <typename Container>
void PrintContainer(const Container& c, const std::string& name) {
  std::cout << name << ": ";
  for (const auto& el : c) {
    std::cout << el << " ";
  }
  std::cout << "\n";
}

// Чтение массива с проверкой на правильность ввода
template <typename Container>
void ReadContainer(Container& c, int n) {
  std::cout << "Enter " << n << " elements: ";
  for (int i = 0; i < n; ++i) {
    typename Container::value_type val{};
    std::cin >> val;
    c.push_back(val);
  }
}

// Задание 1. Задача 5

void Task1_5() {
  std::cout << "\n--- Task 1.5 ---\n";
  int n = 0;
  
  // Проверка ввода
  while (true) {
    std::cout << "Enter number of elements: ";
    std::cin >> n;
    
    if (n > 0 && n % 3 == 0) {
      break; 
    }
    std::cout << "Error: number must be positive and divisible by 3.\n";
  }

  std::list<int> l;
  ReadContainer(l, n);

  int third = n / 3;
  auto it = l.begin();

  // Первая треть (в исходном порядке)
  std::cout << "First third: ";
  for (int i = 0; i < third; ++i, ++it) std::cout << *it << " ";
  std::cout << "\n";

  // Вторая треть (в обратном порядке)
  std::cout << "Second third: ";
  auto it2_start = it;
  std::advance(it, third);
  auto it2_end = it;
  while (it2_end != it2_start) {
    --it2_end;
    std::cout << *it2_end << " ";
  }
  std::cout << "\n";

  // Последняя треть (в обратном порядке)
  std::cout << "Last third: ";
  auto it3_end = l.end();
  while (it3_end != it) {
    --it3_end;
    std::cout << *it3_end << " ";
  }
  std::cout << "\n";
}

// Задание 2. Задача 5

void Task2_5() {
  std::cout << "\n--- Task 2.5 ---\n";
  int n_d = 0;
  
  // Проверка размера 
  while (true) {
    std::cout << "Enter size of deque D (>=5): ";
    std::cin >> n_d;
    if (n_d >= 5) break;
    std::cout << "Error: size must be at least 5.\n";
  }
  
  std::deque<int> d;
  ReadContainer(d, n_d);

  int n_l = 0;
  
  while (true) {
    std::cout << "Enter size of list L (>=5): ";
    std::cin >> n_l;
    if (n_l >= 5) break;
    std::cout << "Error: size must be at least 5.\n";
  }
  
  std::list<int> l;
  ReadContainer(l, n_l);

  // Берем последние 5 элементов дека в обратном порядке
  std::vector<int> temp;
  auto d_it = d.rbegin();
  for (int i = 0; i < 5; ++i, ++d_it) {
    temp.push_back(*d_it);
  }

  // Находим 5-й с конца элемент списка L
  auto l_pos = l.end();
  std::advance(l_pos, -5);

  // Вставляем перед ним
  l.insert(l_pos, temp.begin(), temp.end());

  PrintContainer(l, "Modified L");
}

// Задание 3. Задача 11

void Task3_11() {
  std::cout << "\n--- Task 3.11 ---\n";
  int n = 0;
  
  // Проверка размера
  while (true) {
    std::cout << "Enter size for lists: ";
    std::cin >> n;
    if (n > 0) break;
    std::cout << "Error: size must be positive.\n";
  }

  std::list<int> l1;
  std::list<int> l2;
  std::cout << "Enter L1: ";
  for (int i = 0; i < n; ++i) { int v = 0; std::cin >> v; l1.push_back(v); }
  std::cout << "Enter L2: ";
  for (int i = 0; i < n; ++i) { int v = 0; std::cin >> v; l2.push_back(v); }

  auto i1 = l1.begin();
  auto i2 = l2.begin();

  for (int i = 0; i < n; ++i) {
    // Перемещаем элемент из L1 в L2 после текущего i2
    l2.splice(i2++, l1, i1++);  }

  PrintContainer(l2, "Combined L2");
}

// Задание 4. Задача 5

void Task4_5() {
  std::cout << "\n--- Task 4.5 ---\n";
  std::string input;
  std::cout << "Enter characters: ";
  std::cin >> input;

  std::vector<char> v(input.begin(), input.end());
  std::vector<char> result;

  // Заменяем цифры на '_'
  std::replace_copy_if(
      v.begin(), v.end(), std::back_inserter(result),
      [](char c) { return std::isdigit(static_cast<unsigned char>(c)); }, '_');

  std::cout << "Result: ";
  for (char c : result) std::cout << c;
  std::cout << "\n";
}

// Задание 5. Задача 5

void Task5_5() {
  std::cout << "\n--- Task 5.5 ---\n";
  int n = 0;
  
  // Проверка размера
  while (true) {
    std::cout << "Enter size of list L: ";
    std::cin >> n;
    if (n > 0) break;
    std::cout << "Error: size must be positive.\n";
  }
  
  std::list<int> l;
  ReadContainer(l, n);

  // Вставить 0 после первого отрицательного
  auto it_neg = std::find_if(l.begin(), l.end(), [](int x) { return x < 0; });
  if (it_neg != l.end()) {
    l.insert(++it_neg, 0);
  }

  // Вставить 0 перед последним положительным
  auto it_pos = std::find_if(l.rbegin(), l.rend(), [](int x) { return x > 0; });
  if (it_pos != l.rend()) {
    l.insert(it_pos.base(), 0);
  }

  PrintContainer(l, "Modified L");
}

// Задание 6. Задача 5

void Task6_5() {
  std::cout << "\n--- Task 6.5 ---\n";
  int n = 0;
  
  // Проверка чётности
  while (true) {
    std::cout << "Enter even size for lists: ";
    std::cin >> n;
    if (n > 0 && n % 2 == 0) break;
    std::cout << "Error: size must be positive and even.\n";
  }

  std::list<int> l1;
  std::list<int> l2;
  std::cout << "Enter L1: ";
  for (int i = 0; i < n; ++i) { int v = 0; std::cin >> v; l1.push_back(v); }
  std::cout << "Enter L2: ";
  for (int i = 0; i < n; ++i) { int v = 0; std::cin >> v; l2.push_back(v); }

  auto mid1 = l1.begin();
  std::advance(mid1, n / 2);
  std::swap_ranges(l1.begin(), mid1, mid1);

  auto mid2 = l2.begin();
  std::advance(mid2, n / 2);
  std::rotate(l2.begin(), mid2, l2.end());

  PrintContainer(l1, "L1 after swap_ranges");
  PrintContainer(l2, "L2 after rotate");
}

// Задание 7. Задача 2

void Task7_2() {
  std::cout << "\n--- Task 7.2 ---\n";
  int n = 0;
  
  // Проверка размера 
  while (true) {
    std::cout << "Enter size of vector V (>=3): ";
    std::cin >> n;
    if (n >= 3) break;
    std::cout << "Error: size must be at least 3.\n";
  }
  
  std::vector<int> v;
  ReadContainer(v, n);

  std::partial_sort(v.begin(), v.begin() + 3, v.end());

  std::cout << "First 3 elements after partial_sort: ";
  std::copy(v.begin(), v.begin() + 3, std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
}

// Задание 8. Задача 2

void Task8_2() {
  std::cout << "\n--- Task 8.2 ---\n";
  int n = 0;
  
  // Проверка размера 
  while (true) {
    std::cout << "Enter number of words (>=2): ";
    std::cin >> n;
    if (n >= 2) break;
    std::cout << "Error: need at least 2 words for adjacent_difference.\n";
  }
  
  std::list<std::string> l;
  std::cout << "Enter words: ";
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    l.push_back(s);
  }

  std::deque<std::string> d;
  std::adjacent_difference(
      l.begin(), l.end(), std::back_inserter(d),
      [](const std::string& right, const std::string& left) {
        return std::string(1, left.front()) + std::string(1, right.back());
      });

  d.erase(d.begin()); // Удаляем первый скопированный элемент

  PrintContainer(d, "Resulting deque D");
}

// Задание 9. Задача 1

void Task9_1() {
  std::cout << "\n--- Task 9.1 ---\n";
  int size_v0 = 0;
  
  // Проверка размера 
  while (true) {
    std::cout << "Enter size of V0: ";
    std::cin >> size_v0;
    if (size_v0 > 0) break;
    std::cout << "Error: size must be positive.\n";
  }
  
  std::vector<int> v0;
  ReadContainer(v0, size_v0);

  int n = 0;
  
  // Проверка количества векторов
  while (true) {
    std::cout << "Enter number of vectors N: ";
    std::cin >> n;
    if (n > 0) break;
    std::cout << "Error: N must be positive.\n";
  }

  std::vector<std::vector<int>> vectors(n);
  for (int i = 0; i < n; ++i) {
    int size_v = 0;
    while (true) {
      std::cout << "Enter size of V" << i + 1 << ": ";
      std::cin >> size_v;
      if (size_v > 0) break;
      std::cout << "Error: size must be positive.\n";
    }
    ReadContainer(vectors[i], size_v);
  }

  std::set<int> set_v0(v0.begin(), v0.end());
  int count = 0;

  for (const auto& v : vectors) {
    std::set<int> current_set(v.begin(), v.end());
    if (std::includes(current_set.begin(), current_set.end(), set_v0.begin(),
                      set_v0.end())) {
      ++count;
    }
  }

  std::cout << "Count: " << count << "\n";
}

// Задание 10. Задача 1

void Task10_1() {
  std::cout << "\n--- Task 10.1 ---\n";
  int n = 0;
  
  // Проверка размера 
  while (true) {
    std::cout << "Enter size of vector V: ";
    std::cin >> n;
    if (n > 0) break;
    std::cout << "Error: size must be positive.\n";
  }

  std::vector<int> v;
  ReadContainer(v, n);

  std::map<int, int> m;

  for (int x : v) {
    ++m[x];
  }

  std::cout << "Occurrences:\n";
  for (const auto& pair : m) {
    std::cout << pair.first << " -> " << pair.second << "\n";
  }
}

} 

int main() {
  Task1_5();
  Task2_5();
  Task3_11();
  Task4_5();
  Task5_5();
  Task6_5();
  Task7_2();
  Task8_2();
  Task9_1();
  Task10_1();

  return 0;
}
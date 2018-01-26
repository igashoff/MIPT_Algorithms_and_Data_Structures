//
//  main.cpp
//  #
//
//  Created by Igashov_Ilya on 02.05.16.
//  Copyright (c) 2016 Igashov_Ilya. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>


using namespace std;

int main()
{
    
    size_t size = 10;
    size_t range = 10;
    
    // --1-- //
    /* Заведите массив на 1000 случайных чисел из равномерного распределения {0, 1, ... , 99}. Необходимо иcпользовать при этом std::generate. */
    
    cout << "#1\n";
    
    time_t time_ = time(NULL);
    srand((int)time_);
    vector<int> first(size);
    generate(first.begin(), first.end(), [&range](){return rand()%range;});
    
    cout << "Сгенерированный массив:\n";
    copy(first.begin(), first.end(), ostream_iterator<int>(std::cout, " "));
    cout << '\n';
    
    // --2-- //
    /* Этот исходный массив мы менять не будем. Создайте копию исходного массива, с которой вы и будете дальше работать. Несмотря на то, что конструктором копирования это сделать значительно удобнее, в этом упражнении используйте функции std::copy и std::back_inserter. */
    
    cout << "\n#2\n";
    
    vector<int> copy_first;
    copy(first.begin(), first.end(), back_inserter(copy_first));
    
    cout << "Копия исходного массива:\n";
    copy(copy_first.begin(), copy_first.end(), ostream_iterator<int>(std::cout, " "));
    cout << '\n';

    // --3-- //
    /* Перемешайте элементы в случайном порядке. */
    
    cout << "\n#3\n";
    
    random_shuffle(copy_first.begin(), copy_first.end());
    
    cout << "Перемешали копию:\n";
    copy(copy_first.begin(), copy_first.end(), ostream_iterator<int>(std::cout, " "));
    cout << '\n';
    
    // --4-- //
    /* Отсортируйте их по убыванию. */
    
    cout << "\n#4\n";
    
    sort(copy_first.rbegin(), copy_first.rend());
    
    cout << "Отсортировали по убыванию:\n";
    copy(copy_first.begin(), copy_first.end(), ostream_iterator<int>(std::cout, " "));
    cout << '\n';
    
    // --5--//
    /* Разверните массив. */
    
    cout << "\n#5\n";
    
    reverse(copy_first.rbegin(), copy_first.rend());
    
    cout << "Развернули:\n";
    copy(copy_first.begin(), copy_first.end(), ostream_iterator<int>(std::cout, " "));
    cout << '\n';
    
    // --6-- //
    /* Напишите assert, который проверяет, что первый элемент получившегося массива равен минимальному элементу исходного массива. */
    
    cout << "\n#6\n";
    
    assert(*copy_first.begin() == *min_element(first.begin(), first.end()));
    
    cout << "Первый элемент получившегося массива равен минимальному элементу исходного массива" << '\n';

    // --7-- //
    /* Напишите assetr, который проверяет, что последний элемент получившегося массива равен максимальному элементу исходного массива. */
    
    cout << "\n#7\n";
    
    assert(*(copy_first.end() - 1) == *max_element(first.begin(), first.end()));
    
    cout << "Последний элемент получившегося массива равен максимальному элементу исходного массива" << '\n';
    
    // --8-- //
    /* Создайте массив permutation, заполненный последовательными целыми числами от 0 до 999. */
    
    cout << "\n#8\n";
    
    vector<int> permutation(size);
    int val = 0;
    for_each (permutation.begin(), permutation.end(), [&val](int & x){ x = val++; });
    
    cout << "permutation:\n";
    copy(permutation.begin(), permutation.end(), ostream_iterator<int>(std::cout, " "));
    cout << '\n';
    
    // --9-- //
    /* Сделайте так, чтобы он соответстваовал перестановке исходного массива, которая его сортирует. Для этого нужно вызвать std::sort для массива permutation, в котором лямбда будет захватывать по ссылке исходный массив. Оператор "меньше" для сортировки индексов соответсвует сравнению элементов в исходном массиве. */
    
    cout << "\n#9\n";
    
    sort(permutation.begin(), permutation.end(),
         [&first](int a, int b)
         {
             return first[a] < first[b];
         });
    
    cout << "Перестановка исходного массива:\n";
    copy(permutation.begin(), permutation.end(), ostream_iterator<int>(std::cout, " "));
    cout << '\n';
    
    // --10-- //
    /* Заведите пустой массив sorted. Примените функцию std::transform для массива перестановок, которая в результате получит сортированный исходный массив. Для этого вам снова нужно будет захватить по ссылке исходный массив и использовать функцию std::back_inserter. */
    
    cout << "\n#10\n";
    
    vector<int> sorted;
    transform(permutation.begin(), permutation.end(), back_inserter(sorted),
              [&first](int & x)
              {
                  return first[x];
              });
    
    cout << "Отсортированны исходный массив sorted:\n";
    copy(sorted.begin(), sorted.end(), ostream_iterator<int>(std::cout, " "));
    cout << '\n';
    
    // --11 -- //
    /* Напишите assert, который проверяет, что sorted отсортирован. */
    
    cout << "\n#11\n";
    
    for (int i = 0; i < sorted.size() - 1; ++i)
        assert(sorted[i] <= sorted[i + 1]);
        
    cout << "sorted действительно отсортирован\n";
    
    // --12-- //
    /* Напоминаю, что массив, с которым вы работали в пунктах 2-7, - тоже отсортированный исходный массив. Проверьте это, написав assert, сравнивающий этот массив с массивом sorted. */
    
    cout << "\n#12\n";
    
    for (int i = 0; i < sorted.size(); ++i)
        assert(sorted[i] == copy_first[i]);
    
    cout << "Массивы совпадают\n";
    
    // --13 - 14--//
    /* Теперь будем считать, сколько раз встречаются элементы в массиве. Используйте std::generate для генерации элементов массива counts, внутри которого количество элементов будет считаться с помощью std::count для исходного массива. Добавьте в лямбду из предыдущего пункта assert, который проверяет, что количество, вычисленное с помощью std::count для исходного массива, равно разнице между std::upper_bound и std::lower_bound для отсортированного массива. */
    
    cout << "\n#13-14\n";
    
    vector<int> counts(range);
    size_t j = 0;
    generate(counts.begin(), counts.end(),
             [&first, &sorted, &j]()
             {
                 size_t count_ = count(first.begin(), first.end(), j);
                 assert(count_ == (upper_bound(sorted.begin(), sorted.end(), j)
                                   - lower_bound(sorted.begin(), sorted.end(), j)));
                 ++j;
                 return count_;
             });
    cout << "Количество повторений элементов в исходном массиве:\n";
    copy(counts.begin(), counts.end(), ostream_iterator<int>(std::cout, " "));
    cout << '\n';
    
    // --15-- //
    /* Посчитайте сумму элементов в массиве counts. Напишите assert, который проверит, что она равна количеству сгенерированных чисел. */
    
    cout << "\n#15\n";
    size_t sum = 0;
    for_each(counts.begin(), counts.end(),
             [&sum](int x)
             {
                 sum += x;
             });
    assert (sum = size);
    cout << "Количество элементов в исходном массиве: " << sum << '\n';
    return 0;
}

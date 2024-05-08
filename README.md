# Лабораторная 5. Сравнение хэш-Таблиц

В данной лабораторной работе 
мы сравнивали эффективность различных функций хэширования, а также различных типов Хэш-таблиц.



## Графики

При построении графиков использовался скрипт `graph_ctor.py`. Достаточно создать список с названиями всех файлов, из которых брать данные для текущего графика, указать директорию и все необходимые подписи (всё вынесено в переменные вверху файла) и запустить:

    make print_graph
	
	

## Пункт 2. Сравнение Хэш-таблиц 

В лабораторной работе реализованы:

* Хэширование цепочками (hash_cep )
* открытое хэширование с линейным тестированием (hash_lin)
* Используйте открытое хэширование с квадратичным тестированием(hash_quad)
* Используйте открытое хэширование с методом двойного хэширования(hash_two)

Результаты представлены на графике:

![Хэш-таблицы, график](graph/hash_1png.png)

![Хэш-таблицы, график](graph/hash_1_without_ceppng.png)

Как мы видим, при частом перехэшировании количество calloc и realloc большое в hash_cep(В моей реализации связанного списка массиве)
В two_hash в среднем в два раза чаще считается хэш за счет двух хэш функций и в результате он примерно в два раза медленнее

В итоге у каждой хэш таблице баланс между перехэшированиием и замедлением в работе, в результате большой загруженности достигается при load_factor = 2


Далее я тестировал эти варианты на случайном наборе вставок\удалений\поиска

Результаты представлены на графике:

![Хэш-таблицы, график](graph/hash_2_randpng.png)

![Хэш-таблицы, график](graph/hash_2_rand_wittout_ceppng.png)

Как видно при меньшем процентном соотношении вставок, two_hash становится по эффективности таким же, как и остальные две(реализация hash_cep просто)


На следующей таблице представленны результаты при вероятности добавления 0.25 и 0.75 соответсвенно

![Хэш-таблицы, график](graph/hash_1_random_025png.png)

![Хэш-таблицы, график](graph/hash_1_random_025_without_ceppng.png)

![Хэш-таблицы, график](graph/hash_1_random_075png.png)

![Хэш-таблицы, график](graph/hash_1_random_075_without_ceppng.png)

## Пункт 3 Сравнение Обычного Хэширования с Идеальным


В лабораторной работе реализованы:

* открытое хэширование с линейным тестированием (hash_lin)
* Используйте открытое хэширование с квадратичным тестированием(hash_quad)
* Идеальное хэширование(hash_two)

![Хэш-таблицы, график](graph/hash_2_findpng.png)

Как и следовало из теории, Идеальное хэширование сильно эффективнее остальных при операции запроса.
 А из за не очень большого load_factor массива подсчет квадратичного хэша в среднем медленнее обработки коллизий.
 
 

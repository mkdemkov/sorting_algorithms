# Контрольное домашнее задание №1

## АиСД-2, 2023, задание 5. Демков Михаил Кириллович БПИ212. Среда разработки - CLion

## Основная логика

В **_main.cpp_** у меня есть 3 цикла - один внешний **t** и два внутренних **i**. Внешний цикл
отвечает за **тип массива**, **первый** внутренний за **размеры от 50 до 300 с шагом 50**, **второй
от 100 до 4100 с шагом 100.**
Внутри внутренних циклов прописана одна и та же логика, вынесенная в отдельную функцию ***process***: я создаю массив с типом элементов, заданным внешним циклом **t** и размеров, заданным
внутренним циклом **i**. Далее сортирую его копию, после каждой сортировки возвращая копию в
исходное состояние (в конце выделенная память освобождается)
**Каждая сортировка выполняется по 25 раз, время усредняется, как и число элементарных операций**

## Релизованные сортировки

* **пузырьковая сортировка**
* **пузырьковая сортировка с уловием Айверсона-1**
* **пузырьковая сортировка с условием Айверсона-2**
* **сортировка подсчетом**
* **сортировка выбором**
* **сортировка простыми вставками**
* **сортировка бинарными вставками**
* **цифровая сортировка**
* **сортировка слиянием**
* **быстрая сортировка**
* **пирамидальная сортировка**
* **сортировка Шелла (последовательность Шелла)**

## Реализованный функционал

**Основное:**
* **данные загружены в эксель таблицу (там 2 таблицы внутри) - файл 2 tables.xlsx в корне проекта**
* **графики построены и прокомментированы. Отчет по ним в файле report.pdf в корне проекта**
* **построены общие графики со всеми сортировками на разных типах массивов и диапазонах размеров**
* **построены частные графики со всеми сортировками на разных типах массивов и диапазонах размеров**
* **каждый график проанализирован и прокомментирован**
* **в конце есть небольшой общий вывод**
**Дополнительно:**
* **использование указателей на функции (функция sort в main.cpp принимает указатель на функцию,
  которую нужно использовать в качестве сортировки)**
* **освобождение выделенной памяти**
* **комментарии везде, где могут быть вопросы**
* **вывод результатов в csv файлы**
* **вывод массивов до и после сортировки для кажого вида сортировки в соответствующие текстовые файлы**

## Структура проекта

    — KDZ1 - корень
        | 
          — array-generating - директория с исходными кодами для генерации массива
        |
          — scripts - директория со скриптами для построения графиков
        |
          — sorting-algorithms - директория с исходными кодами 12 видов сортировки
        |
          — static - директория с кодами статичной логики (вывод в файлы, enum)
        |
          — tables - директория с csv таблицами
        |
          — text-files-output - директория с текстовыми файлами для вывода массивов до и после сортировки
        |
          — main.cpp - здесь описана основная логика работы
        |
          — 2 tables.xlsx - таблицы с результатами измерений
        | 
          — report.pdf - отчет по всем графикам

## Элементарные операции

За элементарные операции считаю следующее:

* **присваивание** (int i = 0 в цикле - это одна элементарная операция)
* **операции +, -, /, %, \*, /=, \*=, -=, +=, ++, --** (выражение a + b считается за одну
  элементарную операцию)
* **операторы сравнения >, <, >=, <=, ==, !=**
* встроенная функция **swap** считается за одну элементарную операцию
* **создание массива считаю за одну элементарную операцию** (int *arr = new int[n] - две операции:
  выделение памяти и присваивание).
  **Освобождение памяти считается за одну элементарную операцию** (delete[] arr - одна операция)
* **присваивания и операции для замеров времени не учитываются**

## Замеры времени

Каждую сортировку я прогоняю **25 раз** и беру усредненное время в наносекундах. Время сортировки -
это
**разница между текущим временем сразу после окончания сортировки и временем в самом начале
сортировки**. Для измерения времени используется библиотека _**chrono**_
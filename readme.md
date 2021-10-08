# Решение задачи коммивояжера

## Цель
Дана квадратная матрица расстояний.
Решить задачу коммивояжера точным и приближенным методами.

## Описание
Точный алгоритм основан на алгоритме перестановок Нарайаны.
Эвристический алгоритм - муравьиный алгоритм.
Коэффициенты: жадность 1, стадность 1, затухание феромонов 0.05.
Количество итераций 50.

## Компиляция и запуск
Для компиляции запускать ./makefile.sh
Программа запускается ./salesman -f имя файла -m метод.
Методы: np\_complete - полный перебор, np\_partial - муравьиный алгоритм.

# Библиотка для работы с трёхмерными фигурами
Используемые библиотеки: STL, SFML.
SFML - библиотека для создания 2D-игр(включает в себя модуль графики, аудио, сетевого соединения)
Используемый модуль - графический. При помощи него отрисовываются объемные объекты на 2D камеру.

Версия 0.2 (с поддержкой SFML)

Версия 0.1 (только STL)

Позволяет создавать собственные наборы точек, полигонов, демонстрировать их при помощи движка на SFML.
Присутствует набор базовых фигур: куб, призма, пирамида, цилиндр, конус, шар.

# Достоинства
+Порядок показа фигур правильный

+Порядок показа точек правильный

+Можно двигать фигуры по трём осям (одну за раз), менять масштаб, двигать камерой по вертикальной и горизонтальной круговой оси

+Универсальность модуля отображений(работа не с фигурами, а с наборами полигонов, точек)

+Универсальные классы фигур (При большом количестве точек призма переходит в цилиндр, пирамида - в конус)

+Красивый теневой градиент


# Недостатки

+Полигоны плохо сортируются половину времени.

+Отсутствуют коллизии, физика

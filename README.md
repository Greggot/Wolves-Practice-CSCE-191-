# Движок
Используемые библиотеки: STL, SFML.
SFML - библиотека для создания 2D-игр(включает в себя модуль графики, аудио, сетевого соединения)
Используемый модуль - грфаический. При помощи него отрисовываются объемные объекты на 2D камеру.

Версия Debug.

На данный момент движок является основным приложением, хотя планировалось, что он будет функцией, вызываемой, чтобы просмотреть созданную композицию из готовых и созданнх пользователем фигур.

# Фичи

+Порядок показа фигур правильный

+Порядок показа точек правильный

+Можно двигать фигуры по трём осям (одну за раз)

  +Менять масштаб

  +Двигать камерой по вертикальной и горизонтальной круговой оси

+Универсальность модуля отображений(работа не с фигурами, а с наборами полигонов, точек)

+Универсальные классы фигур (При большом количестве точек призма переходит в цилиндр, пирамида - в конус)

+Красивый теневой градиент


# АнтиФичи

+Полигоны фигур не сортируются, если сортируются, то случайным образом, иногда с попаданием, но только под определённым углом

+Отсутствуют коллизии

  +физика (не факт, что она нужна)

  +полигоны шара

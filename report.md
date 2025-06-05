**Изображение "input.bmp"**:
Формат: PC bitmap.
Размеры: 400 x 400 пикселей.
Глубина цвета: 24 бита.
Размер файла: 469 КБ.


**Значения при измерении времени работы лабораторной работы до введения параллельности:**
Right turn: 21
Left turn: 25
Left blur: 275
Right blur: 276
**Значения после внедрения параллельности:**
Right turn: 28
Left turn: 24
Left blur: 53
Right blur: 35
(Все значения были выведены на одних условаиях, радиус - 3 сигма - 2.0)

**Изменения**:
Поворот вправо: замедлился на 33%. (не страшно, так как начальное значение уже было довольно малым)
Поворот влево: ускорился на 4%.
Размытие влево: ускорилось на 81%.
Размытие вправо: ускорилось на 87%.

**Можно сделать вывод, что паралленость ускоряет процесс операций, которые можно считать более сложными, а для простых операций(поворот изображения) она не дала результата. Это значит что параллельность следует использовать лишь со сложнореализуемыми операциями.**

**Суть распараллеливания**: Изображение разбивается на горизонтальные полосы и каждая полоса обрабатывается отдельным потоком. Это позволяет распределить нагрузку между ядрами и значительно ускорить обработку изображения.

**Результаты тестов**:
[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from ImageTest
[ RUN      ] ImageTest.ConstructorTest
[       OK ] ImageTest.ConstructorTest (0 ms)
[ RUN      ] ImageTest.SetAndGetColorTest
[       OK ] ImageTest.SetAndGetColorTest (0 ms)
[ RUN      ] ImageTest.GaussianBlurTest
[       OK ] ImageTest.GaussianBlurTest (4 ms)
[ RUN      ] ImageTest.RightTurnTest
[       OK ] ImageTest.RightTurnTest (47 ms)
[ RUN      ] ImageTest.LeftTurnTest
[       OK ] ImageTest.LeftTurnTest (45 ms)
[ RUN      ] ImageTest.GaussianKernelTest
[       OK ] ImageTest.GaussianKernelTest (0 ms)
[----------] 6 tests from ImageTest (97 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (97 ms total)
[  PASSED  ] 6 tests.
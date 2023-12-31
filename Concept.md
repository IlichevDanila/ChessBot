# Общее описание

Бот разделен на три части:
- Ядро игры
- UCI интерфейс
- Движок для перебора/поиска

Движок будет работать на минимакс алгоритме с альфа-бета отсечением.
Таблицы транспозиций - ?

# Ядро игры
## Подход к генерации ходов
Состояние игры будет изменяемым, совершение хода будет его изменять (вместо создания нового иммутабельного состояния, как в прошлой версии). Это позволит запихать в состояние практически сколько угодно информации - все равно будет существовать всего одна копия этого объекта на протяжении игры.

Это влечет за собой необходимость уметь отменять ход, а значит объект "хода" должен иметь достаточно информации для полного отката состояния.

Проверка хода на легальность можно сделать глупо - простым перебором всех возможных ходов оппонента и поиском среди них захвата короля. Дело в том, что в основном переборе можно будет рассматривать псевдолегальные ходы - при условии, что бот будет смотреть на два полухода в будущее, мы можем быть уверены, что ветки с потерей короля в любом случае будут отсекаться.
Однако если это вдруг окажется плохим подходом (например из-за увеличения возможных веток), то придется реализовать нормальную проверку легальности хода (скорее всего битбордом атакованных клеток).

## Состояние игры
Полным образом состояние игры описывается следующим набором данных:
- Расположение фигур
- Очередность хода
- Вертикаль для взятия на проходе - если такая есть
- Возможности для рокировок каждой из сторон. Может быть самостоятельно представлена тремя полями:
    + Ходил ли король
    + Ходила ли ладья со стороны короля
    + Ходила ли ладья со стороны королевы
- Сколько ходов прошло с последнего хода пешки или захвата фигуры (для ничьей по правилу 50 ходов)
- Список позиций с момента последнего необратимого хода (взятие фигуры, продвижение пешки, рокировка, изменение вертикали для взятия на проходе) с указанием количества повторений. Под позицией подразумевается:
    + Расположение фигур
    + Очередность хода
    + Возможности рокировок
    + Вертикаль для взятия на проходе

Последний пункт необходим для возможности ничьи по троекратному повтору позиции. Важно, что в таком случае ничья является опциональной возможностью, а не жестким исходом. Так же есть правило, что ничья **обязательно** настает при пятикратном повторении за пять последовательных ходов, но это я точно не стану реализовывать. В целом я скорее всего и ничью по троекратному повторению использовать не стану, но "позицию" всё равно лучше на всякий случай инкапсулировать

Другие аспекты состояния можно определить из перечисленных выше и из правил игры:
- Ходила ли пешка (для выяснения возможности двойного хода) определяется её горизонаталью
- Фактическая возможность рокировки определяется формальной, а так же положением фигур на доске (и клетками под ударом)

## Как ход может изменить состояние игры
Для того, чтоб по одной лишь структуре хода можно было полностью откатить изменения состояния, объект хода должен содержать следующую информацию:
- Передвижение фигур, их снятие и появление. Большинство ходов совершает либо перемещение (тихий ход), либо перемещение со снятием (простой захват). Рокировка перемещает сразу две фигуры. Пешка может совершить продвижение при захвате, то есть фактически совершить снятие двух фигур с поля и появление ещё одной.
- Предыдущее состояние "счетчика 50 ходов". Новое состояние вычисляется по виду хода и предыдущему значению.
- Предыдущие формальные возможности рокировок. Пусть по ходу короля и ладьи можно понять, что рокировка более невозможна - при откате хода неизвестно была ли такая возможность до него.
- Предыдущая вертикаль для взятия на проходе.

Очередность хода всегда меняется на противоположную при совершении хода, так что для отката дополнительной информации об этом не требуется. Так же нет необходимости создавать дополнительных полей объекта хода для отката "истории" позиций - откат всегда заключается в вытеснении новейшего из списка.

# Описание реализации
## Фигура (Piece)
### Данные
- Цвет (1 бит)
- Тип (3 бита)

### Методы
- Конструктор по FEN-нотации фигуры (аргумент: символ)
- Символьное представление для печати на экран

### Оценка объема памяти - 1 байт

## Позиция (State)
### Данные
- Список из 64 клеток/фигур. Пустая клетка - фигура со специальным значением типа (нулевым) и нулевым (черным) цветом. Всего 64 байта (можно снизить до 32 байт путем уплотнения фигур "парами" - ценой дополнительных вычислений)
- Очередность хода (1 бит)
- Возможности рокировок. По 4 возможности для каждой стороны - всего 4 бита
- Вертикаль для взятия на проходе (а так же её отсутствие) - 4 бита
### Методы
- Конструктор по подстроке FEN (аргумент: строка)
- Строковое представление для печати на экран

### Оценка объема памяти - 66 байт

## Состояние игры (Board)
### Данные
- Текущая позиция (оценочно 65 байт)
- Счетчик "50 ходов" (6 бит)
- Список состояний для ничьи по трем повторениям (скорее всего не будет реализовано) - оценка памяти пока неизвестна
- Стек захваченных фигур - чтоб не хранить захваты в объектах хода

- Битборды (по 1 на каждую сторону) - каждый по 8 байт:
    + Клетки под атакой
    + Пешки
    + Кони
    + Слоны
    + Ладьи
    + Королевы
    + Король

- Оценка состояния для перебора (4 байта)
- Хэш состояния по Зобристу (8 байт)

Битборды будут использоваться для:
+ Вычисления атакованных клеток
+ Оценки состояния (например, структуры пешек)

### Методы
- Конструктор из FEN нотации (аргумент: строка)
- Строковое представление для вывода на экран
- Применение хода (аргумент: ход)
    + Применение хода пешки
    + Применение хода ладьи
    + Применение хода короля
    + Применение хода остальных фигур
- Отмена хода (аргумент: ход)
    + Отмена хода пешки
    + Отмена хода ладьи
    + Отмена хода короля
    + Отмена хода остальных фигур
- Пересчет битбордов
- Пересчет хэша
- Пересчет оценки состояния

### Оценка объема памяти - по меньшей мере 216 байта (без истории состояний)

## Ход (Move)
### Данные
- Позиция движимой фигуры (1 байт)
- Позиция назначения движения (1 байт)
- Флаг хода (4 бита). Возможные состояния
    + 0 - тихий ход
    + 1 - Двойной ход пешки
    + 2 - Рокировка стороны короля
    + 3 - Рокировка стороны королевы
    + 4 - Взятие (простое)
    + 5 - Взятие на проходе
    + 8 - Превращение в коня
    + 9 - Превращение в слона
    + 10 - Превращение в ладью
    + 11 - Превращение в королеву
    + 12 - Превращение в коня с захватом
    + 13 - Превращение в слона с захватом
    + 14 - Превращение в ладью с захватом
    + 15 - Превращение в королеву с захватом
- Предыдущее состояния счетчика 50 ходов (6 бит)
- Предыдущие возможности рокировок (4 бита)
- Предыдущая вертикаль для взятия на проходе (4 бита)

### Методы
- Конструктор по UCI нотации (аргументы: состояние, строка)
- Строковое представление в UCI нотации для печати
### Оценка объема памяти - 5 байт

## Генератор ходов (MoveGenerator)
### Данные
### Методы
- Список ходов для пешки (аргументы: состояние, ячейка)
- Список ходов для коня (аргументы: состояние, ячейка)
- Список ходов для слона/ладьи/королевы (аргументы: состояние, ячейка, массив направлений, размер массива направлений)
- Список ходов для короля (аргументы: состояние, ячейка)
- Проверка хода на легальность (аргументы: состояние, ход)
- Список псевдолегальных ходов (аргументы: состояние)
- Список легальных ходов (аргументы: состояние)

Ходы фигур генерируются без учета легальности, но с учетом окружающих фигур и возможности рокировки (для короля) и взятия на проходе (для пешки)
### Оценка объема памяти - 0 байт
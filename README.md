# StringCreatorPieceByPiece


## Клас за построяване на стринг без алокираме памет за всеки добавен символ.


Класът работи с “парчета” (StringPiеce) - част от стринга с дължина най-много 16 символа.
Във всяко едно от тези парчета има функции/оператори за:
- get и set за стойността.
- Оператори << и >> за конкатенация на низове/числа в началото/края.
- Премахване на първите/последните k символа.
- Промяна на символ по индекс.

В класа има колекция от такива парчета, като на всяко от тях може да им се прилагат по-горе описаните операции. В конструктора се подава начален капацитет за броя парчета. Има и операции за:
- Добавяне на ново парче в края на колекцията. Ако не се подаде низ, то парчето да е със стойност празния стринг.
- Размяна на две парчета по подадени два индекса.
- Изтриване на парче по индекс. Този индекс остава празен.
- Добавяне на парче по индекс. Ако на този индекс има парче, то да се замести с новото парче.
- Взимане дължината на построения стринг до момента.
- Връщане на обект от тип MyString с точна големина с построения стринг до момента. Построеният стринг е 
конкатенацията на стойностите на всички парчета. Ако индекс (ПРЕДИ последното парче) е празен  (парчето е било е изтрито и не е добавени нищо),  
то в стринга се поставят 20 символа за интервал.

## Условие

Пълно условие на домашна работа 2:
[Домашна работа 2.pdf](https://github.com/rayagrigorova/string-creator-piece-by-piece/files/12185471/2.pdf)

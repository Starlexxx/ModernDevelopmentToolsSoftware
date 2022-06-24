<div align="center">
Министерство науки и высшего образования Российской Федерации <br />
Федеральное государственное бюджетное образовательное учреждение <br />
высшего образования <br />
«Московский государственный технический университет <br />
имени Н.Э. Баумана <br />
(национальный исследовательский университет)» <br />
(МГТУ им. Н.Э. Баумана)
</div>
<hr />
<div align="center">
ФАКУЛЬТЕТ ИНФОРМАТИКА И СИСТЕМЫ УПРАВЛЕНИЯ <br />
КАФЕДРА КОМПЬЮТЕРНЫЕ СИСТЕМЫ И СЕТИ (ИУ6)
</div>
<br />
<div align="center">
ОТЧЕТ <br />
к лабораторной работе №2 <br />
по дисциплине "Современные средства разработки <br />
программного обеспечения" <br />
Реализация типовых решений с применением шаблонов проектирования.
</div>
<br />

Преподаватель: Фетисов М.В.

Студент группы ИУ6-51Б Павловский Андрей Андреевич.
Студент группы ИУ6-51Б Лучкин Федор Антонович.

## Описание задания

Задание №1: Шаблон проектирования Property Container (Контейнер свойств).

Реализуйте карточку вашего домашнего задания с использованием шаблона проектирования Property container (контейнер свойств). С использованием параметров командной строки выполните наполнение карточки (единственной карточки, работа с контейнером карточек не требуется) и осуществите вывод полей карточки в стандартный поток.
## Адрес проекта

Проект хранится в репозитории по адресу: [https://bmstu.codes/lsx/mstd/iu6-5-2021/iu6-55b-aapavlovskiy-faluchkin/lab2](https://bmstu.codes/lsx/mstd/iu6-5-2021/iu6-55b-aapavlovskiy-faluchkin/lab2).

## Диаграммы классов

![Класс Instrument](https://lsx.pages.bmstu.codes/mstd/iu6-5-2021/iu6-55b-aapavlovskiy-faluchkin/lab2/class_instrument__coll__graph.png)

Описание классов хранится в репозитории по адресу: [https://bmstu.codes/lsx/mstd/iu6-5-2021/iu6-55b-aapavlovskiy-faluchkin/lab2](https://bmstu.codes/lsx/mstd/iu6-5-2021/iu6-55b-aapavlovskiy-faluchkin/lab2).

## Функция main

```cpp
int main(int argc, char **argv) {
  try {
    Instrument guitar;

    guitar.setProperty("name", argv[1]);
    guitar.setProperty("brand", argv[2]);
    guitar.setProperty("model", argv[3]);
    guitar.setProperty("cost", argv[4]);
    guitar.setProperty("isAvailable", argv[5]);

    std::cout << guitar.getProperty("name") << " "
              << guitar.getProperty("brand") << " "
              << guitar.getProperty("model") << " "
              << guitar.getProperty("cost") << " "
              << guitar.getProperty("isAvailable");

    return 0;

    std::cout << "*** Недопустимое количество аргументов" << std::endl;
    return 1;
  }

  catch (std::exception &e) {
    std::cout << "*** " << e.what() << std::endl;
    return 1;
  }
}
```

## Выводы
В ходе выполнения лабораторной работы удалось реализовать шаблон проектирования контейнер свойств на примере инструментов. Также, были изучены параметры командной строки и осуществлено добавление новых свойств с ее помощью. Были усовершенствованы навыки работы с автотестами и удаленным репозиторием GitLab

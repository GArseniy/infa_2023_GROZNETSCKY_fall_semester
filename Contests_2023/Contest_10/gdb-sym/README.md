# gdb-sym

В этой задаче вам предстоит поработать с [GDB](https://www.gnu.org/software/gdb/) (GNU debugger)
и поковырять бинарники (как собранные с дебажными символами, так и без оных), чтобы 
извлечь из них некоторую информацию.

Проверка осуществляется с помощью скрипта `oracle.py`: если вы считаете, что для задачи `xyz` 
ответ `123`, то пишите `python oracle.py xyz 123`, и вам выведется потенциальный флаг. Если он более-менее
похож на осмысленную фразу, то её можно попробовать ввести [сюда](https://cpp.manytask.org/submit).

### Задачи

1. `with_symbols`: Вам дана программа, собранная без оптимизации и с дебажными
символами. __Ответ__: значение переменной `x` после 10000-ой итерации цикла в функции `f()`.
1. `without_symbols`: На этот раз программа собрана с оптимизацией и без дебажной информации.
Придётся немного освежить знание языка ассемблера. __Ответ__: значение регистра `rax` после 10000-ой 
итерации цикла (прямо перед `jne`) в функции `f()`.
1. `with_core`: Вам предстоит покопаться в кишках стандартного контейнера, используя оставшийся после
выполнения программы сore dump. К сожалению, сам контейнер частично побился из-за того же бага, что 
уронил программу, но гарантируется, что данные извлечь можно. __Ответ__: `hashmap[8888][1]`.
1. `flaky`: Эта программа пытается посчитать ответ для вас, но с очень большой вероятностью падает
на полпути. __Ответ__: то, что напечатает программа, если добежит до конца.

### Используем docker

Все бинарники были собраны на ubuntu 18.04. Если у вас стоит
достаточно свежий дистрибутив linux, то задачи можно решать на нём.

Для тех, у кого OSX, Windows или какой-то странный linux, мы собрали
докер образ с правильным окружением.

```
$ docker run --privileged -it darthslon/shad-cpp:gdb /bin/bash
root@a9bc09439be8:/# cd opt
root@a9bc09439be8:/opt# ls
coredump  flaky  with_core  with_symbols  without_symbols
```

### Полезные ссылки
* https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/hashtable.h
* https://www.gnu.org/software/gdb/
* https://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax
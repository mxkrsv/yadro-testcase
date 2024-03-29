# Обзор

`write` - программа, создающая сегмент разделяемой памяти SYSV, записывающая через отображение в
адресное пространство в разделяемую память строку `"Hello, world!"` и выводящая в `stdout` ключ
данного сегмента.

`read` - программа, читающая ключ из `stdin`, и выводящая в `stdout` строку, хранящуюся в данном
сегменте разделяемой памяти.

# Сборка

`Makefile` содержит все необходимые для сборки и запуска цели.

- `make build` локально собирает два исполняемых файла: `write` и `read`.
- `make run` запускает команду `./write | ./read`.
- `make clean` удаляет собранные файлы.

По аналогии, команды для Docker:

- `make dockerbuild` - сборка контейнера.
- `make dockerrun` - запуск контейнера (то же самое `./write | ./read` внутри).
- `make dockerclean` - удаление собранного контейнера.

Или руками:
```ShellSession
$ docker build . -t yadro-testcase
$ docker run --rm yadro-testcase
$ docker rmi yadro-testcase
```

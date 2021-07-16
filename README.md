# service_util
Набор некоторых инструментов

- [ ] Предусмотреть статическую сборку с BOOST для формирования библиотеки

Для использования, необходимо скачать репозиторий в любом виде (лучше git clone, чтобы была возможность быстрого обновления при внесении каких-либо изменений),
добавить скачанные файлы в проект:

Для QMake:
```qmake 
...

HEADERS += some.h \
           c://libs//service_util-master//service.h
            
SOURCES += main.cpp \
           c://libs//service_util-master//service.cpp
...
```
Для CMake:
```cmake
...

include_directories(c://libs//service_util-master//service.h)
add_executable(${NAME_OF_PROJECT} main.cpp ... c://libs//service_util-master//service.cpp)

...
```
**Важное замечание!**

Чтобы всё заработало, нужно правильно указать `#include` путь к файлу `service.h`

По умолчанию выглядит вот так:

```c++
#include <../headers/service/service.h>
```

Так же, для того, чтобы использовать асинхронные контейнеры, необходимо подключить библиотеку `BOOST`. Для отключения возможности использования асинхронных контейнеров необходимо отключить директиву `USE_BOOST` в заголовочном файле, при этому BOOST не будет использоваться.



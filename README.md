# service_util
Набор некоторых инструментов

Для использования, необходимо скачать репозиторий в любом виде (лучше git clone, чтобы была возможность быстрого обновления при внесении каких-либо изменений),
добавить скачанные файлы в проект:

Для QMake
```qmake 
...

INCLUDES += some.h \
            <path>/service.h
            
SOURCES += main.cpp \
            <path>/service.cpp
...
```
Для CMake
```cmake
...

include_directories(<path>/*service.h*)
add_executable(${NAME_OF_PROJECT} main.cpp ... *service.cpp*)

...
```

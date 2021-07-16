# service_util
Набор некоторых инструментов

Для использования, необходимо скачать репозиторий в любом виде (лучше git clone, чтобы была возможность быстрого обновления при внесении каких-либо изменений),
добавить скачанные файлы в проект:

Для QMake:
```qmake 
...

INCLUDES += some.h \
            c://libs//service_util-master//`service.h`
            
SOURCES += main.cpp \
           c://libs//service_util-master///`service.cpp`
...
```
Для CMake:
```cmake
...

include_directories(c://libs//service_util-master///`service.h`)
add_executable(${NAME_OF_PROJECT} main.cpp ... c://libs//service_util-master//`service.cpp`)

...
```

#ifndef SERVICE_H
#define SERVICE_H

#define USE_BOOST

#ifdef USE_BOOST
#include <boost/thread/thread.hpp>
#include <boost/system/error_code.hpp>
#endif

#include <ctime>
#include <vector>

#ifdef USE_BOOST
//Макрос для заворачивания lock_guard
#define BOOST_LOCK(mx) boost::lock_guard<boost::mutex> lock(mx)
#endif

//cout функции для отладки (deprecated)
#define DEBUG std::cout << "[DEBUG] "
#define ERROR std::cout << "[ERROR] "

#ifdef USE_BOOST
// Обёртка над стандартным вектором для использования в асинхронных операциях
namespace async_containers {
    template<class storage_t>
    class async_vector_wrapper {
    private:
        std::vector<storage_t> vec;
        mutable boost::mutex mx;

    public:
        async_vector_wrapper();

        // метод для блокирования мьютекса
        static void lock(async_vector_wrapper<storage_t> &inst);

        // метод для разблокирования мьютекса
        static void unlock(async_vector_wrapper<storage_t> &inst);

        storage_t *get_data_ptr(void);

        //Получение размера хранимого вектора
        void get_size(size_t &out_s);

        // Очистка содержимого вектора
        void clear(void);

        // Полная очистка вектора (со сбросом всех параметров)
        void reset(void);

        // Изменение размера вектора
        void resize(size_t new_size);

        //Обёртка над записью по индексу
        bool write_to(size_t idx, storage_t val, boost::system::error_code &err);

        // Получение значения по индексу (с отслеживанием ошибок выполнения)
        bool get_from(size_t idx,
                      storage_t &res_storage,
                      boost::system::error_code &err);

        //Простое копирование в асинхронный объект из синхронного
        bool put_data_from(std::vector<storage_t> *location,
                           size_t size,
                           boost::system::error_code &err);

        // Копирование данных из объекта в другое синхронное расположение
        bool put_data_to(std::vector<storage_t> *location,
                         size_t size,
                         boost::system::error_code &err);

        // Копирование данных в другой асинхронный вектор
        bool copy_data_to_async_vec(async_vector_wrapper<storage_t> *other_vec,
                                    size_t size,
                                    boost::system::error_code &err);

        // Копирование данных из другого асинхронного вектора
        bool copy_data_from_async_vec(async_vector_wrapper<storage_t> *other_vec,
                                      size_t size,
                                      boost::system::error_code &err);
    };
}
#endif

//Функции преобразования времени
namespace custom_time {
    const time_t y06011998 = 315954000;

    time_t local_time_to_UTC(time_t local_t);

    time_t from_UTC_to_ISS(time_t utc_time);

    time_t from_ISS_to_UTC(time_t uss_time);

    time_t get_offset_from_zero(void);
}

#endif // SERVICE_H
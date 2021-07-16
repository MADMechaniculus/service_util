//
// Created by madded on 13.07.2021.
//

#include "service.h"
#include <ctime>

// Получение смещения
time_t custom_time::get_offset_from_zero() {
    struct tm * tm_ptr;
    tm_ptr = std::localtime(new time_t(0));
    return mktime(tm_ptr);
}

// Преобразование локального времени к единому по UTC
time_t custom_time::local_time_to_UTC(time_t local_t) {
    return local_t - custom_time::get_offset_from_zero();
}

// Перевод из формата UTC в формат используемый на ISS
time_t custom_time::from_UTC_to_ISS(time_t utc_time) {
    time_t ret = utc_time - custom_time::y06011998;
    return ret;
}

// Перевод из формата ISS в формат UTC
time_t custom_time::from_ISS_to_UTC(time_t iss_time) {
    time_t ret = iss_time + custom_time::y06011998;
    return ret;
}

#ifdef USE_BOOST
template<class T>
async_containers::async_vector_wrapper<T>::async_vector_wrapper() {
    this->data_ptr = vec.data();
}

template<class T>
void async_containers::async_vector_wrapper<T>::lock(async_vector_wrapper<T> &inst) {
    inst.mx.lock();
}

template<class T>
void async_containers::async_vector_wrapper<T>::unlock(async_vector_wrapper<T> &inst) {
    inst.mx.unlock();
}

template<class T>
T *async_containers::async_vector_wrapper<T>::get_data_ptr(void) {
    return vec.data();
}

template<class T>
void async_containers::async_vector_wrapper<T>::get_size(size_t &out_s) {
    BOOST_LOCK(mx);
    out_s = vec.size();
}

template<class T>
void async_containers::async_vector_wrapper<T>::clear() {
    BOOST_LOCK(mx);
    vec.clear();
}

template<class T>
void async_containers::async_vector_wrapper<T>::reset() {
    BOOST_LOCK(mx);
    vec.swap(new std::vector<T>());
}

template<class T>
void async_containers::async_vector_wrapper<T>::resize(size_t new_size) {
    BOOST_LOCK(mx);
    vec.resize(new_size);
}

template<class T>
bool async_containers::async_vector_wrapper<T>::write_to(size_t idx, T val, boost::system::error_code &err) {
    BOOST_LOCK(mx);
    using namespace boost::system;
    if (idx > (vec.size() - 1)) {
        err = errc::make_error_code(errc::result_out_of_range);
        return false;
    } else {
        vec[idx] = val;
        return true;
    }
}

template<class T>
bool async_containers::async_vector_wrapper<T>::get_from(size_t idx, T &res_storage,
                                                         boost::system::error_code &err) {
    BOOST_LOCK(mx);
    if (idx > vec.size() - 1) {
        err = boost::system::errc::make_error_code(boost::system::errc::result_out_of_range);
        return false;
    } else {
        res_storage = vec.at(idx);
        return true;
    }
}

template<class T>
bool async_containers::async_vector_wrapper<T>::put_data_from(std::vector<T> *location, size_t size,
                                                              boost::system::error_code &err) {
    BOOST_LOCK(mx);
    using namespace boost::system;
    if ((size > vec.size() - 1) || (size > location->size() - 1)) {
        err = errc::make_error_code(errc::result_out_of_range);
        return false;
    } else {
        memcpy(vec.data(), location->data(), size);
        return true;
    }
}

template<class T>
bool async_containers::async_vector_wrapper<T>::put_data_to(std::vector<T> *location, size_t size,
                                                            boost::system::error_code &err) {
    using namespace boost::system;
    BOOST_LOCK(mx);
    if ((size > vec.size() - 1) || (size > location->size() - 1)) {
        err = errc::make_error_code(errc::result_out_of_range);
        return false;
    } else {
        memcpy(location->data(), vec.data(), size);
        return true;
    }
}

template<class T>
bool async_containers::async_vector_wrapper<T>::copy_data_to_async_vec(async_vector_wrapper<T> *other_vec,
                                                                       size_t size, boost::system::error_code &err) {
    using namespace boost::system;
    BOOST_LOCK(mx);
    size_t other_size = 0;
    other_vec->get_size(other_size);
    if ((size > other_size - 1) || (size > vec.size() - 1)) {
        err = errc::make_error_code(errc::result_out_of_range);
        return false;
    } else {
        async_vector_wrapper::lock(other_vec);
        memcpy(other_vec->get_data_ptr(), vec.data(), size);
        async_vector_wrapper::unlock(other_vec);
        return true;
    }
}

template<class T>
bool async_containers::async_vector_wrapper<T>::copy_data_from_async_vec(async_vector_wrapper<T> *other_vec,
                                                                         size_t size, boost::system::error_code &err) {
    using namespace boost::system;
    BOOST_LOCK(mx);
    size_t other_size = 0;
    other_vec->get_size(other_size);
    if ((size > other_size - 1) || (size > vec.size() - 1)) {
        err = errc::make_error_code(errc::result_out_of_range);
        return false;
    } else {
        async_vector_wrapper::lock(other_vec);
        memcpy(vec.data(), other_vec->get_data_ptr(), size);
        async_vector_wrapper::unlock(other_vec);
        return true;
    }
}
#endif
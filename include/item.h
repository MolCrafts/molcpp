#include <any>
#include <initializer_list>
#include <memory>

#include "dict.h"

namespace molcpp {

    class Item {

        public:

            Item() : _id(reinterpret_cast<size_t>(this)) {};

            // TODO - add constructor that takes a Dict

            size_t get_id() const {
                return _id;
            }

            /**
             * @brief Get the clone of the item.
             * 
             */
            virtual std::unique_ptr<Item> clone() const
            {
                return std::make_unique<Item>(*this);
            }

            /**
             * @brief Get the value associated with a key.
             * 
             * @tparam T 
             * @param key 
             * @return T 
             */
            template <typename T>
            T get(const std::string &key) {
                return _props.get<T>(key);
            }

            /**
             * @brief Get the value associated with a key, or a default value.
             * 
             * @tparam T 
             * @param key 
             * @param default_value 
             * @return T 
             */
             template<typename T>
                T get(const std::string &key, const T &default_value) {
                    return _props.get<T>(key, default_value);
                }

            /**
             * @brief Set the value associated with a key.
             * 
             */
            template<typename T>
            T set(const std::string &key, const T &default_value) {
                return _props.setdefault<T>(key, default_value);
            }

        private:
            size_t _id;
            Dict _props;
    };

    class Atom : public Item {

        public:

            Atom();

            /**
             * @brief Get the clone of the item.
             * 
             */
            std::unique_ptr<Item> clone() const override;

    };

}
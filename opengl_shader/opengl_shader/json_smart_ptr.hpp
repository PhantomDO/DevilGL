#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

namespace PolymorphicJsonSerializer_impl
{
	template<class Base>
    struct Serializer
	{
        void (*to_json)(nlohmann::json &j, Base const &o);
        void (*from_json)(nlohmann::json const &j, Base &o);
	};

    template<class Base, class Derived>
    Serializer<Base> SerializerFor()
    {
        return
        {
            [](nlohmann::json &j, Base const &o)
            {
                return to_json(j, static_cast<Derived const&>(o));
            },
            [](nlohmann::json const &j, Base &o)
            {
                return from_json(j, static_cast<Derived&>(o));
            }
        };
    }
}

template<class Base>
struct PolymorphicJsonSerializer
{
    static inline std::unordered_map<char const*, PolymorphicJsonSerializer_impl::Serializer<Base>> _serializers;

    template<class... Derived>
    static void RegisterTypes()
    {
        (_serializers.emplace(typeid(Derived).name(), PolymorphicJsonSerializer_impl::SerializerFor<Base, Derived>()), ...);
    }

    static void to_json(nlohmann::json &j, Base const &o)
    {
        char const* typeName = typeid(o).name();
        _serializers.at(typeName).to_json(j, o);
        j["_type"] = typeName;
    }

    static void from_json(nlohmann::json const &j, Base &o)
    {
        _serializers.at(j.at("_type").get<std::string>().c_str()).from_json(j, o);
    }
};


// partial specialization (full specialization works too)
namespace nlohmann
{
    template <typename T>
    struct adl_serializer<std::optional<T>>
	{
        static void to_json(json& j, const std::optional<T>& opt)
    	{
            j = opt.value_or(nullptr);
        }

        static void from_json(const json& j, std::optional<T>& opt)
    	{
            opt = j.is_null() ? nullptr : j.get<std::optional<T>>();
        }
    };

    template <typename T>
    struct adl_serializer<std::shared_ptr<T>>
	{
        static void to_json(json& j, const std::shared_ptr<T>& opt)
    	{
            j = opt ? *opt.get() : nullptr;
        }

        static void from_json(const json& j, std::shared_ptr<T>& opt)
    	{
            opt = j.is_null() ? nullptr : j.get<std::shared_ptr<T>>();
        }
    };

	template <typename T>
    struct adl_serializer<std::unique_ptr<T>>
	{
        static void to_json(json& j, const std::unique_ptr<T>& opt)
    	{
            j = opt ? *opt.get() : nullptr;
        }

        static void from_json(const json& j, std::unique_ptr<T>& opt)
    	{
            opt = j.is_null() ? nullptr : j.get<std::unique_ptr<T>>();
        }
    };

}
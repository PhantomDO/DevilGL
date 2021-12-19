#pragma once
#include <iostream>
#include <nlohmann/json.hpp>

#include "Debug.h"
#include "json_smart_ptr.hpp"

#define TO_STRING( x ) #x

//****************
// CLASS_DECLARATION
//
// This macro must be included in the declaration of any subclass of Component.
// It declares variables used in type checking.
//****************
#define CLASS_DECLARATION( classname )                                                      \
public:                                                                                     \
    static const std::size_t Type;                                                          \
    virtual bool IsClassType( const std::size_t classType ) const override;                 \

//****************
// CLASS_DEFINITION
// 
// This macro must be included in the class definition to properly initialize 
// variables used in type checking. Take special care to ensure that the 
// proper parentclass is indicated or the run-time type information will be
// incorrect. Only works on single-inheritance RTTI.
//****************
#define CLASS_DEFINITION( parentclass, childclass )                                         \
const std::size_t childclass::Type = std::hash< std::string >()( TO_STRING( childclass ) ); \
bool childclass::IsClassType( const std::size_t classType ) const {                         \
        if ( classType == childclass::Type ) return true;                                   \
        return parentclass::IsClassType( classType );                                       \
}


namespace Engine
{
	class Component
	{
	public:

		static const std::size_t Type;
		virtual bool IsClassType(const std::size_t classType) const { return classType == Type; }
		
	public:
		virtual ~Component() = default;
		Component() = default;
	};
}


namespace nlohmann
{
	template<>
	struct adl_serializer<Engine::Component> : PolymorphicJsonSerializer<Engine::Component> {};
}


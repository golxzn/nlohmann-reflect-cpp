#pragma once

#if __has_include(<yyjson.h>)
#include <nlohmann/json.hpp>
#else
#error Cannot found <nlohmann/json.hpp> header file!
#endif // __has_include(<yyjson.h>)

#include <rfl/Result.hpp>
#include <rfl/always_false.hpp>

namespace rfl::nlohmann {

struct Reader {
	struct InputArrayType {
		::nlohmann::json *value{ nullptr };
	};
	struct InputObjectType {
		::nlohmann::json *value{ nullptr };
	};
	struct InputVarType  {
		::nlohmann::json *value{ nullptr };
	};

	/// If you do not want to support custom constructors,
	/// just set this to false.
	template<class T>
	static constexpr bool has_custom_constructor = false;

	/// Retrieves a particular field from an array.
	/// Returns an rfl::Error if the index is out of bounds.
	/// If your format is schemaful, you do not need this.
	auto get_field_from_array(
		const size_t _idx, const InputArrayType &_arr
	) const noexcept -> rfl::Result<InputVarType>;

	/// Retrieves a particular field from an object.
	/// Returns an rfl::Error if the field cannot be found.
	/// If your format is schemaful, you do not need this.
	auto get_field_from_object(
		const std::string &_name, const InputObjectType &_obj
	) const noexcept -> rfl::Result<InputVarType>;

	/// Determines whether a variable is empty (the NULL type).
	auto is_empty(const InputVarType &_var) const noexcept -> bool;

	/// Cast _var as a basic type (bool, integral,
	/// floating point, std::string).
	/// Returns an rfl::Error if it cannot be cast
	/// as that type
	template <class T>
	auto to_basic_type(const InputVarType &_var) const noexcept -> rfl::Result<T> {
		return _var.value->get<T>();
	}

	/// Casts _var as an InputArrayType.
	/// Returns an rfl::Error if `_var` cannot be cast as an array.
	auto to_array(const InputVarType &_var) const noexcept -> rfl::Result<InputArrayType>;

	/// Casts _var as an InputObjectType.
	/// Returns an rfl::Error if `_var` cannot be cast as an object.
	auto to_object(const InputVarType &_var) const noexcept -> rfl::Result<InputObjectType>;

	/// Iterates through an array and inserts the values into the array
	/// reader. See below for a more detailed explanation.
	auto read_array(
		const auto  &_array_reader,
		const InputArrayType &_arr
	) const noexcept -> std::optional<rfl::Error> {
		for (auto &value : *_arr.value) {
			if (auto error{ _array_reader.read(InputVarType{ &value }) }; error) {
				return std::move(error);
			}
		}
		return std::nullopt;
	}

	/// Iterates through an object and inserts the key-value pairs into the object
	/// reader. See below for a more detailed explanation.
	auto read_object(
		const auto &_object_reader,
		const InputObjectType &_obj
	) const noexcept -> std::optional<rfl::Error> {
		for (auto &[key, value] : _obj.value->items()) {
			_object_reader.read(key, InputVarType{ &value });
		}
		return std::nullopt;
	}

	/// Constructs T using its custom constructor. This will only be triggered if
	/// T was determined to have a custom constructor by
	/// static constexpr bool has_custom_constructor, as defined above.
	/// Returns an rfl::Error, if the custom constructor throws an exception.
	template <class T>
	rfl::Result<T> use_custom_constructor(
		const InputVarType& _var) const noexcept {
		// If you do not want to support this functionality,
		// just return this.
		return rfl::Error("Not supported.");
	}
};

} // namespace rfl::nlohmann

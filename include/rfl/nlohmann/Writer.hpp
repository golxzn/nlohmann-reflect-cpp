#pragma once

#if __has_include(<yyjson.h>)
#include <nlohmann/json.hpp>
#else
#error Cannot found <nlohmann/json.hpp> header file!
#endif // __has_include(<yyjson.h>)

#include <rfl/Result.hpp>
#include <rfl/always_false.hpp>

namespace rfl::nlohmann {

struct Writer {
	mutable ::nlohmann::json document;

	struct OutputArrayType {
		::nlohmann::json *value{ nullptr };
	};
	struct OutputObjectType {
		::nlohmann::json *value{ nullptr };
	};
	struct OutputVarType  {
		::nlohmann::json *value{ nullptr };
	};

	/// Sets an empty array as the root element of the document.
	/// Some serialization formats require you to pass the expected size in
	/// advance. If you are not working with such a format, you can ignore the
	/// parameter `_size`. Returns the new array for further modification.
	auto array_as_root(const size_t _size) const noexcept -> OutputArrayType;

	/// Sets an empty object as the root element of the document.
	/// Some serialization formats require you to pass the expected size in
	/// advance. If you are not working with such a format, you can ignore the
	/// parameter `_size`.
	/// Returns the new object for further modification.
	auto object_as_root(const size_t _size) const noexcept -> OutputObjectType;

	/// Sets a null as the root element of the document. Returns OutputVarType
	/// containing the null value.
	auto null_as_root() const noexcept -> OutputVarType;

	/// Sets a basic value (bool, numeric, string) as the root element of the
	/// document. Returns an OutputVarType containing the new value.
	auto value_as_root(const auto &_var) const noexcept -> OutputVarType {
		document = ::nlohmann::json{ _var };
		return OutputVarType{ &document };
	}

	/// Adds an empty array to an existing array. Returns the new
	/// array for further modification.
	auto add_array_to_array(
		const size_t _size, OutputArrayType *_parent
	) const noexcept -> OutputArrayType;

	/// Adds an empty array to an existing object. The key or name of the field is
	/// signified by `_name`. Returns the new array for further modification.
	auto add_array_to_object(
		const std::string_view &_name, const size_t _size,
		OutputObjectType *_parent
	) const noexcept -> OutputArrayType;

	/// Adds an empty object to an existing array. Returns the new
	/// object for further modification.
	auto add_object_to_array(
		const size_t _size, OutputArrayType *_parent
	) const noexcept -> OutputObjectType;

	/// Adds an empty object to an existing object. The key or name of the field
	/// is signified by `_name`. Returns the new object for further modification.
	auto add_object_to_object(
		const std::string_view& _name, const size_t _size,
		OutputObjectType* _parent
	) const noexcept -> OutputObjectType;

	/// Adds a basic value (bool, numeric, string) to an array. Returns an
	/// OutputVarType containing the new value.
	auto add_value_to_array(
		const auto &_var, OutputArrayType *_parent
	) const noexcept -> OutputVarType {
		return OutputVarType{ &_parent->value->emplace_back(_var) };
	}

	/// Adds a basic value (bool, numeric, string) to an existing object. The key
	/// or name of the field is signified by `name`. Returns an
	/// OutputVarType containing the new value.
	auto add_value_to_object(
		const std::string_view &_name, const auto &_var,
		OutputObjectType *_parent
	) const noexcept -> OutputVarType {
		auto &value{ *_parent->value };
		value[_name] = _var;
		return OutputVarType{ &value[_name] };
	}

	/// Adds a null value to an array. Returns an
	/// OutputVarType containing the null value.
	auto add_null_to_array(OutputArrayType *_parent) const noexcept -> OutputVarType;

	/// Adds a null value to an existing object. The key
	/// or name of the field is signified by `name`. Returns an
	/// OutputVarType containing the null value.
	auto add_null_to_object(
		const std::string_view& _name, OutputObjectType* _parent
	) const noexcept -> OutputVarType;

	/// Signifies to the writer that we do not want to add any further elements to
	/// this array. Some serialization formats require this. If you are working
	/// with a serialization format that doesn't, just leave the function empty.
	void end_array(OutputArrayType *) const noexcept {}

	/// Signifies to the writer that we do not want to add any further elements to
	/// this object. Some serialization formats require this. If you are working
	/// with a serialization format that doesn't, just leave the function empty.
	void end_object(OutputObjectType *) const noexcept {}
};

} // namespace rfl::nlohmann

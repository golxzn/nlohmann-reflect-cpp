#include "rfl/nlohmann/Writer.hpp"

namespace rfl::nlohmann {

auto Writer::array_as_root(const size_t) const noexcept -> OutputArrayType {
	document = ::nlohmann::json::array();
	return OutputArrayType{ &document };
}

auto Writer::object_as_root(const size_t) const noexcept -> OutputObjectType {
	document = ::nlohmann::json::object();
	return OutputObjectType{ &document };
}

auto Writer::null_as_root() const noexcept -> OutputVarType {
	document = ::nlohmann::json{};
	return OutputVarType{ &document };
}

auto Writer::add_array_to_array(const size_t, OutputArrayType *_parent) const noexcept -> OutputArrayType {
	return OutputArrayType{ &_parent->value->emplace_back(::nlohmann::json::array()) };
}

auto Writer::add_array_to_object(
	const std::string_view &_name, const size_t,
	OutputObjectType *_parent
) const noexcept -> OutputArrayType {
	auto &value{ *_parent->value };
	value[_name] = ::nlohmann::json::array();
	return OutputArrayType{ &value[_name] };
}

auto Writer::add_object_to_array(
	const size_t, OutputArrayType *_parent
) const noexcept -> OutputObjectType {
	return OutputObjectType{ &_parent->value->emplace_back(::nlohmann::json::object()) };
}

auto Writer::add_object_to_object(
	const std::string_view& _name, const size_t _size,
	OutputObjectType* _parent
) const noexcept -> OutputObjectType {
	auto &value{ *_parent->value };
	value[_name] = ::nlohmann::json::object();
	return OutputObjectType{ &value[_name] };
}


auto Writer::add_null_to_array(OutputArrayType *_parent) const noexcept -> OutputVarType {
	return OutputVarType{ &_parent->value->emplace_back(::nlohmann::json{}) };
}

auto Writer::add_null_to_object(const std::string_view &_name, OutputObjectType *_parent) const noexcept -> OutputVarType {
	auto &value{ *_parent->value };
	value[_name] = ::nlohmann::json{};
	return OutputVarType{ &value[_name] };
}



} // namespace rfl::nlohmann

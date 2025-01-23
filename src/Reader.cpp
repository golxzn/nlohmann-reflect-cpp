#include "rfl/nlohmann/Reader.hpp"

namespace rfl::nlohmann {

auto Reader::get_field_from_array(
	const size_t _idx, const InputArrayType &_arr
) const noexcept -> rfl::Result<InputVarType> {
	if (_idx < _arr.value->size()) {
		return InputVarType{ &_arr.value->at(_idx) };
	}
	return rfl::Error{ "Index " + std::to_string(_idx) + " of of bounds." };
}

auto Reader::get_field_from_object(
	const std::string &_name, const InputObjectType &_obj
) const noexcept -> rfl::Result<InputVarType> {
	if (_obj.value->contains(_name)) {
		return InputVarType{ &(*_obj.value)[_name] };
	}

	return rfl::Error{ "Object contains no field named '" + _name + "'." };
}

auto Reader::is_empty(const InputVarType &_var) const noexcept -> bool {
	return _var.value->empty();
}

auto Reader::to_array(const InputVarType &_var) const noexcept -> rfl::Result<InputArrayType> {
	if (_var.value->is_array()) {
		return InputArrayType{ _var.value };
	}
	return rfl::Error{ "Could not cast to array!" };
}

auto Reader::to_object(const InputVarType &_var) const noexcept -> rfl::Result<InputObjectType> {
	if (_var.value->is_object()) {
		return InputObjectType{ _var.value };
	}
	return rfl::Error{ "Could not cast to object!" };
}

} // namespace rfl::nlohmann

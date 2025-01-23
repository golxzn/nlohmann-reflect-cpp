#pragma once

#include <rfl/Processors.hpp>
#include <rfl/internal/wrap_in_rfl_array_t.hpp>

#include "rfl/nlohmann/Parser.hpp"

namespace rfl::nlohmann {

using InputVarType = typename Reader::InputVarType;

/// Parses an object from a JSON var.
template<class T, class ...Ps>
auto read(const InputVarType &_obj) {
	return Parser<T, Processors<Ps...>>::read(Reader{}, _obj);
}

/// Parses an object from JSON using reflection.
template<class T, class ...Ps>
auto read(const std::string_view json_string) -> Result<internal::wrap_in_rfl_array_t<T>> {
	if (auto document{ ::nlohmann::json::parse(json_string, nullptr, false) }; !document.is_discarded()) {
		return read<T, Ps...>(InputVarType{ &document });
	}
	return rfl::Error{ "Could not parse document" };
}

/// Parses an object from a stringstream.
template<class T, class ...Ps>
auto read(std::istream &stream) -> Result<internal::wrap_in_rfl_array_t<T>> {
	if (auto document{ ::nlohmann::json::parse(stream, nullptr, false) }; !document.is_discarded()) {
		return read<T, Ps...>(InputVarType{ &document });
	}
	return rfl::Error{ "Could not parse document" };
}

} // namespace rfl::nlohmann


#pragma once

#include <rfl/Processors.hpp>
#include <rfl/internal/wrap_in_rfl_array_t.hpp>

#include "rfl/nlohmann/Parser.hpp"

namespace rfl::nlohmann {

struct write_format {
	int32_t indent{ -1 };
	char indent_char{ ' ' };
	bool ensure_ascii{ false };
};

/// Returns a JSON
template<class ...Ps>
auto to_json(const auto &obj) -> ::nlohmann::json {
	using T = std::remove_cvref_t<decltype(obj)>;
	using ParentType = rfl::parsing::Parent<Writer>;

	Writer w{};
	Parser<T, Processors<>>::write(w, obj, typename ParentType::Root{});
	return w.document;
}

/// Returns a JSON string
template<class ...Ps>
auto write(const auto &obj, const write_format format = {}) -> std::string {
	return to_json<Ps...>(obj).dump(format.indent, format.indent_char, format.ensure_ascii);
}

/// Writes a JSON into an ostream.
auto write(const auto &obj, std::ostream &stream) -> std::ostream & {
	return stream << to_json(obj);
}

} // namespace rfl::nlohmann



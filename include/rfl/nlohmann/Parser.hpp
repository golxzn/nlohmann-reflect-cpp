#pragma once

#include <rfl/parsing/Parser.hpp>

#include "rfl/nlohmann/Reader.hpp"
#include "rfl/nlohmann/Writer.hpp"

namespace rfl::nlohmann {

template<class T, class ProcessorsType>
using Parser = parsing::Parser<Reader, Writer, T, ProcessorsType>;

} // namespace rfl::nlohmann

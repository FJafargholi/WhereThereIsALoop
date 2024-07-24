#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace WhereThereIsAlLoop
{
    using SubCommandParameterMap = std::unordered_map<std::string, std::vector<std::string>>;

    struct CliSubcommandRegistration
    {
        std::string Name{};
        std::string UsageText{};
        std::string HelpText{};
        bool Required = false;
        size_t MinArgs = 0;
        std::optional<size_t> MaxArgs = std::nullopt;
    };

    using CliSubcommandRegistrations = std::vector<CliSubcommandRegistration>;
} // namespace WhereThereIsAlLoop

#include "pch.h"

#include "CliSubcommandRegistration.h"

namespace WhereThereIsAlLoop
{
    // Validate that the subcommands provided by the user are
    // one of the valid subcommands in the registry.
    void Validate(CliSubcommandRegistrations const & registry, SubCommandParameterMap const & userInput)
    {
        // original
        {
            for (auto const & [name, _] : userInput)
            {
                for (auto it = registry.begin(); it != registry.end(); ++it)
                {
                    if (it->Name == name)
                    {
                        break;
                    }

                    if (it == registry.end())
                    {
                        throw std::invalid_argument("Invalid subcommand: " + name);
                    }
                }
            }
        }

        // first attempt
        { // use find_if
            for (auto const & [name, _] : userInput)
            {
                auto it = std::ranges::find_if(registry, [&name](auto const & reg) { return reg.Name == name; });

                if (it == registry.end())
                {
                    throw std::invalid_argument("Invalid subcommand: " + name);
                }
            }
        }

        // second attempt
        { // use a projection
            for (auto const & [name, _] : userInput)
            {
                auto it = std::ranges::find(registry, name, &CliSubcommandRegistration::Name);

                if (it == registry.end())
                {
                    throw std::invalid_argument("Invalid subcommand: " + name);
                }
            }
        }

        // third attempt
        { // use contains and keys
            auto const & subcommandNames = userInput | std::views::keys;

            for (auto const & name : subcommandNames)
            {
                if (!std::ranges::contains /*C++23*/ (registry, name, &CliSubcommandRegistration::Name))
                {
                    throw std::invalid_argument("Invalid subcommand: " + name);
                }
            }
        }

        // fourth attempt
        { // use any_of
            auto const & subcommandNames = userInput | std::views::keys;

            if (std::ranges::any_of(
                    subcommandNames,
                    [&registry](auto const & name)
                    { return !std::ranges::contains(registry, name, &CliSubcommandRegistration::Name); }))
            {
                throw std::invalid_argument("Invalid subcommand"); // but I lost the name!
            }
        }

        // Now compare!
        {
            // Are they all correct?
            // Which one is the most readable?
            // I'm not even on C++23 yet, so I can't use contains.
        }
    }
} // namespace WhereThereIsAlLoop

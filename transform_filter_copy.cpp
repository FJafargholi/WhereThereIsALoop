#include "pch.h"

#include "DbItemDatabase.h"

namespace WhereThereIsAlLoop
{
    std::vector<ItemMetadata> GetMetadataFromMatches(std::vector<MatchResults> const & matches, DbItemDatabase const & index)
    {
        std::vector<ItemMetadata> topMatchesMetadata;
        topMatchesMetadata.reserve(matches.size());

        // original
        {
            for (auto const & match : matches)
            {
                if (auto metadata = index.TryGetItemMetadata(match.Id))
                {
                    topMatchesMetadata.push_back(metadata.value());
                }
            }
        }

        // first attempt
        { // use transform
            std::ranges::transform(
                matches,
                std::back_inserter(topMatchesMetadata),
                [&index](auto const & match)
                { return index.TryGetItemMetadata(match.Id).value_or(0); }); // but this is not the same as the original

            // could do a remove_if here, but that's not the same as the original either
        }

        // second attempt
        { // use transform and filter and copy
            auto metadata =
                matches
                | std::views::transform([&index](auto const & match) { return index.TryGetItemMetadata(match.Id); })
                | std::views::filter([](auto const & metadata) { return metadata.has_value(); })
                | std::views::transform([](auto const & metadata) { return metadata.value(); });

            std::ranges::copy(metadata, std::back_inserter(topMatchesMetadata));

            // What is Big O complexity of this code?
        }

        // third attempt ... partition and remove
        {
            // auto met
        }

        // compare
        {
            // correct and safe?
            // readable?
            // efficient?
            // I personally like the original code better
        }

        return topMatchesMetadata;
    }

    auto GetRegionIDs(std::span<MatchResults> matches, DbItemDatabase const & index)
    {

        // original intended
        {
            std::vector<RegionId> regionId(matches.size());

            for (auto const & match : matches)
            {
                regionId.push_back(ToRegionId(match.Id));
            }
        }

        // refactored
        {
            std::vector<RegionId> regionIds(matches.size());

            std::ranges::transform(
                matches,
                std::back_inserter(regionIds),
                [&index](auto const & match) { return ToRegionId(match.Id); });

            return regionIds;
        }

        // refactored
        {
            //  return matches | std::views::transform([](auto const & match) { return ToRegionId(match.Id); });
        }

        // BUT...one of these is WRONG!
        {
            // the caller is going to get a dangling reference
            // because the return value is a temporary
            // fix by returning a vector
            // return std::vector<RegionId>(matches | std::views::transform([](auto const & match) { return ToRegionId(match.Id); }));
        }
    }
} // namespace WhereThereIsAlLoop

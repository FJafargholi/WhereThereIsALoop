#include "pch.h"

#include "DbItemDatabase.h"

namespace WhereThereIsAlLoop
{
    std::vector<InsertionResult> AddItemsToDatabase(DbItemDatabase & index, std::vector<Guid> const & ids, std::vector<ItemMetadata> const & metadata)
    {
        std::vector<InsertionResult> results(ids.size());

        // original
        {
            for (size_t i = 0; i < ids.size(); ++i)
            {
                results.push_back(index.AddItems(ids[i], metadata[i]));
            }
        }

        // 1st attempt
        { // use zip, transform, and copy
            auto resultsView = std::views::zip /*C++23*/ (ids, metadata)
                             | std::views::transform([&index](auto const & pair)
                                                     { return index.AddItems(std::get<0>(pair), std::get<1>(pair)); });

            std::ranges::copy(resultsView, std::back_inserter(results));
        }

        // 2nd attempt
        { // use transform
            std::ranges::transform(
                ids,
                metadata, // YAY! transform can take two ranges
                std::back_inserter(results),
                [&index](Guid const & id, ItemMetadata const & meta) { return index.AddItems(id, meta); });
        }

        return results;
    }
} // namespace WhereThereIsAlLoop

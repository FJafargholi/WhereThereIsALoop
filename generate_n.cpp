#include "pch.h"

#include "DbItemDatabase.h"

namespace WhereThereIsAlLoop
{
    auto GetRandomIds(size_t n)
    {
        std::vector<Guid> ids(n);

        // original
        {
            for (size_t i = 0; i < n; ++i) // raw loop? :/
            {
                ids.push_back(NewGuid());
            }
        }

        // first attempt
        { // use generate_n
            std::ranges::generate_n(std::back_inserter(ids), n, NewGuid);
        }

        return ids;
    }
} // namespace WhereThereIsAlLoop

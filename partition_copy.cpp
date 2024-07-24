#include "pch.h"

#include "DbItemDatabase.h"

namespace WhereThereIsAlLoop
{
    auto Foo(std::span<ItemKey> keys)
    {
        /// ... lots of code here to retrieve all keys ...

        auto activeKeys = std::vector<ItemKey>();
        auto expiredKeys = std::vector<ItemKey>();

        // original
        {

            for (auto const & key : keys)
            {
                if (key.Status == KeyStatus::Active)
                {
                    activeKeys.push_back(key);
                }
                else
                {
                    expiredKeys.push_back(key);
                }
            }
        }

        // first attempt
        { // use partition_copy
            std::ranges::partition_copy(
                keys,
                std::back_inserter(activeKeys),
                std::back_inserter(expiredKeys),
                [](auto const & key) { return key.Status == KeyStatus::Active; });
        }
    }
} // namespace WhereThereIsAlLoop

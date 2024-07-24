#pragma once
#include <optional>

namespace WhereThereIsAlLoop
{
    /// <summary>
    /// * Success
    /// * Duplicate
    /// * Error
    /// </summary>
    enum class InsertionResult
    {
        Success,
        Duplicate,
        Error
    };

    struct MatchResults
    {
        int Id;
    };

    using RegionId = int;
    using ItemMetadata = float;
    using Guid = int;

    enum class KeyStatus
    {
        Active,
        Expired
    };

    struct ItemKey
    {
        Guid Id;
        KeyStatus Status;
    };

    class DbItemDatabase
    {
    public:

        std::optional<float> TryGetItemMetadata([[maybe_unused]] int id) const
        {
            return std::nullopt;
        }

        int GetSomething([[maybe_unused]] int tx, [[maybe_unused]] auto & regionIds)
        {
            return 0;
        }

        InsertionResult AddItems([[maybe_unused]] Guid const & id, [[maybe_unused]] ItemMetadata const & metadata)
        {
            return {};
        }
    };

    inline Guid NewGuid()
    {
        return 0;
    }

    inline RegionId ToRegionId(int id)
    {
        return id;
    }

    inline int BeginReadTransaction()
    {
        return 0;
    }

} // namespace WhereThereIsAlLoop

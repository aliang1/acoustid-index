// Copyright (C) 2011  Lukas Lalinsky
// Distributed under the MIT license, see the LICENSE file for details.

#ifndef ACOUSTID_INDEX_SEGMENT_MERGE_POLICY_H_
#define ACOUSTID_INDEX_SEGMENT_MERGE_POLICY_H_

#include "common.h"
#include "segment_info.h"
#include "segment_info_list.h"

namespace Acoustid {

class SegmentMergePolicy
{
public:
	SegmentMergePolicy(int maxMergeAtOnce = 10, int maxSegmentsPerTier = 10);
	virtual ~SegmentMergePolicy();

	void setMaxMergeAtOnce(int maxMergeAtOnce)
	{
		m_maxMergeAtOnce = maxMergeAtOnce;
	}

	int maxMergeAtOnce() const
	{
		return m_maxMergeAtOnce;
	}

	void setMaxSegmentsPerTier(int maxSegmentsPerTier)
	{
		m_maxSegmentsPerTier = maxSegmentsPerTier;
	}

	int maxSegmentsPerTier() const
	{
		return m_maxSegmentsPerTier;
	}

	QList<int> findMerges(const SegmentInfoList &infos);

private:
	int m_maxMergeAtOnce;
	int m_maxSegmentsPerTier;
};

}

#endif

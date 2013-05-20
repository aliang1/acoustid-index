// Copyright (C) 2011  Lukas Lalinsky
// Distributed under the MIT license, see the LICENSE file for details.

#include <gtest/gtest.h>
#include "util/test_utils.h"
#include "store/ram_directory.h"
#include "store/input_stream.h"
#include "store/output_stream.h"
#include "top_hits_collector.h"
#include "index.h"
#include "index_writer.h"
#include "index_reader.h"

using namespace Acoustid;

TEST(IndexReaderTest, Get)
{
	DirectorySharedPtr dir(new RAMDirectory());
	IndexSharedPtr index(new Index(dir, true));

	uint32_t fp[] = { 7, 9, 12 };

	{
		IndexWriter writer(index);
		writer.addDocument(1, fp, 3);
		writer.commit();
	}

	{
		IndexReader reader(index);
		uint32_t *fp2;
		size_t length;
		bool result = reader.get(1, &fp2, &length);
		ASSERT_TRUE(result);
		ASSERT_EQ(3, length);
		ASSERT_INTARRAY_EQ(fp, fp2, length);
		delete fp2;
	}

	{
		IndexReader reader(index);
		uint32_t *fp2;
		size_t length;
		bool result = reader.get(2, &fp2, &length);
		ASSERT_FALSE(result);
		delete fp2;
	}
}

TEST(IndexReaderTest, Search)
{
	DirectorySharedPtr dir(new RAMDirectory());
	IndexSharedPtr index(new Index(dir, true));

	uint32_t fp[] = { 7, 9, 12 };

	{
		IndexWriter writer(index);
		writer.addDocument(1, fp, 3);
		writer.commit();
		writer.addDocument(2, fp, 3);
		writer.commit();
	}

	{
		IndexReader reader(index);
		TopHitsCollector collector(100);
		reader.search(fp, 3, &collector);
		ASSERT_EQ(2, collector.topResults().size());
		ASSERT_EQ(1, collector.topResults().at(0).id());
		ASSERT_EQ(3, collector.topResults().at(0).score());
		ASSERT_EQ(2, collector.topResults().at(1).id());
		ASSERT_EQ(3, collector.topResults().at(1).score());
	}
}


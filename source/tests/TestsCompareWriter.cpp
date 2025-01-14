/*
	MIT No Attribution

	Copyright 2021-2022 Mr. Hands

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to
	deal in the Software without restriction, including without limitation the
	rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
	sell copies of the Software, and to permit persons to whom the Software is
	furnished to do so.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.
*/

#include <gtest/gtest.h>
#include <Panini.hpp>

TEST(CompareWriter, WriteNewFile)
{
	using namespace panini;

	CompareWriterConfig c;
	c.filePath = "compare_write.txt";
	std::filesystem::remove(c.filePath);

	CompareWriter w(c);
	w << "I'll catch you next time, Gadget!";
	EXPECT_TRUE(w.IsChanged());
	EXPECT_TRUE(w.Commit());

	std::ifstream f(c.filePath, std::ios::in | std::ios::binary);
	EXPECT_TRUE(f.is_open());
	std::stringstream ss;
	ss << f.rdbuf();

	EXPECT_STREQ("I'll catch you next time, Gadget!", ss.str().c_str());
}

TEST(CompareWriter, PreventDoubleCommit)
{
	using namespace panini;

	CompareWriterConfig c;
	c.filePath = "compare_double_commit.txt";
	std::filesystem::remove(c.filePath);

	std::ofstream p(c.filePath, std::ios::out | std::ios::binary);
	p << "Won't they always love you?";
	p.close();

	CompareWriter w(c);
	w << "Yes, they will.";
	EXPECT_TRUE(w.IsChanged());
	EXPECT_TRUE(w.Commit());

	EXPECT_FALSE(w.IsChanged());
	EXPECT_FALSE(w.Commit());
}

TEST(CompareWriter, ScopedCommit)
{
	using namespace panini;

	CompareWriterConfig c;
	c.filePath = "compare_scoped_commit.txt";
	std::filesystem::remove(c.filePath);

	{
		CompareWriter w(c);
		w << "Ballad Heaven";
	}

	std::ifstream f(c.filePath, std::ios::in | std::ios::binary);
	EXPECT_TRUE(f.is_open());
	std::stringstream ss;
	ss << f.rdbuf();

	EXPECT_STREQ("Ballad Heaven", ss.str().c_str());
}

TEST(CompareWriter, FileExistsAndOutputWasUnchanged)
{
	using namespace panini;

	CompareWriterConfig c;
	c.filePath = "compare_exists.txt";
	std::filesystem::remove(c.filePath);

	std::ofstream p(c.filePath, std::ios::out | std::ios::binary);
	p << "TRUE\nTRUE\nFALSE";
	p.close();

	CompareWriter w(c);
	w << "TRUE\nTRUE\nFALSE";
	EXPECT_FALSE(w.IsChanged());
	EXPECT_FALSE(w.Commit());

	std::ifstream f(c.filePath, std::ios::in | std::ios::binary);
	EXPECT_TRUE(f.is_open());
	std::stringstream ss;
	ss << f.rdbuf();

	EXPECT_STREQ("TRUE\nTRUE\nFALSE", ss.str().c_str());
}

TEST(CompareWriter, FileExistsAndOutputWasChanged)
{
	using namespace panini;

	CompareWriterConfig c;
	c.filePath = "compare_changed.txt";
	std::filesystem::remove(c.filePath);

	std::ofstream p(c.filePath, std::ios::out | std::ios::binary);
	p << "going to { the moon }";
	p.close();

	CompareWriter w(c);
	w << "going to { mars }";
	EXPECT_TRUE(w.IsChanged());
	EXPECT_TRUE(w.Commit());

	std::ifstream f(c.filePath, std::ios::in | std::ios::binary);
	EXPECT_TRUE(f.is_open());
	std::stringstream ss;
	ss << f.rdbuf();

	EXPECT_STREQ("going to { mars }", ss.str().c_str());
}

TEST(CompareWriter, WindowsNewLines)
{
	using namespace panini;

	CompareWriterConfig c;
	c.filePath = "compare_windows.txt";
	std::filesystem::remove(c.filePath);

	std::ofstream p(c.filePath, std::ios::out | std::ios::binary);
	p << "Actually,\r\nI *love*\r\nstrPascalCase";
	p.close();

	CompareWriter w(c);
	w << "Actually,\r\nI *love*\r\nstrPascalCase";
	EXPECT_FALSE(w.IsChanged());
	EXPECT_FALSE(w.Commit());

	std::ifstream f(c.filePath, std::ios::in | std::ios::binary);
	EXPECT_TRUE(f.is_open());
	std::stringstream ss;
	ss << f.rdbuf();

	EXPECT_STREQ("Actually,\r\nI *love*\r\nstrPascalCase", ss.str().c_str());
}

TEST(CompareWriter, DeprecatedConstructor)
{
	using namespace panini;

	std::filesystem::path fp = "deprecated.txt";
	std::filesystem::remove(fp);

	CompareWriter w(fp);
	w << "Please don't use me anymore!";
	EXPECT_TRUE(w.IsChanged());
	EXPECT_TRUE(w.Commit());

	std::ifstream f(fp, std::ios::in | std::ios::binary);
	EXPECT_TRUE(f.is_open());
	std::stringstream ss;
	ss << f.rdbuf();

	EXPECT_STREQ("Please don't use me anymore!", ss.str().c_str());
}

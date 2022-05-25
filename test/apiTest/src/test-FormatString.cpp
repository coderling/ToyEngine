#include<gtest/gtest.h>
#include<FormatString.hpp>

#include<fstream>
#include<string>

TEST(FormatString, Output)
{
	const std::string filename = "format_out.bytes";
	std::fstream fs(filename, std::ios::out | std::ios::binary | std::ios::in | std::ios::trunc);
	EXPECT_TRUE(fs.is_open());

	Toy::StreamOutput(fs, static_cast<double>(3.14));
	Toy::StreamOutput(fs, "abc");

	fs.seekp(0);
	double d = 0;
	fs >> d;
	EXPECT_EQ(d, 3.14);

	std::string str;
	fs >> str;
	EXPECT_EQ(str, std::string("abc"));
	fs.close();
}

TEST(FormatString, StreamFormatOutput)
{
	const std::string filename = "format_out.bytes";
	std::fstream fs(filename, std::ios::out | std::ios::binary | std::ios::in | std::ios::trunc);
	EXPECT_TRUE(fs.is_open());
	
	constexpr std::string_view format = "my name is {} age is {}\n";
	std::string name = "coderling";
	int age = 30;
	std::string str;
	Toy::StreamFormatOutput(fs, format, name, age);
	Toy::StreamFormatOutput(fs, format, name, age, "rest");
	fs.seekp(0);
	std::getline(fs, str);
	EXPECT_EQ(str, "my name is coderling age is 30");
	std::getline(fs, str);
	EXPECT_EQ(str, "my name is coderling age is 30");
	fs.close();
}

TEST(FormatString, FormatString)
{
	constexpr std::string_view format = "my name is {} age is {}";
	std::string name = "coderling";
	int age = 30;
	std::string str = Toy::FormatString(format, name, age);
	EXPECT_EQ(str, "my name is coderling age is 30");
	str = Toy::FormatString(format, name, age, "rest");
	EXPECT_EQ(str, "my name is coderling age is 30");
}
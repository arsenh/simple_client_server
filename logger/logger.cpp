#include "logger.hpp"

#include <iostream>
#include <cassert>
#include <chrono>
#include <algorithm>

dolly::logger::logger& dolly::logger::logger::
get() noexcept
{
	static logger l;
	return l;
}

bool dolly::logger::logger::
setupLogger(const std::string path, const level l)
{
	if (! std::filesystem::is_directory(path)) {
		return false;
	}
	setLevel(l);
	std::string fileName = generateFileName();
	std::string filePath = path + fileName;
	mFileStream.open(filePath, std::ios::out | std::ios::app);
	if (mFileStream.fail()) {
		throw std::ios_base::failure(std::strerror(errno));
	}
	mFileStream.exceptions(mFileStream.exceptions()
		| std::ios::failbit
		| std::ifstream::badbit);
	assert(mFileStream.is_open());
}

void dolly::logger::logger::
setLevel(level l) noexcept
{
	mLevel = l;
}

void dolly::logger::logger::
fatal(const std::string mess) noexcept
{
	assert(mFileStream.is_open());
	if (static_cast<int>(mLevel) >= static_cast<int>(level::fatal)) {
		mFileStream << "FATAL: " << mess << std::endl;
	}
}

void dolly::logger::logger::
critical(const std::string mess) noexcept
{
	assert(mFileStream.is_open());
	if (static_cast<int>(mLevel) >= static_cast<int>(level::critical)) {
		mFileStream << "CRITICAL: " << mess << std::endl;
	}
}

void dolly::logger::logger::
error(const std::string mess) noexcept
{
	assert(mFileStream.is_open());
	if (static_cast<int>(mLevel) >= static_cast<int>(level::error)) {
		mFileStream << "ERROR: " << mess << std::endl;
	}
}

void dolly::logger::logger::
warning(const std::string mess) noexcept
{
	assert(mFileStream.is_open());
	if (static_cast<int>(mLevel) >= static_cast<int>(level::warning)) {
		mFileStream << "WARNING: " << mess << std::endl;
	}
}

void dolly::logger::logger::
notice(const std::string mess) noexcept
{
	assert(mFileStream.is_open());
	if (static_cast<int>(mLevel) >= static_cast<int>(level::notice)) {
		mFileStream << "NOTICE: " << mess << std::endl;
	}
}

void dolly::logger::logger::
information(const std::string mess) noexcept
{
	assert(mFileStream.is_open());
	if (static_cast<int>(mLevel) >= static_cast<int>(level::information)) {
		mFileStream << "INFORMATION: " << mess << std::endl;
	}
}

void dolly::logger::logger::
debug(const std::string mess) noexcept
{
	assert(mFileStream.is_open());
	if (static_cast<int>(mLevel) >= static_cast<int>(level::debug)) {
		mFileStream << "DEBUG: " << mess << std::endl;
	}
}

void dolly::logger::logger::
trace(const std::string mess) noexcept
{
	assert(mFileStream.is_open());
	if (static_cast<int>(mLevel) >= static_cast<int>(level::trace)) {
		mFileStream << "TRACE: " << mess << std::endl;
	}
}

dolly::logger::logger::
logger()
	: mLevel {level::none}
	, mFileStream{}
{

}

std::string dolly::logger::logger::
generateFileName() const noexcept
{
	const std::string prefix = "loggerOutput_";
	const std::string format = ".txt";
	const auto now = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(now);
	std::string str(30, '\0');
	std::strftime(&str[0], str.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
	std::transform(std::begin(str), std::end(str), std::begin(str), [](char c) {
	if (' ' == c) {
		return c = '_';
	}
	if (':' == c) {
		return c = '-';
	}
	});
	return prefix + str + format;
}

dolly::logger::logger::
~logger()
{
	assert(mFileStream.is_open());
	mFileStream.close();
}

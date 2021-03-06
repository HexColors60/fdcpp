/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Steffen Nuessle
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGqEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <unistd.h>
#include <sys/syscall.h>
#include <sys/stat.h>

#include <utility>

#include <fds/memfd.hpp>
#include <util/throw.hpp>

static const char *tag = "memfd";

static int memfd_create(const char *name, int flags)
{
    return static_cast<int>(syscall(SYS_memfd_create, name, flags));
}

namespace fd {

memfd::memfd(const char *name, int flags)
    : iodescriptor(memfd_create(name, flags))
{
    if (_fd < 0)
        throw_system_error(tag, "memfd()");
}

memfd::memfd(const std::string &name, int flags)
    : memfd(name.c_str(), flags)
{
}

memfd::memfd(descriptor &&other)
    : iodescriptor(std::move(other))
{
    if (_fd < 0)
        throw_system_error(tag, "memfd()", EBADF);
}


memfd::memfd(const memfd &other)
: iodescriptor(::dup(other._fd))
{
    if (_fd < 0)
        throw_system_error(tag, "dup()");
}

const memfd &memfd::operator=(const memfd &other) const
{
    int err = ::dup2(other._fd, _fd);
    if (err < 0)
        throw_system_error(tag, "dup2()");
    
    return *this;
}

memfd memfd::dup() const
{
    return memfd(*this);
}

void memfd::dup2(const memfd &other) const
{
    *this = other;
}

void memfd::ftruncate(size_t size) const
{
    auto err = ::ftruncate(_fd, static_cast<off_t>(size));
    if (err < 0)
        throw_system_error(tag, "ftruncate()");
}

void memfd::fstat(struct stat &st) const
{
    auto err = ::fstat(_fd, &st);
    if (err < 0)
        throw_system_error(tag, "fstat()");
}


}
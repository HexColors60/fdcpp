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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <sys/un.h>
#include <string.h>

#include <utility>

#include <easy/unix_socket.hpp>

namespace fd {

namespace easy {

namespace unix_socket {

socket client(const char *path)
{
    struct sockaddr_un addr;
    
    addr.sun_family = AF_UNIX;
    *stpncpy(addr.sun_path, path, sizeof(addr.sun_path)) = '\0';
    
    auto socket = fd::socket(AF_UNIX, SOCK_STREAM);
    socket.connect(addr);
    
    return socket;
}

socket client(const std::string &path)
{
    return client(path.c_str());
}

socket server(const char *path, int backlog)
{
    struct sockaddr_un addr;
    
    addr.sun_family = AF_UNIX;
    *stpncpy(addr.sun_path, path, sizeof(addr.sun_path)) = '\0';
    
    auto socket = fd::socket(AF_UNIX, SOCK_STREAM);
    
    socket.bind(addr);
    socket.listen(backlog);
    
    return socket;
}

socket server(const std::string &path, int backlog)
{
    return server(path.c_str(), backlog);
}

}
}
}
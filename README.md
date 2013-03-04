amqp.lua
========

RabbitMQ bindings for Lua

The amqp.lua package adds support for sending messages to RabbitMQ via LuaJIT FFI.  This allows a Lua programmer to
communicate with other programs using enterprise grade messaging infrasturcture.  The module amqp.lua makes use of 
LuaJIT's awesome foreign function interface (FFI) to invoke the librabbitmq's functions directly.  It exposes a 
simplified interface to librabbitmq natively, but also preserves the ability of an intrepid programmer to use the
full depth of the upstream library.

Prerequisites:
==============

* librabbitmq - https://github.com/alanxz/rabbitmq-c.git
* luajit 2.0.1 - http://luajit.org/download.html 

Currently both a recent copy of librabbitmq (head was used for development) and a copy of LuaJIT are required for
use.  These have only been tested on Mac OS X at the time of writing, but should soon be verified on Linux as well.


Getting Started:
================

```lua
  local amqp = require('amqp')
  amqp.connect('amqp://guest:guest@127.0.0.1:5672/')
  amqp.send("test","test","this is a test")
  amqp.disconnect()
```

This sample code will connect to a RabbitMQ server and send a message "this is a test" to the exchange "test" with a
routing key of "test".  It connects with the default credential for most RabbitMQ servers, but you could easily specify
your own amqp:// url to connect to any server.  A sample application send.lua, exists to demonstrate how to use it as 
a command line tool to send messages to an exchange and a routing key.

Application Programming Interface
=================================

  TODO


License
=======

Copyright (c) 2013, David J Goehrig <dave@dloh.org>
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
disclaimer. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and 
the following disclaimer in the documentation and/or other materials provided with the distribution.

Neither the name of the project nor the names of its contributors may be used to endorse or promote products derived
from this software without specific prior written permission.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

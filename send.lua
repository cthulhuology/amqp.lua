#!/usr/bin/env luajit 
--
-- © 2013 David J Goehrig <dave@dloh.org>
--
-- Copyright (c) 2013, David J Goehrig <dave@dloh.org>
-- All rights reserved.
--
-- Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
-- following conditions are met:
--
-- Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
-- disclaimer. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and 
-- the following disclaimer in the documentation and/or other materials provided with the distribution.
--
-- Neither the name of the project nor the names of its contributors may be used to endorse or promote products derived
-- from this software without specific prior written permission.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
-- CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
-- MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
-- CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
-- (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
-- INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
-- (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
-- POSSIBILITY OF SUCH DAMAGE.
--

amqp = require('amqp')

if #arg < 2 then
	print("Usage: send.lua exchange routing_key [message]")
	os.exit()
elseif #arg < 3 then
	message = io.stdin:read('*a')
else 
	message = arg[3]	-- assume we're getting it on the command line
end

amqp.connect('amqp://guest:guest@127.0.0.1:5672/')

amqp.send(arg[1],arg[2],message)

amqp.disconnect()

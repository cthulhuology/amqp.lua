-- amqp module
-- 
-- © 2013 David J Goehrig <dave@dloh.org>
--

module("amqp",package.seeall)

local ffi = require('ffi')
ffi.cdef(io.open('ffi-amqp.h'):read('*a'))

local rabbitmq = ffi.load('rabbitmq')

return rabbitmq

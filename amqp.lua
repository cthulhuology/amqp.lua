-- amqp module
-- 
-- © 2013 David J Goehrig <dave@dloh.org>
--

module("amqp",package.seeall)

local ampq = { 
	AMQP_PROTOCOL_VERSION_MAJOR = 0, 
	AMQP_PROTOCOL_VERSION_MINOR = 9,
	AMQP_PROTOCOL_VERSION_REVISION = 1,
	AMQP_PROTOCOL_PORT = 5672,
	AMQP_FRAME_METHOD = 1,
	AMQP_FRAME_HEADER = 2,
	AMQP_FRAME_BODY = 3,
	AMQP_FRAME_HEARTBEAT = 8,
	AMQP_FRAME_MIN_SIZE = 4096,
	AMQP_FRAME_END = 206,
	AMQP_REPLY_SUCCESS = 200,
	AMQP_CONTENT_TOO_LARGE = 311,
	AMQP_NO_ROUTE = 312,
	AMQP_NO_CONSUMERS = 313,
	AMQP_ACCESS_REFUSED = 403,
	AMQP_NOT_FOUND = 404,
	AMQP_RESOURCE_LOCKED = 405,
	AMQP_PRECONDITION_FAILED = 406,
	AMQP_CONNECTION_FORCED = 320,
	AMQP_INVALID_PATH = 402,
	AMQP_FRAME_ERROR = 501,
	AMQP_SYNTAX_ERROR = 502,
	AMQP_COMMAND_INVALID = 503,
	AMQP_CHANNEL_ERROR = 504,
	AMQP_UNEXPECTED_FRAME = 505,
	AMQP_RESOURCE_ERROR = 506,
	AMQP_NOT_ALLOWED = 530,
	AMQP_NOT_IMPLEMENTED = 540,
	AMQP_INTERNAL_ERROR = 541
}

local ffi = require('ffi')
ffi.cdef(io.open('ffi-amqp.h'):read('*a'))

local rabbitmq = ffi.load('rabbitmq')

amqp.ffi = ffi
amqp.rabbitmq = rabbitmq

function amqp.connect(url) 
	amqp.info = ffi.new('struct amqp_connection_info')
	local buffer = ffi.new('char[?]', #url)
	ffi.copy(buffer,url)
	print("Connecting to " .. url)
	rabbitmq.amqp_parse_url(buffer,amqp.info)
	amqp.connection = rabbitmq.amqp_new_connection()	
	amqp.socket = rabbitmq.amqp_open_socket(amqp.info.host,amqp.info.port)
	rabbitmq.amqp_set_sockfd(amqp.connection,amqp.socket)
	rabbitmq.amqp_login(amqp.connection, amqp.info.vhost,0,131072,0,amqp.AMQP_SASL_METHOD_PLAIN,amqp.info.user,amqp.info.password)
	
end

function amqp.user() 
	return ffi.string(amqp.info.user)
end

function amqp.password()
	return ffi.string(amqp.info.password)
end

function amqp.host()
	return ffi.string(amqp.info.host)
end	

function amqp.port()
	return amqp.info.port
end

function amqp.vhost()
	return ffi.string(amqp.info.vhost)
end

return amqp

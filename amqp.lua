-- amqp module
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

module("amqp",package.seeall)


local amqp = { 
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
	AMQP_INTERNAL_ERROR = 541,
	AMQP_CONNECTION_START_METHOD = 0x000A000A,
	AMQP_CONNECTION_START_OK_METHOD   = 0x000A000B,
	AMQP_CONNECTION_SECURE_METHOD   = 0x000A0014,
	AMQP_CONNECTION_SECURE_OK_METHOD   = 0x000A0015,
	AMQP_CONNECTION_TUNE_METHOD   = 0x000A001E,
	AMQP_CONNECTION_TUNE_OK_METHOD   = 0x000A001F,
	AMQP_CONNECTION_OPEN_METHOD   = 0x000A0028,
	AMQP_CONNECTION_OPEN_OK_METHOD   = 0x000A0029,
	AMQP_CONNECTION_CLOSE_METHOD   = 0x000A0032,
	AMQP_CONNECTION_CLOSE_OK_METHOD   = 0x000A0033,
	AMQP_CHANNEL_OPEN_METHOD   = 0x0014000A,
	AMQP_CHANNEL_OPEN_OK_METHOD   = 0x0014000B,
	AMQP_CHANNEL_FLOW_METHOD   = 0x00140014,
	AMQP_CHANNEL_FLOW_OK_METHOD   = 0x00140015,
	AMQP_CHANNEL_CLOSE_METHOD   = 0x00140028,
	AMQP_CHANNEL_CLOSE_OK_METHOD   = 0x00140029,
	AMQP_ACCESS_REQUEST_METHOD   = 0x001E000A,
	AMQP_ACCESS_REQUEST_OK_METHOD   = 0x001E000B,
	AMQP_EXCHANGE_DECLARE_METHOD   = 0x0028000A,
	AMQP_EXCHANGE_DECLARE_OK_METHOD   = 0x0028000B,
	AMQP_EXCHANGE_DELETE_METHOD   = 0x00280014,
	AMQP_EXCHANGE_DELETE_OK_METHOD   = 0x00280015,
	AMQP_EXCHANGE_BIND_METHOD   = 0x0028001E,
	AMQP_EXCHANGE_BIND_OK_METHOD   = 0x0028001F,
	AMQP_EXCHANGE_UNBIND_METHOD   = 0x00280028,
	AMQP_EXCHANGE_UNBIND_OK_METHOD   = 0x00280033,
	AMQP_QUEUE_DECLARE_METHOD   = 0x0032000A,
	AMQP_QUEUE_DECLARE_OK_METHOD   = 0x0032000B,
	AMQP_QUEUE_BIND_METHOD   = 0x00320014,
	AMQP_QUEUE_BIND_OK_METHOD   = 0x00320015,
	AMQP_QUEUE_PURGE_METHOD   = 0x0032001E,
	AMQP_QUEUE_PURGE_OK_METHOD   = 0x0032001F,
	AMQP_QUEUE_DELETE_METHOD   = 0x00320028,
	AMQP_QUEUE_DELETE_OK_METHOD   = 0x00320029,
	AMQP_QUEUE_UNBIND_METHOD   = 0x00320032,
	AMQP_QUEUE_UNBIND_OK_METHOD   = 0x00320033,
	AMQP_BASIC_QOS_METHOD   = 0x003C000A,
	AMQP_BASIC_QOS_OK_METHOD   = 0x003C000B,
	AMQP_BASIC_CONSUME_METHOD   = 0x003C0014,
	AMQP_BASIC_CONSUME_OK_METHOD   = 0x003C0015,
	AMQP_BASIC_CANCEL_METHOD   = 0x003C001E,
	AMQP_BASIC_CANCEL_OK_METHOD   = 0x003C001F,
	AMQP_BASIC_PUBLISH_METHOD   = 0x003C0028,
	AMQP_BASIC_RETURN_METHOD   = 0x003C0032,
	AMQP_BASIC_DELIVER_METHOD   = 0x003C003C,
	AMQP_BASIC_GET_METHOD   = 0x003C0046,
	AMQP_BASIC_GET_OK_METHOD   = 0x003C0047,
	AMQP_BASIC_GET_EMPTY_METHOD   = 0x003C0048,
	AMQP_BASIC_ACK_METHOD   = 0x003C0050,
	AMQP_BASIC_REJECT_METHOD   = 0x003C005A,
	AMQP_BASIC_RECOVER_ASYNC_METHOD   = 0x003C0064,
	AMQP_BASIC_RECOVER_METHOD   = 0x003C006E,
	AMQP_BASIC_RECOVER_OK_METHOD   = 0x003C006F,
	AMQP_BASIC_NACK_METHOD   = 0x003C0078,
	AMQP_TX_SELECT_METHOD   = 0x005A000A,
	AMQP_TX_SELECT_OK_METHOD   = 0x005A000B,
	AMQP_TX_COMMIT_METHOD   = 0x005A0014,
	AMQP_TX_COMMIT_OK_METHOD   = 0x005A0015,
	AMQP_TX_ROLLBACK_METHOD   = 0x005A001E,
	AMQP_TX_ROLLBACK_OK_METHOD   = 0x005A001F,
	AMQP_CONFIRM_SELECT_METHOD   = 0x0055000A,
	AMQP_CONFIRM_SELECT_OK_METHOD   = 0x0055000B,
	AMQP_CONNECTION_CLASS = 0x000A,
	AMQP_CHANNEL_CLASS = 0x0014,
	AMQP_ACCESS_CLASS = 0x001E,
	AMQP_EXCHANGE_CLASS = 0x0028,
	AMQP_QUEUE_CLASS = 0x0032,
	AMQP_BASIC_CLASS = 0x003C,
	AMQP_BASIC_CONTENT_TYPE_FLAG = 32768,
	AMQP_BASIC_CONTENT_ENCODING_FLAG = 16384,
	AMQP_BASIC_HEADERS_FLAG = 8192,
	AMQP_BASIC_DELIVERY_MODE_FLAG = 4096,
	AMQP_BASIC_PRIORITY_FLAG = 2048,
	AMQP_BASIC_CORRELATION_ID_FLAG = 1024,
	AMQP_BASIC_REPLY_TO_FLAG = 512,
	AMQP_BASIC_EXPIRATION_FLAG = 256,
	AMQP_BASIC_MESSAGE_ID_FLAG = 128,
	AMQP_BASIC_TIMESTAMP_FLAG = 64,
	AMQP_BASIC_TYPE_FLAG = 32,
	AMQP_BASIC_USER_ID_FLAG = 16,
	AMQP_BASIC_APP_ID_FLAG = 8,
	AMQP_BASIC_CLUSTER_ID_FLAG = 4,
	AMQP_TX_CLASS = 0x005A,
	AMQP_CONFIRM_CLASS = 0x0055
}

local ffi = require('ffi')
ffi.cdef(io.open('ffi-amqp.h'):read('*a'))

local rabbitmq = ffi.load('rabbitmq')

amqp.ffi = ffi
amqp.rabbitmq = rabbitmq

function amqp.die_on_error(message,reply)
	if not reply then reply = rabbitmq.amqp_get_rpc_reply(amqp.connection) end
        if (reply.reply_type == rabbitmq.AMQP_RESPONSE_LIBRARY_EXCEPTION or reply.reply_type == AMQP_RESPONSE_SERVER_EXCEPTION) then
		print(message .. ": " .. ffi.string(rabbitmq.amqp_error_string(reply.library_error)))
	end
	return reply
end

function amqp.connect(url) 
	amqp.info = ffi.new('struct amqp_connection_info')
	local buffer = ffi.new('char[?]', #url)
	ffi.copy(buffer,url)
	rabbitmq.amqp_parse_url(buffer,amqp.info)
	amqp.connection = rabbitmq.amqp_new_connection()	
	amqp.socket = rabbitmq.amqp_open_socket(amqp.info.host,amqp.info.port)
	rabbitmq.amqp_set_sockfd(amqp.connection,amqp.socket)
	if (ffi.string(amqp.info.vhost) == "" ) then
		amqp.info.vhost = ffi.new('char[?]',1)
		ffi.copy(amqp.info.vhost,"/")
	end
	amqp.die_on_error("Failed to login",
		rabbitmq.amqp_login(amqp.connection, amqp.info.vhost,0,131072,0,0,amqp.info.user,amqp.info.password))
	amqp.channel = 1
	rabbitmq.amqp_channel_open(amqp.connection,amqp.channel)
end

function amqp.send(exchange,routing_key,message)
	local props = ffi.new('struct amqp_basic_properties_t_')
	props._flags = bit.bor(amqp.AMQP_BASIC_CONTENT_TYPE_FLAG, amqp.AMQP_BASIC_DELIVERY_MODE_FLAG)
	props.content_type = rabbitmq.amqp_cstring_bytes("text/plain")
	props.delivery_mode = 2
	local ex_buffer = rabbitmq.amqp_cstring_bytes(exchange)
	local rk_buffer = rabbitmq.amqp_cstring_bytes(routing_key)
	local msg_buffer = rabbitmq.amqp_cstring_bytes(message)
	rabbitmq.amqp_basic_publish(amqp.connection,amqp.channel,ex_buffer,rk_buffer,0,0,props,msg_buffer)
end

function amqp.receive(exchange,routing_key,queue,kind)
	if queue then Q = rabbitmq.amqp_cstring_bytes(queue) else Q = rabbitmq.amqp_empty_bytes end
	if routing_key then R = rabbitmq.amqp_cstring_bytes(routing_key) else R = rabbitmq.amqp_empty_bytes end
	if exchange  then E = rabbitmq.amqp_cstring_bytes(exchange) else E = rabbitmq.amqp_empty_bytes end
	if kind then K = rabbitmq.amqp_cstring_bytes(kind) else K = rabbitmq.amqp_cstring_bytes("topic") end
	resp = rabbitmq.amqp_exchange_declare(amqp.connection, amqp.channel, E, K, 0, 0, rabbitmq.amqp_empty_table)
	resp = rabbitmq.amqp_queue_declare(amqp.connection, amqp.channel, Q, 0, 0, 0, 1,rabbitmq.amqp_empty_table)
	amqp.die_on_error("Failed to declare queue")
	amqp.queue = ffi.string(resp.queue.bytes)
	print("Binding " .. queue .. " -> " .. routing_key .. " on " .. exchange)
	rabbitmq.amqp_queue_bind(amqp.connection,amqp.channel,Q,E,R,rabbitmq.amqp_empty_table)
	amqp.die_on_error("Failed to bind queue")
	rabbitmq.amqp_basic_consume(amqp.connection, amqp.channel, Q, rabbitmq.amqp_empty_bytes, 0, 1, 0, rabbitmq.amqp_empty_table)
	amqp.die_on_error("Failed to register consumer");
end

function amqp.wait(fun)
	frame = ffi.new('struct amqp_frame_t_')	
	while true do
		rabbitmq.amqp_maybe_release_buffers(amqp.connection)					-- possibly free some memory
		result = rabbitmq.amqp_simple_wait_frame(amqp.connection, frame)
		if result < 0 then return end 								-- error 
    		if not frame.frame_type == amqp.AMQP_FRAME_METHOD then goto continue end
		if not frame.payload.method.id == amqp.AMQP_BASIC_DELIVER_METHOD then goto continue end
		result = rabbitmq.amqp_simple_wait_frame(amqp.connection, frame)			-- wait again for header
		if result < 0 then return end								-- error
		if not frame.frame_type == amqp.AMQP_FRAME_HEADER then return end			-- missing header
		target = frame.payload.properties.body_size
		received = 0
		while received < target do
			result = rabbitmq.amqp_simple_wait_frame(amqp.connection, frame)		-- wait for content
			if result < 0 then return end							-- error
      			if not frame.frame_type == amqp.AMQP_FRAME_BODY then return end			-- missing body
			received = received + frame.payload.body_fragment.len
			fun(ffi.string(frame.payload.body_fragment.bytes, frame.payload.body_fragment.len))
		end
		received = received + 1
		::continue::
	end
end

function amqp.disconnect()
	rabbitmq.amqp_channel_close(amqp.connection, amqp.channel, amqp.AMQP_REPLY_SUCCESS)
  	rabbitmq.amqp_connection_close(amqp.connection, amqp.AMQP_REPLY_SUCCESS)
  	rabbitmq.amqp_destroy_connection(amqp.connection)
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

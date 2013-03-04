
amqp = require('amqp')

if #arg < 3 then
	print("Usage: send.lua exchange routing_key message")
	os.exit()
end

amqp.connect('amqp://guest:guest@127.0.0.1:5672/')

amqp.send(arg[1],arg[2],arg[3])

amqp.disconnect()

print("Starting Client ...")
filename = "/client.lua"

while true do
	--[blocking call to receive]--
	local sender, message, distance = rednet.receive()
	print("Message: " .. message)
	if(message == "u") then
		print("Updating...");
		--[[maintencance command mode]]--	
		local sender, message, distance = rednet.receive()
		local file = io.open(filename, "w+")
		file:write(message)
		file:close()
		os.reboot()
	else
		shell.run(filename)
	end
end

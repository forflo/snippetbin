for i=0,5-1 do
	for j=0,5-1 do
		for k=0,5-1 do
			if j%2==0 then
				print("up")
			else
				print("down")
			end
		end
		print("---")
		if i%2==0 then
			print("right")
		else
			print("left");
		end
	end
	print("---")
	print("foreward")
	
end

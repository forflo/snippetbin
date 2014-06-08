matrix1 = {{1,2,3},{2,3,4},{3,4,5}}
matrix2 = {{1,2,3},{2,3,4},{3,4,5}}
print(getmetatable(t))
print("will now set the metatable")


function matrix_add(m1, m2)
	result = {}
	for i=1,table.getn(m1) do
		for j=1,table.getn(m2) do
			result[i][j] = m1[i][j] + m2[i][j]
		end
	end
end

matrix_class = {["__add"] = "matrix_add"}

setmetatable=(matrix1, matrix_class)
setmetatable=(matrix2, matrix_class)

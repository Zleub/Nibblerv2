inspect = require 'inspect'

function love.load()
	socket = require("socket")

	t = {}
	time = 0
	height = love.window.getHeight()
	print("load")

	s = socket.connect("127.0.0.1", 4242)
	if s == nil then love.event.quit() end
	s:settimeout(0.01)
	timeout = 0.1
	time = 0
	view = {}
	champ = 0
	test = {}
end

function love.update(dt)
	width = love.window.getWidth()
	height = love.window.getHeight()
	time = time + dt
	-- print(time)
	-- print("update")
	local keys = {}

	keys.up = love.keyboard.isDown('up')
	keys.down = love.keyboard.isDown('down')
	keys.left = love.keyboard.isDown('left')
	keys.right = love.keyboard.isDown('right')


	if time > timeout then
		view = {}

		local l
		while 42 do
			local line, err = s:receive('*l')
			if err == 'closed' then
				love.event.quit()
				break
			end
			if err == 'timeout' then
				break
			end

			print(line, err)
			if line ~= nil then
				l = line
			end
		end


		for i in string.gmatch(l, "(.-,)") do
			table.insert(view, {})
			for j in string.gmatch(i, "[0-9]+") do
				-- print(j)
				table.insert(view[#view], j)
			end
		end

		print(inspect(view))

		test = {}
		local var1 = height / 2
		for i = 1,#view + 1 do
			local x = 0
			local y = var1 + height / 2
			table.insert(test, {})

			love.graphics.circle('fill', x, y, 2)
			table.insert(test[#test], {x = x, y = y})

			local tmp_size
			if view[i] then
				tmp_size = #view[i]
			else
				tmp_size = #view[i - 1] + 2
			end

			for j = 1,tmp_size do
				local size = width / tmp_size
				local x = size * j
				-- local y = var1 + height / 2
				love.graphics.circle('fill', x, y, 2)
				table.insert(test[#test], {x = x, y = y})

				-- print(j,v)
			end
			var1 = var1 / 2
		end

		-- table.insert(t, l)
		-- if #t * 12 > height then
		-- 	table.remove(t, 1)
		-- end
		time = 0
	end

	local msg = ' '
	for k,v in pairs(keys) do
		if v then
			msg = msg..k..' '
		end
	end
	s:send(msg)
end

function love.draw()
	-- width = love.window.getWidth()
	-- height = love.window.getHeight()

	local scale = 25
	depth = #view
	if depth ~= 0 then
		local tmp = view[#view]
		champ = #tmp
	end

	test = math.floor(champ / 2)
	for k,v in ipairs(view) do
		i = 1
		for j=-test,test do
			if v[j + #v - k] == '2' then love.graphics.setColor(255, 0, 0, 255)
			elseif v[j + #v - k] == '0' then love.graphics.setColor(255, 255, 255, 100)
			-- elseif v[j + #v - k] == '1' then love.graphics.setColor(100, 100, 100, 100)
			elseif v[j + #v - k] == '11' then love.graphics.setColor(0, 255, 0, 100)
			else love.graphics.setColor(255, 255, 255, 255) end
			love.graphics.rectangle("fill", i * scale, k * scale, 1 * scale, 1 * scale)
			i = i + 1
		end

		-- for i, j in ipairs(v) do
		-- 	if j == '2' then love.graphics.setColor(255, 0, 0, 255)
		-- 	else love.graphics.setColor(255, 255, 255, 255) end
		-- 	love.graphics.rectangle("fill", i * scale, k * scale, 1 * scale, 1 * scale)
		-- end
	end


	-- love.graphics.print("depth: "..depth, 0, 0)
	-- love.graphics.print("champ: "..champ, 0, 12)

	-- size = width / champ


	-- love.graphics.setColor(150, 100, 0, 255)
	-- love.graphics.rectangle('fill', 0, height / 2 + 10, width, height)
	-- love.graphics.setColor(255, 255, 255, 255)

	-- love.graphics.circle('fill', width / 2, height / 2, 10);

	-- for i,v in ipairs(test) do
	-- 	for j,v in ipairs(v) do
	-- 		if test[i + 1] then
	-- 			love.graphics.line(
	-- 				test[i][j].x, test[i][j].y,
	-- 				test[i + 1][j + 1].x, test[i + 1][j + 1].y
	-- 				)
	-- 			-- if view[i] and view[i][j] then
	-- 				if view[i][j] == '2' then
	-- 					love.graphics.circle('fill', test[i][j].x / 2 + test[i][j + 1].x  / 2, test[i][j].y / 2 + test[i + 1][j].y / 2, 2)
	-- 				elseif view[i][j] == '1' then
	-- 					love.graphics.circle('line', test[i][j].x / 2 + test[i][j + 1].x  / 2, test[i][j].y / 2 + test[i + 1][j].y / 2, 10)
	-- 				end
	-- 			-- end
	-- 		end

	-- 		if test[i][j + 1] then
	-- 			love.graphics.line(
	-- 				test[i][j].x, test[i][j].y,
	-- 				test[i][j + 1].x, test[i][j + 1].y
	-- 				)
	-- 		end
	-- 		-- if view[i] and view[i][j] then

	-- 		-- 	love.graphics.circle('fill', test[i][j].x / 2 + test[i][j + 1].x  / 2, test[i][j].y / 2 + test[i + 1][j].y / 2, 2)
	-- 		-- end
 -- 		end
	-- end

end

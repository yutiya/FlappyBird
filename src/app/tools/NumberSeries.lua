
local NumberSeries = class("NumberSeries", cc.Object)

function NumberSeries:ctor()
	self.numberSeries = {}
end

function NumberSeries:loadNumber(fmt, base)
	local fileName = nil
	for i = base, (10 - 1 + base) do
		fileName = string.format(fmt, i)
		table.insert(self.numberSeries, fileName)
	end
end

function NumberSeries:at(index)
	local atlasLoader = require("app.tools.AtlasLoader"):getInstance()
	return atlasLoader:getSpriteFrameByName(self.numberSeries[math.floor(index)+1])
end

return NumberSeries

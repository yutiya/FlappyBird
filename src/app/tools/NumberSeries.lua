
local NumberSeries = class("NumberSeries", cc.Object)

function NumberSeries:ctor()
	self.numberSeries = {}
end

function NumberSeries:loadNumber(fmt, base)
	local atlasLoader = require("app.tools.AtlasLoader"):getInstance()
	local fileName = nil
	for i = base, (10 - 1 + base) do
		fileName = string.format(fmt, i)
		table.insert(self.numberSeries, atlasLoader:getSpriteFrameByName(fileName))
	end
end

function NumberSeries:at(index)
	return self.numberSeries[index + 1]
end

return NumberSeries


local _number = nil
cc.exports.Gravity = { GRAVITY_CENTER = 1, GRAVITY_LEFT = 2, GRAVITY_RIGHT = 3 }

local Number = class("Number", cc.Object)
local atlasLoader = require("app.tools.AtlasLoader"):getInstance()

function Number:getInstance()
    if _number == nil then
        _number = Number:create()
    end
    return _number
end

function Number:destroyInstance()
	_number = nil
end

function Number:ctor()
	self.numberContainer = {}
end

function Number:loadNumber(name, fmt, base)
	local numberSeries = require("app.tools.NumberSeries"):create()
	numberSeries:loadNumber(fmt, base)
	self.numberContainer[name] = numberSeries
end

function Number:convert(name, number, gravity)
	local numberSeries = self.numberContainer[name]
	local numberZero = nil
	if (number == 0) then
		numberZero = cc.Sprite:createWithSpriteFrame(numberSeries:at(0))
		numberZero:setAnchorPoint({ x = 0.5, y = 0 })
		return numberZero
	end
	local numberNode = cc.Node:create()
	local totalWidth = 0
	local temp = nil
	local sprite = nil
	while(number > 0) 
	do
		temp = math.floor(number % 10)
		number = math.floor(number / 10)
		sprite = cc.Sprite:createWithSpriteFrame(numberSeries:at(temp))
		totalWidth = totalWidth + sprite:getContentSize().width
		numberNode:addChild(sprite)
	end

	numberZero = cc.Sprite:createWithSpriteFrame(numberSeries:at(0))
	numberNode:setContentSize({ width = totalWidth, height = numberZero:getContentSize().height })
	local singleWidth = totalWidth / (numberNode:getChildrenCount())
	local index = nil
	local offLength = 0
	local children = numberNode:getChildren()
	if (gravity == Gravity.GRAVITY_CENTER) then
		index = numberNode:getChildrenCount() / 2
		for k in ipairs(children) do
			children[k]:setAnchorPoint({ x = 0.5, y = 0 })
			offLength = singleWidth * index
			index = index - 1
			children[k]:setPositionX(offLength)
		end
	elseif (gravity == Gravity.GRAVITY_RIGHT) then
		index = numberNode:getChildrenCount()
		for k in ipairs(children) do
			children[k]:setAnchorPoint({ x = 1, y = 0 })
			offLength = singleWidth * index
			index = index - 1
			children[k]:setPositionX(offLength)
		end
	elseif (gravity == Gravity.GRAVITY_LEFT) then
		index = 0
		for k in ipairs(children) do
			children[k]:setAnchorPoint({ x = 0, y = 0 })
			offLength = singleWidth * index 
			index = index - 1
			children[k]:setPositionX(offLength)
		end
	end
	return numberNode
end

return Number

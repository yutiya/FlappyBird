
local backgroundDayName = "bg_day"
local backgroundNightName = "bg_night"

local BackgroundLayer = class("BackgroundLayer", cc.Layer)

function BackgroundLayer:ctor()
	local atlasLoader = require("app.tools.AtlasLoader"):getInstance()

	local backgroundSprite = nil
	local timeFormat = os.date("*t")
	if(timeFormat.hour >= 6 and timeFormat.hour <= 17) then
		backgroundSprite = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(backgroundDayName))
	else 
		backgroundSprite = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(backgroundNightName))
	end
	backgroundSprite:setAnchorPoint({ x = 0, y = 0 })
	backgroundSprite:setPosition({ x = 0, y = 0 })
	self:addChild(backgroundSprite)
end

return BackgroundLayer

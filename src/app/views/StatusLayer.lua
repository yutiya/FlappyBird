
local numberScore = "number_score"
local numberFont = "font"
local textReady = "text_ready"
local tutorial = "tutorial"

local number = require("app.tools.Number"):getInstance()

local StatusLayer = class("StatusLayer", cc.Layer)

function StatusLayer:ctor()

	self.bestScore = 0
	self.currentScore = 0
	self.isNewRecord = false
	
	number:loadNumber(numberFont, "font_0%02d", 48)
	number:loadNumber(numberScore, "number_score_%02d", 0)

end

function StatusLayer:showReadyStatus()
	local atlasLoader = require("app.tools.AtlasLoader"):getInstance()
	local visibleSize = cc.Director:getInstance():getVisibleSize()
	local originPoint = cc.Director:getInstance():getVisibleOrigin()

	self.scoreSprite = number:convert(numberFont, 0)
	self.scoreSprite:setPosition({ x = originPoint.x + visibleSize.width / 2, y = originPoint.y + visibleSize.height * 5 / 6 })
	self:addChild(self.scoreSprite)

	self.getreadySprite = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(textReady))
	self.getreadySprite:setPosition({ x = originPoint.x + visibleSize.width / 2, y = originPoint.y + visibleSize.height * 2 / 3 });
end

return StatusLayer
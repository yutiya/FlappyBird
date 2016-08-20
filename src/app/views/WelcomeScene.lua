--print("WelcomeScene")
-- print(string.format("xxx: %s", xxx))
local backgroundDayName = "bg_day"
local backgroundNightName = "bg_night"
local titleName = "title"
local landName = "land"

local WelcomeScene = class("WelcomeScene", cc.Scene)

function WelcomeScene:ctor()
	local visibleSize = cc.Director:getInstance():getVisibleSize()
	local origin = cc.Director:getInstance():getVisibleOrigin()
	local atlasLoader = require("app.tools.AtlasLoader"):getInstance()
	--获取当前时间的数字形式
	-- os.time()
	--获取带格式的当前时间,返回格式为table
	--[[
		year	年
		month	月	
		day		日
		hour	时
		min		分
		sec		秒
		isdst	是否使用夏令时
		wday	星期几 从星期日开始 1-7
		yday	一年中的第几天	1月1日为1
	]]
	--background
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
	--title
	local title = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(titleName))
	title:setPosition({ x = origin.x + visibleSize.width/2, y = origin.y + visibleSize.height/2 })
	self:addChild(title)
	--land1
	self.land1 = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(landName))
	self.land1:setAnchorPoint({ x = 0, y = 0 })
	self.land1:setPosition({ x = 0, y = 0 })
	self:addChild(self.land1)
	--land2
	self.land2 = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(landName))
	self.land2:setAnchorPoint({ x = 0, y = 0 })
	self.land2:setPosition({ x = self.land1:getContentSize().width - 2.0, y = 0 })
	self:addChild(self.land2)
	--schedule
	cc.Director:getInstance():getScheduler():scheduleScriptFunc(handler(self, self.scrollHand), 0.01, false)
end

function WelcomeScene:scrollHand(dt)
	self.land1:setPositionX(self.land1:getPositionX() - 2.0)
	self.land2:setPositionX(self.land1:getPositionX() + self.land1:getContentSize().width - 2.0)
	if(self.land2:getPositionX() == 0) then
		self.land1:setPositionX(0)
	end
end 

return WelcomeScene

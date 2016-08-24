
require "bit"

local _birdSprite = nil
local atlasLoader = require("app.tools.AtlasLoader"):getInstance()

cc.exports.ActionState = 
{
	ACTION_STATE_IDLE = 0,
	ACTION_STATE_FLY = 1,
	ACTION_STATE_DIE = 2
}

local BirdSprite = class("BirdSprite", cc.Object)

function BirdSprite:getInstance()
    if _birdSprite == nil then
        _birdSprite = BirdSprite:create()
    end
    return _birdSprite
end

function BirdSprite:destroyInstance()
	_birdSprite = nil
end

--随机生成小鸟
local function createBirdByRandom(obj)
	--[[if band(obj.isFirstTime, 1) then
		obj.isFirstTime = 2
	elseif band(obj.isFirstTime, 2) then
		obj.isFirstTime = 1
		return
	end]]
	math.randomseed(os.time())
	local type = math.random(3) - 1
	if type == 0 then
		obj.birdName = "bird0_0";
		obj.birdNameFormat = "bird0_%d";
	elseif type == 1 then
		obj.birdName = "bird1_0";
		obj.birdNameFormat = "bird1_%d";
	elseif type == 2 then
		obj.birdName = "bird2_0";
		obj.birdNameFormat = "bird2_%d";
	else
		obj.birdName = "bird0_0";
		obj.birdNameFormat = "bird0_%d";
	end
end

--生成小鸟飞的动画
local function createAnimation(fmt, count, fps)
	local animation = cc.Animation:create()
	animation:setDelayPerUnit(1/fps)
	local fileName = nil
	local frame = nil
	for i = 0, (count - 1) do
		fileName = string.format(fmt, i)
		frame = atlasLoader:getSpriteFrameByName(fileName)
		animation:addSpriteFrame(frame)
	end
	return animation
end

function BirdSprite:ctor()
	self.isFirstTime = 3
end

function BirdSprite:createBird()
	createBirdByRandom(self)
	local bird = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(self.birdName))
	local animation = createAnimation(self.birdNameFormat, 3, 10)
	local animate = cc.Animate:create(animation)
	self.idleAction = cc.RepeatForever:create(animate)
	local up = cc.MoveBy:create(0.4, { x = 0, y = 8 })
	local upBack = up:reverse()
	self.swingAction = cc.RepeatForever:create(cc.Sequence:create(up, upBack))
	return bird
end

function BirdSprite:idle(bird)
	self.state = ActionState.ACTION_STATE_IDLE
	bird:runAction(self.idleAction)
	bird:runAction(self.swingAction)
end

function BirdSprite:fly(bird)
	self.state = ActionState.ACTION_STATE_FLY
	bird:stopAction(self.swingAction)
end

function BirdSprite:die(bird)
	self.state = ActionState.ACTION_STATE_DIE
	bird:stopAllActions()
end

function BirdSprite:changeState(state)
	self.state = state
end

return BirdSprite

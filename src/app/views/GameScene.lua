
cc.exports.GameStatus = 
{
	GAME_STATUS_READY = 0,
	GAME_STATUS_START = 1,
	GAME_STATUS_OVER = 2
}

cc.exports.UP_PIP = 21
cc.exports.DOWN_PIP = 12
cc.exports.PIP_PASS = 30
cc.exports.PIP_NEW = 31
cc.exports.BIRD_RADIUS = 15
cc.exports.PIP_HEIGHT = 320
cc.exports.PIP_WIDTH = 52
cc.exports.PIP_SHIFT_SPEED = 80
cc.exports.PIP_DISTANCE = 120
cc.exports.PIP_INTERVAL = 180
cc.exports.PIP_COUNT = 2
cc.exports.WAIT_DISTANCE = 100

local oggWing = "sfx_wing.ogg"
local oggPoint = "sfx_point.ogg"
local oggHit = "sfx_hit.ogg"
local oggDie = "sfx_die.ogg"
local pipeUpName = "pipe_up"
local pipeDownName = "pipe_down"
local landName = "land"
local saveScoreKey = "best_score"

local GameScene = class("GameScene", cc.Layer)

local birdSprite = require("app.tools.BirdSprite"):getInstance()
local atlasLoader = require("app.tools.AtlasLoader"):getInstance()
local director = cc.Director:getInstance()
local visibleSize = director:getVisibleSize()
local origin = director:getVisibleOrigin()

function GameScene:createScene()
	local scene = cc.Scene:createWithPhysics()
	scene:getPhysicsWorld():setGravity({ x=0, y=-900 })
	-- scene:getPhysicsWorld():setDebugDrawMask(cc.PhysicsWorld.DEBUGDRAW_ALL)
	local backgroundLayer = require("app.views.BackgroundLayer"):create()
	local statusLayer = require("app.views.StatusLayer"):create()
	local gameLayer = GameScene:create()
	local optionLayer = require("app.views.OptionLayer"):create()

	gameLayer.statusDelegate = statusLayer
	gameLayer.gameScene = scene

	optionLayer.gameDelegate = gameLayer

	scene:addChild(backgroundLayer)
	scene:addChild(gameLayer)
	scene:addChild(statusLayer)
	scene:addChild(optionLayer)
	return scene
end

function GameScene:ctor()
	math.randomseed(os.time())
	
	self.gameStatus = GameStatus.GAME_STATUS_READY
	self.score = 0
	self.pips = {}

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

	self.groundNode = cc.Node:create()
	local landHeight = self.land1:getContentSize().height
	local groundBody = cc.PhysicsBody:create()
	groundBody:addShape(cc.PhysicsShapeBox:create({ width=288, landHeight }))
	groundBody:setDynamic(false)
	groundBody:setLinearDamping(0.0)
	groundBody:setContactTestBitmask(0xFFFFFFFF)
	self.groundNode:setPhysicsBody(groundBody)
	self.groundNode:setPosition(144, landHeight)
	self:addChild(self.groundNode)

	self.bird = birdSprite:createBird()
	self.bird:setPosition({ x=origin.x + visibleSize.width/3-5, y=origin.y + visibleSize.height/2+5 })
	birdSprite:idle(self.bird)
	self:addChild(self.bird)

	--schedule
	self.scrollLandSchedule = director:getScheduler():scheduleScriptFunc(handler(self, self.scrollHand), 0.01, false)
	self:scheduleUpdateWithPriorityLua(handler(self, self.update), 0)
	--onEnter onExit 事件分发
	self:registerScriptHandler(handler(self, self.onNodeEvent))
end

function GameScene:onNodeEvent(event)
	if event == "enter" then
		self:onEnter()
	elseif event == "exit" then
		self:onExit()
	end
end

function GameScene:restartGame()
	birdSprite:die(self.bird)
	self:removeChild(self.bird)
	self.bird = nil

	local scene = GameScene:createScene()
	local transition = cc.TransitionFade:create(1.3, scene)
	cc.Director:getInstance():replaceScene(transition)
end

function GameScene:onContactBegin(contact)
	self.bird:getPhysicsBody():setVelocity({ x=0, y=0 })
	self.bird:getPhysicsBody():setGravityEnable(false)
	self:gameOver()
end

function GameScene:update(dt)
	if(self.gameStatus == GameStatus.GAME_STATUS_START) then
		self:rotateBird()
		self:checkHit()
	end
end

function GameScene:scrollHand(dt)
	self.land1:setPositionX(self.land1:getPositionX() - 2.0)
	self.land2:setPositionX(self.land1:getPositionX() + self.land1:getContentSize().width - 2.0)
	if(self.land2:getPositionX() == 0) then
		self.land1:setPositionX(0)
	end

	for k in ipairs(self.pips) do
		self.pips[k]:setPositionX(self.pips[k]:getPositionX() - 2)
		if ((self.pips[k]:getPositionX()) < (-PIP_WIDTH)) then
			self.pips[k]:setTag(PIP_NEW)
			self.pips[k]:setPositionX(visibleSize.width)
			self.pips[k]:setPositionY(self:getRandomHeight())
		end
	end
end 

function GameScene:onEnter()
	local contactListener = cc.EventListenerPhysicsContact:create()
	contactListener:registerScriptHandler(handler(self, self.onContactBegin), cc.Handler.EVENT_PHYSICS_CONTACT_BEGIN)
	cc.Director:getInstance():getEventDispatcher():addEventListenerWithSceneGraphPriority(contactListener, self)
end

function GameScene:onExit()
	self:unregisterScriptHandler()
	cc.Director:getInstance():getEventDispatcher():removeEventListenersForTarget(self)
end

function GameScene:onTouch()
	if self.gameStatus == GameStatus.GAME_STATUS_OVER then
		return
	end
	cc.SimpleAudioEngine:getInstance():playEffect(oggWing)
	if self.gameStatus == GameStatus.GAME_STATUS_READY then
		local body = cc.PhysicsBody:create()
		body:addShape(cc.PhysicsShapeCircle:create(BIRD_RADIUS))
		body:setLinearDamping(0.0)
		body:setContactTestBitmask(0xFFFFFFFF)
		self.bird:setPhysicsBody(body)
		if self.statusDelegate then
			self.statusDelegate:onGameStart()
		end
		birdSprite:fly(self.bird)
		self.gameStatus = GameStatus.GAME_STATUS_START
		self:createPips()
	end
	self.bird:getPhysicsBody():setVelocity({ x=0, y=260 })
	self:rotateBird()
end

function GameScene:rotateBird()
	local verticalSpeed = self.bird:getPhysicsBody():getVelocity().y
	self.bird:setRotation(-math.min(math.max(-90, verticalSpeed*0.2+60), 30))
end

function GameScene:createPips() 
    for i = 0, PIP_COUNT-1 do
        local pipUp = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(pipeUpName))
        local pipDown = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(pipeDownName))
        local singlePip = cc.Node:create()
        
        pipUp:setPosition({ x=0, y=0 })
        pipDown:setPosition({ x=0, y=PIP_HEIGHT + PIP_DISTANCE})
        singlePip:addChild(pipDown, 0, DOWN_PIP)
        singlePip:addChild(pipUp, 0, UP_PIP)
        singlePip:setPosition({ x=visibleSize.width + i*PIP_INTERVAL + WAIT_DISTANCE, y=self:getRandomHeight() })
        local body = cc.PhysicsBody:create()
        local shapeBoxDown = cc.PhysicsShapeBox:create(pipDown:getContentSize(), cc.PHYSICSSHAPE_MATERIAL_DEFAULT, { x=0, y=PIP_HEIGHT + PIP_DISTANCE })
        body:addShape(shapeBoxDown)
        body:addShape(cc.PhysicsShapeBox:create(pipUp:getContentSize()))
        body:setDynamic(false)
        body:setContactTestBitmask(0xFFFFFFFF)
        singlePip:setPhysicsBody(body)
        singlePip:setTag(PIP_NEW)
        
        self:addChild(singlePip)
        table.insert(self.pips, singlePip)
    end
end

function GameScene:getRandomHeight() 
    return (math.random(PIP_HEIGHT/2) - 1)
end

function GameScene:checkHit() 
    for k in ipairs(self.pips) do
        if (self.pips[k]:getTag() == PIP_NEW) then
            if (self.pips[k]:getPositionX() < self.bird:getPositionX()) then
                cc.SimpleAudioEngine:getInstance():playEffect(oggPoint)
                self.score = self.score + 1
                self.statusDelegate:onGamePlaying(self.score)
                self.pips[k]:setTag(PIP_PASS)
            end
        end
    end
end

function GameScene:gameOver() 
    if (self.gameStatus == GameStatus.GAME_STATUS_OVER) then
        return
    end
    cc.SimpleAudioEngine:getInstance():playEffect(oggHit)
    local userRecord = require("app.tools.UserRecord"):getInstance()
    local bestScore = userRecord:readIntegerFromUserDefault(saveScoreKey)
    if (self.score > bestScore)  then
        userRecord:saveIntegerToUserDefault(saveScoreKey, self.score)
    end
    if self.statusDelegate then
    	self.statusDelegate:onGameEnd(self.score, bestScore)
	end
    director:getScheduler():unscheduleScriptEntry(self.scrollLandSchedule)
    cc.SimpleAudioEngine:getInstance():playEffect(oggDie)
	birdSprite:getInstance():die(self.bird)
    self.bird:setRotation(90)
    self:birdSpriteFadeOut()
    self.gameStatus = GameStatus.GAME_STATUS_OVER;
end

function GameScene:birdSpriteFadeOut()
    local animation = cc.FadeOut:create(1.5)
    local animationDone = cc.CallFunc:create(handler(self, self.birdSpriteRemove))
    local sequence = cc.Sequence:create(animation, animationDone)
    self.bird:stopAllActions()
    self.bird:runAction(sequence)
end

function GameScene:birdSpriteRemove()
    self.bird:setRotation(0)
    self:removeChild(self.bird)
    self.bird = nil
end

return GameScene

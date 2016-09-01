
local numberScore = "number_score"
local numberFont = "font"
local textReady = "text_ready"
local tutorial = "tutorial"
local white = "white"
local textGameover = "text_game_over"
local scorePanel = "score_panel"
local new = "new"
local swooshingOGG = "sfx_swooshing.ogg"
local buttonPlay = "button_play"
local buttonScore = "button_score"
local StatusLayer = class("StatusLayer", cc.Layer)
local blinkName = "blink_00"
local CURRENT_SCORE_SPRITE_TAG = 10001

local number = require("app.tools.Number"):getInstance()
local origin = cc.Director:getInstance():getVisibleOrigin()
local visibleSize = cc.Director:getInstance():getVisibleSize()
local atlasLoader = require("app.tools.AtlasLoader"):getInstance()

function StatusLayer:ctor()
	self.bestScore = 0
	self.currentScore = 0
	self.isNewRecord = false
	
	number:loadNumber(numberFont, "font_0%02d", 48)
	number:loadNumber(numberScore, "number_score_%02d", 0)

	self:showReadyStatus()
	self:loadWhiteSprite()
end

--准备状态
function StatusLayer:showReadyStatus()
	self.scoreSprite = number:convert(numberFont, 0, Gravity.GRAVITY_CENTER)
	self.scoreSprite:setPosition({ x = origin.x + visibleSize.width / 2, y = origin.y + visibleSize.height * 5 / 6 })
	self:addChild(self.scoreSprite)

	self.getreadySprite = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(textReady))
	self.getreadySprite:setPosition({ x = origin.x + visibleSize.width / 2, y = origin.y + visibleSize.height * 2 / 3 });
	self:addChild(self.getreadySprite)

	self.tutorialSprite = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(tutorial))
	self.tutorialSprite:setPosition({ x = origin.x + visibleSize.width / 2, y = origin.y + visibleSize.height / 2 })
	self:addChild(self.tutorialSprite)
end

--开始状态
function StatusLayer:showStartStatus()
	self.getreadySprite:runAction(cc.FadeOut:create(0.4))
	self.tutorialSprite:runAction(cc.FadeOut:create(0.4))
end

--结束状态
function StatusLayer:showOverStatus(currentScore, bestScore)
	self.currentScore = currentScore
	self.bestScore = bestScore
	if(currentScore > bestScore) then
		self.bestScore = currentScore
		self.isNewRecord = true
	else
		self.isNewRecord = false
	end
	self:removeChild(self.scoreSprite)
	self.scoreSprite = nil
	self:blinkFullScreen()
end

--开始
function StatusLayer:onGameStart()
	self:showStartStatus()
end

--即时更新得分
function StatusLayer:onGamePlaying(score)
	self:removeChild(self.scoreSprite)
	self.scoreSprite = nil
	self.scoreSprite = number:convert(numberFont, score, Gravity.GRAVITY_CENTER)
	self.scoreSprite:setPosition({ x = origin.x + visibleSize.width / 2, y = origin.y + visibleSize.height * 5 / 6 })
	self:addChild(self.scoreSprite)
end

--进入游戏结束
function StatusLayer:onGameEnd(currentScore, bestScore)
	self:showOverStatus(currentScore, bestScore)
end

--加载白屏
function StatusLayer:loadWhiteSprite()
	self.whiteSprite = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(white))
	self.whiteSprite:setScale(100)
	self.whiteSprite:setOpacity(0)
	self:addChild(self.whiteSprite)
end

--全屏闪白
function StatusLayer:blinkFullScreen()
	local fadeOut = cc.FadeOut:create(0.1)
	local fadeIn = cc.FadeIn:create(0.1)
	local blinkAction = cc.Sequence:create(fadeIn, fadeOut)
	local actionDone = cc.CallFunc:create(handler(self, self.fadeInGameOver))
	local sequence = cc.Sequence:create(blinkAction, actionDone)
	self.whiteSprite:stopAllActions()
	self.whiteSprite:runAction(sequence)
end

--游戏结束UI
function StatusLayer:fadeInGameOver()
	local gameoverSprite = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(textGameover))
	gameoverSprite:setPosition({ x = origin.x + visibleSize.width / 2, y = origin.y + visibleSize.height * 4 / 5 })
	self:addChild(gameoverSprite)
	local gameoverFadeIn = cc.FadeIn:create(0.5)
	local actionDone = cc.CallFunc:create(handler(self, self.jumpToScorePanel))
	local sequence = cc.Sequence:create(gameoverFadeIn, actionDone)
	gameoverSprite:stopAllActions()	
	gameoverSprite:runAction(sequence)
end

--跳出得分UI
function StatusLayer:jumpToScorePanel()
	local scorepanelSprite = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(scorePanel))
	scorepanelSprite:setPosition({ x = origin.x + visibleSize.width / 2, y = origin.y - scorepanelSprite:getContentSize().height })
	self:addChild(scorepanelSprite)
	local bestScoreSprite = number:convert(numberScore, self.bestScore, Gravity.GRAVITY_RIGHT)
	bestScoreSprite:setAnchorPoint({ x=1, y=1})
	bestScoreSprite:setPosition({x=scorepanelSprite:getContentSize().width - 28,
		y=50})
	scorepanelSprite:addChild(bestScoreSprite)
	local medalsName = self:getMedalsName(currentScore)
	if (medalsName ~= "") then
		local medalsSprite = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(medalsName))
		medalsSprite:addChild(self.blink)
		medalsSprite:setPosition({ x=54, y=58 })
		scorepanelSprite:addChild(medalsSprite)
	end

	if (self.isNewRecord) then
		local newTagSprite = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(new))
		newTagSprite:setPosition({ x=-16, y=12 })
		bestScoreSprite:addChild(newTagSprite)
	end

	local scorePanelMoveTo = cc.MoveTo:create(0.8, { x=origin.x + visibleSize.width / 2, y = origin.y + visibleSize.height / 2 + 20.0 })
	local sineIn = cc.EaseExponentialOut:create(scorePanelMoveTo)
	local actionDone = cc.CallFunc:create(handler(self, self.fadeInRestartBtn))
	local sequence = cc.Sequence:create(sineIn, actionDone)
	scorepanelSprite:stopAllActions()
	cc.SimpleAudioEngine:getInstance():playEffect(swooshingOGG)
	scorepanelSprite:runAction(sequence)
end

--进入重新开始UI
function StatusLayer:fadeInRestartBtn()
	local tempNode = cc.Node:create()
	local restartBtn = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(buttonPlay))
	local restartBtnActive = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(buttonPlay))
	restartBtnActive:setPositionY(-4)
	local menuItem = cc.MenuItemSprite:create(restartBtn, restartBtnActive)
	menuItem:registerScriptTapHandler(handler(self, self.menuRestartCallback))
	local menu = cc.Menu:create(menuItem)
	menu:setPosition({ x=origin.x + visibleSize.width/2 - restartBtn:getContentSize().width/2, y=origin.y + visibleSize.height*2/6 - 10 })
	tempNode:addChild(menu)

	local rateBtn = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(buttonScore));
	rateBtn:setPosition({ x=origin.x + visibleSize.width/2 + rateBtn:getContentSize().width/2, y=origin.y + visibleSize.height*2/6 -10 })
	tempNode:addChild(rateBtn)
	self:addChild(tempNode)
	local fadeIn = cc.FadeIn:create(0.1)
	local actionDone = cc.CallFunc:create(handler(self, self.refreshScoreCallback))
	local sequence = cc.Sequence:create(fadeIn, actionDone)
	tempNode:stopAllActions()
	tempNode:runAction(sequence)
end

--刷新分数调用
function StatusLayer:refreshScoreCallback()
	self.tempScore = 0
	self.refreshScoreSchedule = cc.Director:getInstance():getScheduler():scheduleScriptFunc(handler(self, self.refreshScoreExecutor), 0.01, false)
end

--模仿时间滚动变化的效果
function StatusLayer:refreshScoreExecutor(dt)
	if (self:getChildByTag(CURRENT_SCORE_SPRITE_TAG)) then
		self:removeChildByTag(CURRENT_SCORE_SPRITE_TAG)
	end
	self.scoreSprite = number:convert(numberScore, self.tempScore, Gravity.GRAVITY_RIGHT)
	self.scoreSprite:setAnchorPoint({ x=1, y=0 })
	self.scoreSprite:setPosition({ x=origin.x + visibleSize.width*3/4 + 20, y=origin.y + visibleSize.height/2 + self.scoreSprite:getContentSize().height*3/2 })
	self.scoreSprite:setTag(CURRENT_SCORE_SPRITE_TAG)
	self:addChild(self.scoreSprite)
	self.tempScore = self.tempScore + 1
	if (self.tempScore > self.currentScore) then 
		cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self.refreshScoreSchedule)
	end
end

--把布灵布灵实例化
function StatusLayer:setBlinkSprite()
	self.blink = cc.Sprite:createWithSpriteFrame(atlasLoader:getSpriteFrameByName(blinkName))
	local animation = cc.Animation:create()
	animation:setDelayPerUnit(0.1)
	local fileName
	local frame
	for i = 1, 3-1 do
		fileName = string.format("blink_%02d", i)
		frame = atlasLoader:getSpriteFrameByName(fileName)
		animation:addSpriteFrame(frame)
	end
	for i = 2, 0 do
		fileName = string.format("blink_%02d", i)
		frame = atlasLoader:getInstance():getSpriteFrameByName(fileName)
		animation:addSpriteFrame(frame)
	end
	local animate = cc.Animate:create(animation)
	local actionDone = cc.CallFunc:create(handler(self, self.blinkAction))
	local sequence = cc.Sequence:create(animate, actionDone)
	self.blink:runAction(cc.RepeatForever:create(sequence))
end

--随机位置,布灵布灵
function StatusLayer:blinkAction()
	if self.blink and self.blink:getParent() then
		local activeSize = self.blink:getParent():getContentSize()
		self.blink:setPosition({ x=math.random(activeSize.width)-1, y=math.random(activeSize.height)-1 })
	end
end

--金银铜铁,布灵布灵
function StatusLayer:getMedalsName(score)
	self:setBlinkSprite()
	local medalsName = ""
	if (self.currentScore >= 10 and self.currentScore < 20) then
		medalsName = "medals_0"
	elseif (self.currentScore >= 20 and self.currentScore < 30) then
		medalsName = "medals_1"
	elseif (self.currentScore >= 30 and self.currentScore < 50) then
		medalsName = "medals_2"
	elseif (self.currentScore >= 50) then
		medalsName = "medals_3";
	end
	return medalsName
end

--重新开始按钮点击
function StatusLayer:menuRestartCallback()
	cc.SimpleAudioEngine:getInstance():playEffect(swooshingOGG)
    local scene = require("app.views.GameScene"):createScene()
    local transition = cc.TransitionFade:create(1.3, scene)
    cc.Director:getInstance():replaceScene(transition)
end

return StatusLayer

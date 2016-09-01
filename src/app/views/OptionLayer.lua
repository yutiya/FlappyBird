
local OptionLayer = class("OptionLayer", cc.Layer)

function OptionLayer:ctor()
	self:registerScriptHandler(handler(self, self.onNodeEvent))
end

function OptionLayer:onNodeEvent(event)
	if event == "enter" then
		self:onEnter()
	elseif event == "exit" then
		self:onExit()
	end
end

function OptionLayer:onEnter()
	local dispatcher = cc.Director:getInstance():getEventDispatcher()
	local listener = cc.EventListenerTouchAllAtOnce:create()
	listener:registerScriptHandler(handler(self, self.onTouchBegan), cc.Handler.EVENT_TOUCHES_BEGAN)
	dispatcher:addEventListenerWithSceneGraphPriority(listener, self)
end

function OptionLayer:onExit()
	self:unregisterScriptHandler()
	cc.Director:getInstance():getEventDispatcher():removeEventListenersForTarget(self)
end

function OptionLayer:onTouchBegan(touches, event)
	if self.gameDelegate then
		self.gameDelegate:onTouch()
	end
end

return OptionLayer

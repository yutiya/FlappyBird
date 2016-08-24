
local GameScene = class("GameScene", cc.Layer)

function GameScene:createScene()
	local scene = cc.Scene:create()
	local backgroundLayer = require("app.views.BackgroundLayer"):create()
	local layer = GameScene:create()
	scene:addChild(backgroundLayer)
	scene:addChild(layer)
	return scene
end

return GameScene

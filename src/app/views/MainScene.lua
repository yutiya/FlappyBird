--print("MainScene")
local backgroundImageName = "splash.png"
local imageName = "atlas.png"
local audioData = { "sfx_die.ogg", "sfx_hit.ogg", "sfx_point.ogg", "sfx_swooshing.ogg", "sfx_wing.ogg" }

local MainScene = class("MainScene", cc.load("mvc").ViewBase)

--MainScene.RESOURCE_FILENAME = "MainScene.csb"

function MainScene:onCreate()
    --print("resource node = %s", tostring(self:getResourceNode()))
    
    --[[ you can create scene with following comment code instead of using csb file.
    -- add background image
    display.newSprite("HelloWorld.png")
        :move(display.center)
        :addTo(self)

    -- add HelloWorld label
    cc.Label:createWithSystemFont("Hello World", "Arial", 40)
        :move(display.cx, display.cy + 200)
        :addTo(self)
    ]]
    local background = cc.Sprite:create(backgroundImageName)
    local visibleSize = cc.Director:getInstance():getVisibleSize()
    local origin = cc.Director:getInstance():getVisibleOrigin()

    background:setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2)
    self:addChild(background)

    cc.Director:getInstance():getTextureCache():addImageAsync(imageName, self.loadingCallBack)
end

function MainScene:loadingCallBack()
    require("app.tools.AtlasLoader"):getInstance()
    for k in ipairs(audioData) do
        cc.SimpleAudioEngine:getInstance():preloadEffect(audioData[k])
    end
    local scene = require("app.views.WelcomeScene"):create()
    local transition = cc.TransitionFade:create(1.3, scene)
    cc.Director:getInstance():replaceScene(transition)
end

return MainScene

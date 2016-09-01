--print("AtlasLoader")
local _atlasData = {}

local _atlasLoader = nil
local imageName = "atlas.png"
local fileName = "atlas.txt"

local AtlasLoader = class("AtlasLoader", cc.Object)

--AtlasLoader._index = AtlasLoader

--setmetatable(_atlasLoader, AtlasLoader)

function AtlasLoader:getInstance()
    if _atlasLoader == nil then
        _atlasLoader = AtlasLoader:create()
    end
    return _atlasLoader
end

function AtlasLoader:destroyInstance()
	_atlasLoader = nil
end

--生成sprite lua file
local function generateSpriteFrameCache()
	-- print("AtlasLoader generateSpriteFrameCache")
	local atlasFileData = cc.FileUtils:getInstance():getStringFromFile(fileName)
	local pos = string.find(atlasFileData, "\n")
	local line = string.sub(atlasFileData, 0, pos)
	local atlasFileData = string.sub(atlasFileData, pos+1, string.len(atlasFileData))
	local tmpSprite
	while (line ~= "")
	do
		tmpSprite = {}
		for i in string.gmatch(line, "%S+") do
			tmpSprite[#tmpSprite+1] = i
		end
		local xSprite = math.floor(1024 * (tonumber(tmpSprite[4])) + 0.1)
		local ySprite = math.floor(1024 * (tonumber(tmpSprite[5])) + 0.1)
		if(tmpSprite[1] == "land") then
			xSprite = xSprite + 1
		end
		_atlasData[tmpSprite[1]] = { width = tmpSprite[2], height = tmpSprite[3], x = xSprite, y = ySprite }
		--计算下一行,找不到为nil
		pos = string.find(atlasFileData, "\n")
		if(pos == nil) then
			break
		end
		line = string.sub(atlasFileData, 0, pos)
		atlasFileData = string.sub(atlasFileData, pos+1, string.len(atlasFileData))
	end
end

function AtlasLoader:ctor()
	generateSpriteFrameCache()
end

function AtlasLoader:getSpriteFrameByName(name)
	local textureAtlas = cc.Director:getInstance():getTextureCache():addImage(imageName)
	return cc.SpriteFrame:createWithTexture(textureAtlas, _atlasData[name])
end

return AtlasLoader

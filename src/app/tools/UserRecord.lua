
local _userRecord = nil

local UserRecord = class("UserRecord", cc.Object)

function UserRecord:getInstance()
    if _userRecord == nil then
        _userRecord = UserRecord:create()
    end
    return _userRecord
end

function UserRecord:destroyInstance()
	_userRecord = nil
end

function UserRecord:saveIntegerToUserDefault(key, score)
	local oldScore = cc.UserDefault:getInstance():getIntegerForKey(key)
	if score > oldScore then
		cc.UserDefault:getInstance():setIntegerForKey(key, score)
	end
end

function UserRecord:readIntegerFromUserDefault(key)
	return cc.UserDefault:getInstance():getIntegerForKey(key)
end

return UserRecord

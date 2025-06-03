-- debugging
tod.TraceAndLog("Hey from Lua! CurveQuad(0.4): " .. tostring(tod.CurveQuad(0.4)))
--tod.ErrorMessageBox("i am evil!", "Error")

-- rects, points
local r1 = Sexy.Rect.new() -- default rect (0,0,0,0)
local r2 = Sexy.Rect.new(10, 20, 100, 200)
local r3 = Sexy.Rect.new(r2) -- copy constructor

print("r2:", r2.mX, r2.mY, r2.mWidth, r2.mHeight) -- 10 20 100 200

r2:Inflate(5, 5)
print("r2 inflated:", r2.mX, r2.mY, r2.mWidth, r2.mHeight)
-- should print (20, 40, 120, 220) because Inflate expands and shifts

local r4 = Sexy.Rect.new(30, 40, 50, 60)
local intersects = r2:Intersects(r4)
print("r2 intersects r4?", intersects)

local inter = r2:Intersection(r4)
print("Intersection rect:", inter.mX, inter.mY, inter.mWidth, inter.mHeight)

local uni = r2:Union(r4)
print("Union rect:", uni.mX, uni.mY, uni.mWidth, uni.mHeight)

print("r2 contains point (40, 50)?", r2:Contains(40, 50))

print("r2 == r3?", r2 == r3) -- false after offset and inflate
print("r3 == Sexy.Rect(10, 20, 100, 200)?", r3 == Sexy.Rect.new(10, 20, 100, 200)) -- true

-- paks
local pak = PakInterface

local ok = pak:AddPakFile("robots.pak")
print("pak file loaded?", ok)

local file = pak:FOpen("sounds\\ZombiesOnYourLawn.ogg", "rb")
if file ~= nil then
    local size_bytes = file.mRecord.mSize
    local size_mb = size_bytes / (1024 * 1024)
    print(string.format("file size: %.2f MB", size_mb))

    pak:FClose(file)
end

-- colors
local c = Sexy.Color.new(255, 100, 50, 255)
print("red:", c:GetRed())

local white = Sexy.Color.White
print("white RGB:", white.mRed, white.mGreen, white.mBlue)

-- matrix and stuff
local m = Sexy.Matrix3.new()
m:LoadIdentity()

local t = Sexy.Transform2D.new()
t:Translate(10, 20)
t:RotateDeg(90)

local tr = Sexy.Transform.new()
tr:Translate(5, 5)
tr:Scale(2, 2)
tr:RotateDeg(90)

print("rotation of transform:", tr.mRot)

-- BASS!!!
local music = GetBassMusic()

music:FadeOutAll(true, 2.0)

-- typing checks
tc = Sexy.TypingCheck.new("sexy")

Hook.new("TypingCheck::AddKeyCode", function(self, code)
	if tc:Check(code) then
		print("typed correctly!")
	else
		print("keep typing...")
	end
end)
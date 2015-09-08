Vector = require('vector')

local InverseMetersPerPixel = 1/5

local PhysicsAcc = 0
local Physics_DT = 1/60
local Physics_G = -9.82
local Physics_DAMPENING = 0.0
local Physics_ELASTICITY = 0.4
local Physics_FRICTION = 0.15

local LaunchVelocity = Vector(10, 0)
local LaunchPosition = Vector(0, 600 / InverseMetersPerPixel)

local Ball = {}
Ball.Position = Vector(0, 0)
Ball.Velocity = Vector(0, 0)
Ball.Radius = 8 / InverseMetersPerPixel

local PlaneNormal = Vector(0, 1)
PlaneNormal:normalize_inplace()
local PlaneOrigin = Vector(0, 100 / InverseMetersPerPixel)

function LaunchBall(pos, vel)
    Ball.Position = pos or LaunchPosition
    Ball.Velocity = vel or LaunchVelocity
end

-- Load some default values for our rectangle.
function love.load()
    LaunchBall()
end

-- Increase the size of the rectangle every frame.
function love.update(dt)
	require("lurker"):update()

    PhysicsAcc = PhysicsAcc + dt

    while PhysicsAcc >= Physics_DT do
    	PhysicsAcc = PhysicsAcc -  Physics_DT

    	--UPDATE PHYSICS

        Ball.Velocity = (Ball.Velocity + Vector(0, Physics_G) ) * (1-Physics_DAMPENING)

        Ball.Position = Ball.Position + Ball.Velocity

        local depth = Ball.Radius - ((Ball.Position - PlaneOrigin)*PlaneNormal)

        if depth > 0 then

            -- If inside ground, move up
            Ball.Position = Ball.Position + (PlaneNormal * depth)

            local VelocityAlongPlane = ((Ball.Velocity - PlaneNormal*(PlaneNormal*Ball.Velocity)) * (1-Physics_FRICTION))
            local VelocityAlongPlaneNormal = -Physics_ELASTICITY*PlaneNormal*(PlaneNormal*Ball.Velocity)

            Ball.Velocity = VelocityAlongPlane + VelocityAlongPlaneNormal

        end
    end
end

-- Draw a coloured rectangle.
function love.draw()
    love.graphics.translate(200, 600)
    love.graphics.scale(InverseMetersPerPixel, -InverseMetersPerPixel )

    love.graphics.setColor(0, 100, 100)

    local LineVector =  (PlaneNormal:perpendicular() * 10000)

    --print(LineVector)

    love.graphics.line(PlaneOrigin.x + LineVector.x, PlaneOrigin.y + LineVector.y, PlaneOrigin.x - LineVector.x, PlaneOrigin.y - LineVector.y)

    love.graphics.circle("fill", Ball.Position.x, Ball.Position.y, Ball.Radius, 32)
end

function love.keypressed(key, isrepeat)
    if key == "escape" then
        love.event.quit()
    end

    if key == "1" then
        LaunchBall()--Default
    end

    if key == "2" then
        LaunchBall(Vector(0, 300 / InverseMetersPerPixel), Vector(150, 0))
    end

    if key == "3" then
        LaunchBall(Vector(0, 100 / InverseMetersPerPixel), Vector(50, 200))
    end

    if key == "q" then--Default
        PlaneNormal = Vector(0, 1)
        PlaneNormal:normalize_inplace()
    end

    if key == "w" then
        PlaneNormal = Vector(-0.2, 1)
        PlaneNormal:normalize_inplace()
    end

     if key == "e" then
        PlaneNormal = Vector(0.2, 1)
        PlaneNormal:normalize_inplace()
    end

    if key == "r" then
        LaunchBall()

    end
end
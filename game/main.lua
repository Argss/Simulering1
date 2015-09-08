Vector = require('vector')

local PhysicsAcc = 0
local Physics_DT = 1/60
local Physics_G = -9.82
local Physics_DAMPENING = 0.0
local Physics_ELASTICITY = 1.0

local LaunchVelocity = Vector(10, 0)
local LaunchPosition = Vector(0, 600)

local Ball = {}
Ball.Position = Vector(0, 0)
Ball.Velocity = Vector(0, 0)
Ball.Radius = 8

local PlaneNormal = Vector(0.1, 1)
PlaneNormal:normalize_inplace()
local PlaneOrigin = Vector(0, 100)

function LaunchBall()
    Ball.Position = LaunchPosition
    Ball.Velocity = LaunchVelocity
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

        --V = V - (1+Physics_ELASTICITY)*N*(N*V)

        local n = PlaneNormal

        local vrel = Ball.Velocity * PlaneNormal
        local depth = Ball.Radius - ((Ball.Position - PlaneOrigin)*n)

        if depth > 0 then

            Ball.Velocity = Ball.Velocity - (1+Physics_ELASTICITY)*PlaneNormal*(PlaneNormal*Ball.Velocity)

        end
    end
end

-- Draw a coloured rectangle.
function love.draw()
    love.graphics.translate(200, 600)
    love.graphics.scale(1.0, -1.0 )

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

    if key == "r" then
        LaunchBall()

    end
end
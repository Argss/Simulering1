Vector = require('vector')

local PhysicsAcc = 0
local Physics_DT = 1/60

local Ball = {}
Ball.Position = Vector(0, 0)
Ball.Velocity = Vector(0, 0)
Ball.Radius = 64

-- Load some default values for our rectangle.
function love.load()
    local t = Vector(20, 20)
    print(t)
end
 
-- Increase the size of the rectangle every frame.
function love.update(dt)
	require("lurker"):update()
    PhysicsAcc = PhysicsAcc + dt

    while PhysicsAcc >= Physics_DT do
    	PhysicsAcc = PhysicsAcc -  Physics_DT

    	--UPDATE PHYSICS

        Ball.Velocity = Ball.Velocity + Vector(0, 9.82)
        Ball.Position = Ball.Position + Ball.Velocity
    end
end
 
-- Draw a coloured rectangle.
function love.draw()
    love.graphics.setColor(0, 100, 100)
    --love.graphics.rectangle("fill", x, y, w, h)

    love.graphics.circle("fill", Ball.Position.x, Ball.Position.y, Ball.Radius, 32)
end

function love.keypressed(key, isrepeat)
    if key == "escape" then
        love.event.quit()
    end

    if key == "r" then
        Ball.Position = Vector(0, 0)
        Ball.Velocity = Vector(0, 0)
    end
end